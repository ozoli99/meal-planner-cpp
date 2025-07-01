#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>
#include "Ingredient.h"

struct Recipe {
    std::string id;
    std::string name;
    std::string type;
    int kcal = 0;
    int protein = 0;
    int carbs = 0;
    int fat = 0;
    int prepTimeMinutes = 0;
    std::vector<std::string> tags;
    std::vector<Ingredient> ingredients;
};

#endif // RECIPE_H