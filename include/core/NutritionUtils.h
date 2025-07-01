#ifndef NUTRITION_UTILS_H
#define NUTRITION_UTILS_H

#include "Recipe.h"
#include "MealPlan.h"
#include "UserProfile.h"
#include <vector>
#include <string>

namespace NutritionUtils {
    MacroRatios calculateRatios(int protein, int carbs, int fat, int totalKcal);
    bool isRecipeCompliant(const Recipe& recipe, const std::vector<std::string>& restrictions);
    double scorePlan(const MealPlan& plan, const UserProfile& user);
}

#endif // NUTRITION_UTILS_H
