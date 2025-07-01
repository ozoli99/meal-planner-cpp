#ifndef BALANCED_MEAL_PLANNER_H
#define BALANCED_MEAL_PLANNER_H

#include <vector>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/MealPlan.h"
#include "IMealPlanner.h"

class BalancedMealPlanner : public IMealPlanner {
public:
    BalancedMealPlanner();
    
    MealPlan generateMealPlan(const std::vector<Recipe>& recipes, const UserProfile& user) override;
};

#endif // BALANCED_MEAL_PLANNER_H