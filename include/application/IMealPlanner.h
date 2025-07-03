#ifndef I_MEAL_PLANNER_H
#define I_MEAL_PLANNER_H

#include <vector>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/MealPlan.h"

namespace mealplanner::application {
    class IMealPlanner {
    public:
        virtual ~IMealPlanner() = default;
    
        virtual model::MealPlan generateMealPlan(const std::vector<model::Recipe>& recipes, const model::UserProfile& user) = 0;
    };
}

#endif // I_MEAL_PLANNER_H