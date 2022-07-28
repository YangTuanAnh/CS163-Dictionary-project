#include "Dictionary.h"

Word::Word(const std::string &s)
{
    index = -1;
    isFavorite = false;
    data = s;
}

ResourceWord::ResourceWord(const std::string &s)
{
    data = s;
}

Definition::Definition(const std::string &s)
{
    data = s;
}

Dictionary::Dictionary(const std::string &_dir, const std::string &chars, const std::string &resourceChars)
{
    dir = _dir;
    trie = new Trie<Word *>(chars, nullptr);
    resource = new Trie<ResourceWord *>(resourceChars, nullptr);
    loadData();
    loadHistory();
    loadFavorite();
}

Dictionary::~Dictionary()
{
    saveData();
    saveHistory();
    saveFavorite();
    for (auto word : allWords)
    {
        delete word;
    }
    for (auto def : allDefs)
    {
        delete def;
    }
    allWords.clear();
    allDefs.clear();
    history.clear();
    delete trie;
}

void Dictionary::loadHistory()
{
    std::string filePath = dir + "/history.txt";
    std::ifstream fin(filePath);
    if (!fin.is_open())
    {
        std::cerr << "Could not load file " << filePath << std::endl;
        exit(0);
    }
    std::string line;
    while (getline(fin, line))
    {
        Word *temp;
        if (trie->find(line, temp) != success)
        {
            std::cerr << "Could not load history (" << line << ")" << std::endl;
            continue;
        }
        history.push_back(temp);
    }
    fin.close();
}

void Dictionary::loadFavorite()
{
    std::string filePath = dir + "/favorite.txt";
    std::ifstream fin(filePath);
    if (!fin.is_open())
    {
        std::cerr << "Could not load file " << filePath << std::endl;
        exit(0);
    }
    std::string line;
    while (getline(fin, line))
    {
        Word *temp;
        if (trie->find(line, temp) != success)
        {
            std::cerr << "Could not load favorite (" << line << ")" << std::endl;
            continue;
        }
        updateFavorite(temp);
    }
    fin.close();
}

void Dictionary::loadData()
{
    std::string filePath = dir + "/data.txt";
    std::ifstream fin(filePath);
    if (!fin.is_open())
    {
        std::cerr << "Could not load file " << filePath << std::endl;
        exit(0);
    }

    std::string line;
    int lineNum = 0;
    while (getline(fin, line))
    {
        ++lineNum;
        auto tmp = Split(line, '\t');

        if (tmp.size() != 2)
        {
            std::cerr << "in file: " << filePath << ":" << std::endl;
            std::cerr << "skip line " << lineNum << ": " << line << std::endl;
        }
        else
        {
            Word *word;
            if (trie->find(tmp[0], word) != success)
            {
                word = new Word(tmp[0]);
                if (trie->insert(tmp[0], word) != success)
                {
                    std::cerr << "in file: " << filePath << ":" << std::endl;
                    std::cerr << "could not insert word " << tmp[0] << std::endl;
                    continue;
                }
                allWords.push_back(word);
                word->index = allWords.size() - 1;
            }

            Definition *def = new Definition(tmp[1]);
            word->defs.push_back(def);
            def->word = word;
            allDefs.push_back(def);
            updateDefsLinks(def, +1);
        }
    }
    fin.close();
}

void Dictionary::updateHistory(Word *word, bool addOrDel)
{
    for (int i = 0; i < (int)history.size(); i++)
        if (history[i] == word)
        {
            history.erase(history.begin() + i);
        }
    if (addOrDel)
        history.insert(history.begin(), word);
    if (history.size() > HISTORY_LIMIT)
        history.pop_back();
}

Word *Dictionary::insertWord(std::string newWord)
{
    Word *word;
    if (trie->find(newWord, word) == success)
    {
        std::cerr << newWord << " already exist" << std::endl;
        return nullptr;
    }
    word = new Word(newWord);
    allWords.push_back(word);
    trie->insert(newWord, word);
    return word;
}

void Dictionary::insertDef(Word *word, std::string newDef)
{
    Definition *def = new Definition(newDef);
    allDefs.push_back(def);
    word->defs.push_back(def);
    updateDefsLinks(def, +1);
}

void Dictionary::editDef(Definition *def, std::string newData)
{
    updateDefsLinks(def, -1);
    def->data = newData;
    updateDefsLinks(def, +1);
}

