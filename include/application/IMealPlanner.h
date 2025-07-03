#ifndef I_MEAL_PLANNER_H
#define I_MEAL_PLANNER_H

#include <vector>
#include <optional>
#include "core/Recipe.h"
#include "core/UserProfile.h"
#include "core/MealPlan.h"

namespace mealplanner::application {
    /**
     * @brief Interface for meal plan generation strategies.
     *
     * Implementations of this interface generate meal plans based on a set of recipes and user profile data.
     * This abstraction allows for different planning algorithms or business rules to be swapped in easily.
     */
    class IMealPlanner {
    public:
        /**
         * @brief Virtual destructor for interface.
         */
        virtual ~IMealPlanner() = default;

        /**
         * @brief Generate a meal plan for a user from a set of recipes.
         * @param recipes The list of available recipes to choose from.
         * @param user The user profile containing preferences, restrictions, and health data.
         * @return An optional MealPlanl std::nullopt if no valid plan can be generated.
         */
        virtual std::optional<model::MealPlan> generateMealPlan(const std::vector<model::Recipe>& recipes, const model::UserProfile& user) = 0;
    };
}

#endif // I_MEAL_PLANNER_H