#ifndef RECIPE_H
#define RECIPE_H

#include <vector>
#include <string>

struct Recipe {
    std::string id;
    std::string name;
    std::string type;
    int kcal;
    int protein;
    int carbs;
    int fat;
    int prepTimeMinutes;
    std::vector<std::string> tags;
};

#endif // RECIPE_H