void Dictionary::deleteDef(Definition *def)
{
    if (std::find(def->word->defs.begin(), def->word->defs.end(), def) == def->word->defs.end())
    {
        std::cerr << "Error: link from word not exist (deleteDef)" << std::endl;
        return;
    }
    if (std::find(allDefs.begin(), allDefs.end(), def) == allDefs.end())
    {
        std::cerr << "Error: allDefs does not contain this def (deleteDef)" << std::endl;
        return;
    }
    updateDefsLinks(def, -1);
    def->word->defs.erase(std::find(def->word->defs.begin(), def->word->defs.end(), def));
    allDefs.erase(std::find(allDefs.begin(), allDefs.end(), def));
    delete def;
}

void Dictionary::deleteWord(Word *word)
{
    for (auto def : word->defs)
    {
        deleteDef(def);
    }
    if (std::find(allWords.begin(), allWords.end(), word) == allWords.end())
    {
        std::cerr << "Error: allWords does not contain this word (deleteWord)" << std::endl;
        return;
    }
    allWords.erase(std::find(allWords.begin(), allWords.end(), word));
    assert(trie->trie_delete(word->data) == success);
    delete word;
}

void Dictionary::updateFavorite(Word *word)
{
    word->isFavorite = true;
    std::cerr << "set " << word->data << "->isFavorite = " << std::boolalpha << word->isFavorite << std::endl;
}
void Dictionary::removeFavorite(Word *word)
{
    word->isFavorite = false;
    std::cerr << "set " << word->data << "->isFavorite = " << std::boolalpha << word->isFavorite << std::endl;
}

std::vector<Word *> Dictionary::SearchWord(const std::string &key)
{
    if (key != "")
        return trie->search(key);
    return getSearchHistory();
}

std::vector<Word *> Dictionary::SearchDef(const std::string &key)
{
    for (auto def : allDefs)
    {
        def->_cnt = 0;
    }

    for (auto s : Split(key, ' '))
    {
        s = Normalize(s);
        if (s.size() < 3)
        {
            continue;
        }
        ResourceWord *tmp;
        if (resource->find(s, tmp) == Trie_error::success)
        {
            for (auto def : tmp->defs)
            {
                ++def->_cnt;
            }
        }
    }

    std::sort(allDefs.begin(), allDefs.end(), [](auto a, auto b)
              { return a->_cnt > b->_cnt; });

    std::vector<Word *> result;
    for (auto def : allDefs)
    {
        if (def->_cnt > 0)
        {
            bool exist = false;
            for (auto w : result)
            {
                if (w == def->word)
                {
                    exist = true;
                    break;
                }
            }
            if (!exist)
            {
                result.push_back(def->word);
            }
        }
        if ((int)result.size() == SEARCH_RESULTS_LIMIT)
        {
            break;
        }
    }

    return result;

    /*

    std::vector<std::pair<int, int>> rank(allWords.size());
    for (int i = 0; i < (int)rank.size(); i++)
    {
        rank[i].first = 0;
        rank[i].second = i;
    }
    for (int i = 0; i < DefResource.size(); i++)
    {
        ResourceWord *tmp;
        if (resource->find(DefResource[i], tmp) == success)
        {
            for (int j = 0; j < tmp->inDefOf.size(); j++)
                rank[tmp->inDefOf[j]].first++;
        }
    }
    quick_sort(rank, 0, rank.size() - 1);
    std::vector<Word *> result;
    for (int i = 0; i < rank.size(), result.size() < 50; i++)
    {
        if (rank[i].first > 0)
            result.push_back(allWords[rank[i].second]);
        else if (rank[i].first == 0)
            break;
    }
    return result;
    */
}

std::vector<std::string> Dictionary::getFullDefinition(const std::string &word)
{
    Word *ptr;
    if (trie->find(word, ptr) != success)
    {
        std::cerr << "Word " << word << " not exist.";
        return std::vector<std::string>();
    }
    updateHistory(ptr, true);

    std::vector<std::string> defs;
    for (auto def : ptr->defs)
    {
        defs.push_back(def->data);
    }
    return defs;
}

std::vector<Word *> Dictionary::getSearchHistory()
/* Returns the latest searched words, up to 20 records
 */
{
    std::vector<Word *> result = history;
    return result;
}

std::vector<Word *> Dictionary::getFavoriteList()
{
    std::vector<Word *> result;
    for (auto word : allWords)
    {
        if (word->isFavorite)
        {
            result.push_back(word);
        }
    }
    return result;
}

void Dictionary::saveData()
{
    // implement later
}

void Dictionary::saveHistory()
{
    std::ofstream fout(dir + "/history.txt");
    if (!fout.is_open())
    {
        std::cerr << "could not save file" + dir + "/history.txt" << std::endl;
    }
    else
    {
        for (int i = 0; i < (int)history.size(); i++)
            fout << history[i]->data << "\n";
    }
    fout.close();
}

