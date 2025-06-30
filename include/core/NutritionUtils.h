#ifndef NUTRITION_UTILS_H
#define NUTRITION_UTILS_H

#include "core/Recipe.h"
#include <vector>
#include <string>

struct MacroRatios {
    double protein = 0;
    double carbs = 0;
    double fat = 0;
};

namespace NutritionUtils {
    MacroRatios calculateRatios(int protein, int carbs, int fat, int totalKcal);
    bool isRecipeCompliant(const Recipe& recipe, const std::vector<std::string>& restrictions);
}

#endif // NUTRITION_UTILS_H
