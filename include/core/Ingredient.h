#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>

struct Ingredient {
    std::string name;
    double quantity;
    std::string unit;
    double kcalPerUnit = 0.0;
    double proteinPerUnit = 0.0;
    double carbsPerUnit = 0.0;
    double fatPerUnit = 0.0;
};

#endif // INGREDIENT_H