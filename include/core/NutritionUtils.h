#ifndef NUTRITION_UTILS_H
#define NUTRITION_UTILS_H

#include "Recipe.h"
#include "MealPlan.h"
#include "UserProfile.h"
#include <vector>
#include <string>

namespace NutritionUtils {
    mealplanner::model::MacroRatios calculateRatios(int protein, int carbs, int fat, int totalKcal);
    bool isRecipeCompliant(const mealplanner::model::Recipe& recipe, const std::vector<std::string>& restrictions);
    double scorePlan(const mealplanner::model::MealPlan& plan, const mealplanner::model::UserProfile& user);
}

#endif // NUTRITION_UTILS_H
