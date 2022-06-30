#include "favorites.h"
#include <vector>

std::vector<Word *> favorites;
void insertFavorites(Word *word)
{
    favorites.push_back(word);
}
void removeFavorites(Word *word)
{
}
void printFavorites()
{
    for (auto i : favorites)
        std::cerr << i->data << ' ';
    std::cout << '\n';
}