void Dictionary::saveFavorite()
{
    std::ofstream fout(dir + "/favorite.txt");
    if (!fout.is_open())
    {
        std::cerr << "could not save file" + dir + "/favorite.txt" << std::endl;
    }
    else
    {
        for (auto word : getFavoriteList())
        {
            fout << word->data << "\n";
        }
    }
    fout.close();
}

std::string Dictionary::getRandomWord()
{
    using namespace std::chrono;
    auto seedValue = duration_cast<seconds>(steady_clock::now().time_since_epoch()).count();
    std::srand(seedValue);
    return allWords[rand() % allWords.size()]->data;
}

std::vector<Word *> Dictionary::generateRandQuiz()
/* This functions returns a vector of 5 integers quiz[5], where quiz[0..3] are indices of random chosen Words,
and quiz[4] is the Answer.
            quiz[0] -> response given by option A
            quiz[1] -> response given by option B
            quiz[2] -> response given by option C
            quiz[3] -> response given by option D
            quiz[4] -> one of the value{0, 1, 2, 3} corresponding to the correct answer
*/
{
    using namespace std::chrono;
    std::vector<int> quiz;
    std::vector<Word *> ans;
    auto seedValue = duration_cast<seconds>(steady_clock::now().time_since_epoch()).count();
    std::srand(seedValue);
    for (int i = 0; i < 4; i++)
    {
        auto new_option = rand() % (allWords.size());  // generate an index from 0 to allWords.size()-1
        while (!checkQuizValidation(new_option, quiz)) // Check to prevent options duplication
            new_option = rand() % (allWords.size());
        quiz.push_back(new_option);
        ans.push_back(allWords[new_option]);
    }
    ans.push_back(ans[rand() % 4]); // generate the Answer
    return ans;
}

/*
type = +1: create links form resourceWord to Def
type = -1: delete above links
*/
void Dictionary::updateDefsLinks(Definition *def, int type)
{
    for (auto rw : Split(def->data, ' '))
    {
        rw = Normalize(rw);
        if (rw.size() < 3)
        {
            continue;
        }
        if (type == +1)
        {
            ResourceWord *tmp;
            if (resource->find(rw, tmp) == Trie_error::non_exist)
            {
                tmp = new ResourceWord(rw);
                assert(resource->insert(rw, tmp) == Trie_error::success);
            }
            tmp->defs.push_back(def);
        }
        else if (type == -1)
        {
            ResourceWord *tmp;
            if (resource->find(rw, tmp) == Trie_error::non_exist)
            {
                std::cerr << "Error: ResourceWord not found (updateDefsLinks)" << std::endl;
                return;
            }
            if (std::find(tmp->defs.begin(), tmp->defs.end(), def) == tmp->defs.end())
            {
                std::cerr << "Error: corresponding definition not found (updateDefsLinks)" << std::endl;
                return;
            }
            tmp->defs.erase(std::find(tmp->defs.begin(), tmp->defs.end(), def));
        }
        else
        {
            std::cerr << "Error: invalid argument (updateDefsLinks)" << std::endl;
        }
    }
}

bool checkQuizValidation(int new_option, std::vector<int> &quiz)
/* This function helps Dictionary::generateRandQuiz() with checking if a new generated option already exists.
If it does, return false - invalid. Else, return true - valid. */
{
    for (int i = 0; i < quiz.size(); i++)
        if (quiz[i] == new_option)
            return false;
    return true;
}

std::vector<std::string> Split(const std::string &s, char delim)
{
    std::string tmp;
    std::vector<std::string> res;
    for (char ch : s)
    {
        if (ch == delim)
        {
            res.push_back(tmp);
            tmp.clear();
        }
        else
        {
            tmp.push_back(ch);
        }
    }
    res.push_back(tmp);
    return res;
}

bool IsPrefix(const std::string &p, const std::string &s)
{
    if (p.size() > s.size())
    {
        return false;
    }
    return (p == s.substr(0, p.size()));
}

// keeps letters and digits only
std::string Normalize(const std::string &s)
{
    std::string norm;
    for (auto c : s)
    {
        if ('a' <= c && c <= 'z')
        {
            norm.push_back(c);
        }
        else if ('A' <= c && c <= 'Z')
        {
            norm.push_back(c + ' '); // to lowercase
        }
        else if ('0' <= c && c <= '9')
        {
            norm.push_back(c);
        }
    }
    return norm;
}
