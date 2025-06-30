#ifndef I_MEAL_PLANNER_H
#define I_MEAL_PLANNER_H

#include <vector>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/MealPlan.h"

class IMealPlanner {
public:
    virtual ~IMealPlanner() = default;

    virtual MealPlan generateMealPlan(const std::vector<Recipe>& recipes, const UserProfile& user) = 0;
};

#endif // I_MEAL_PLANNER_H