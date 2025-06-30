#ifndef MEAL_PLAN_H
#define MEAL_PLAN_H

#include <vector>
#include "Recipe.h"
#include "NutritionUtils.h"

struct MealPlan {
    std::vector<Recipe> selectedRecipes;
    int totalKcal = 0;
    int totalProtein = 0;
    int totalCarbs = 0;
    int totalFats = 0;

    MacroRatios GetRatios() const;
};

#endif // MEAL_PLAN_H