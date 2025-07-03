#ifndef BALANCED_MEAL_PLANNER_H
#define BALANCED_MEAL_PLANNER_H

#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/MealPlan.h"
#include "core/IngredientDatabase.h"
#include "IMealPlanner.h"

#include <vector>

namespace mealplanner::application {
    /**
     * @brief A meal planner that generates a nutritionally balanced meal plan by scoring combinations.
     */
    class BalancedMealPlanner : public IMealPlanner {
    public:
        explicit BalancedMealPlanner(const IngredientDatabase& ingredientDatabase);
    
        model::MealPlan generateMealPlan(const std::vector<model::Recipe>& recipes, const model::UserProfile& user) override;
    
    private:
        const IngredientDatabase& m_ingredientDatabase;
    };
}

#endif // BALANCED_MEAL_PLANNER_H