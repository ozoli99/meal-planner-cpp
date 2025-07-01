#ifndef INGREDIENT_DATABASE_H
#define INGREDIENT_DATABASE_H

#include <unordered_map>
#include <string>

#include "Ingredient.h"

class IngredientDatabase {
public:
    void loadFromFile(const std::string& path);
    bool has(const std::string& name) const;
    Ingredient getPerUnitInfo(const std::string& name) const;

private:
    std::unordered_map<std::string, Ingredient> m_ingredients;
};

#endif // INGREDIENT_DATABASE_H