#pragma once
#include <vector>
#include "../utility/search.h"

extern std::vector<Word*> favorites;
void insertFavorites(Word* word);
void removeFavorites(Word* word);
void printFavorites();
class Favorites
{
private:
public:
};