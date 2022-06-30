#include "search.h"
#include "Trie.h"
#include "limits.h"

std::vector<Word *> allWords;
std::vector<Definition *> allDefs;
Trie<Word *, 256> *trie;

Word::Word(const std::string &s)
{
    data = s;
}

Definition::Definition(const std::string &s)
{
    data = s;
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

void LoadData(const std::string &filePath)
{
    std::ifstream fin(filePath);
    if (!fin.is_open())
    {
        std::cerr << "could not load file " << filePath << std::endl;
        throw 1;
    }

    trie = new Trie<Word *, 256>(nullptr);

    std::string line;
    Word *lastWord = nullptr;
    while (getline(fin, line))
    {
        auto tmp = Split(line, '`');

        if (tmp.size() > 1)
        {
            lastWord = new Word(tmp[0]);
            trie->insert(lastWord->data, lastWord);
            allWords.push_back(lastWord);
            tmp.erase(tmp.begin());
        }

        Definition *def = new Definition(tmp[0]);
        lastWord->defs.push_back(def);
        def->word = lastWord;

        allDefs.push_back(def);
    }

    fin.close();
}

std::vector<Word *> SearchWord(const std::string &key)
{
    return trie->search(key);
}

std::vector<Word *> SearchDef(const std::string &key)
{
    std::vector<Word *> results;
    for (auto def : allDefs)
    {
        if (IsPrefix(key, def->data) && results.size() < SEARCH_RESULTS_LIMIT)
        {
            results.push_back(def->word);
        }
    }
    return results;
}

void Deallocate()
{
    for (auto word : allWords)
    {
        delete word;
    }
    for (auto def : allWords)
    {
        delete def;
    }
    allWords.clear();
    allDefs.clear();
    delete trie;
}
