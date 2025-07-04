#ifndef MEAL_PLAN_H
#define MEAL_PLAN_H

#include <vector>
#include "Recipe.h"
#include "MacroRatios.h"

namespace mealplanner::model {
    struct MealPlan {
        std::vector<Recipe> selectedRecipes;
        Calories totalKcal = Calories{0};
        Grams totalProtein = Grams{0};
        Grams totalCarbs = Grams{0};
        Grams totalFats = Grams{0};
    
        MacroRatios GetRatios() const;
    };
}

#endif // MEAL_PLAN_H