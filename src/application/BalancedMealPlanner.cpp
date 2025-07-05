#include "application/BalancedMealPlanner.h"
#include "core/NutritionCalculator.h"
#include "core/NutritionUtils.h"

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

using namespace mealplanner::application;
using namespace mealplanner::model;

namespace {
    int countSetBits(int value) {
        int count = 0;
        while (value) {
            count += value & 1;
            value >>= 1;
        }
        return count;
    }
    
    bool recipeHasTag(const Recipe& recipe, const std::string& tag) {
        return std::find(recipe.tags.begin(), recipe.tags.end(), tag) != recipe.tags.end();
    }

    std::vector<std::vector<Recipe>> generateSnackCombinations(const std::vector<Recipe>& snacks, int slots) {
        std::vector<std::vector<Recipe>> combinations;

        int snackCount = static_cast<int>(snacks.size());
        int totalMasks = 1 << snackCount;

        for (int mask = 0; mask < totalMasks; ++mask) {
            if (countSetBits(mask) != slots) {
                continue;
            }

            std::vector<Recipe> combo;
            for (int i = 0; i < snackCount; ++i) {
                if (mask & (1 << i)) {
                    combo.push_back(snacks[i]);
                }
            }
            combinations.push_back(combo);
        }

        return combinations;
    }
} // namespace

BalancedMealPlanner::BalancedMealPlanner(const IngredientDatabase& ingredientDatabase)
    : m_ingredientDatabase(ingredientDatabase) {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

std::optional<MealPlan> BalancedMealPlanner::generateMealPlan(const std::vector<Recipe>& recipes, const UserProfile& user) {
    std::vector<Recipe> breakfastOptions;
    std::vector<Recipe> lunchOptions;
    std::vector<Recipe> dinnerOptions;
    std::vector<Recipe> snackOptions;

    for (const auto& recipe : recipes) {
        if (!NutritionUtils::isRecipeCompliant(recipe, user.dietaryRestrictions) || recipe.prepTime > user.maxPrepTime) {
            continue;
        }

        if (recipeHasTag(recipe, "breakfast")) {
            breakfastOptions.push_back(recipe);
        } else if (recipeHasTag(recipe, "lunch")) {
            lunchOptions.push_back(recipe);
        } else if (recipeHasTag(recipe, "dinner")) {
            dinnerOptions.push_back(recipe);
        } else if (recipeHasTag(recipe, "snack")) {
            snackOptions.push_back(recipe);
        }
    }

    if (breakfastOptions.empty()) {
        throw std::runtime_error("No breakfast recipes match your dietary restrictions and max prep time.");
    }
    if (lunchOptions.empty()) {
        throw std::runtime_error("No lunch recipes match your dietary restrictions and max prep time.");
    }
    if (dinnerOptions.empty()) {
        throw std::runtime_error("No dinner recipes match your dietary restrictions and max prep time.");
    }
    if (user.snackSlots > 0 && snackOptions.empty()) {
        throw std::runtime_error(std::string("User requested ") + std::to_string(user.snackSlots) + " snacks, but no compliant snack recipes were found.");
    }

    MealPlan bestPlan;
    double highestScore = -1e9;
    bool found = false;

    NutritionCalculator calculator(m_ingredientDatabase);

    for (const auto& breakfast : breakfastOptions) {
        for (const auto& lunch : lunchOptions) {
            for (const auto& dinner : dinnerOptions) {
                auto snackCombinations = (user.snackSlots > 0)
                    ? generateSnackCombinations(snackOptions, user.snackSlots)
                    : std::vector<std::vector<Recipe>>{{}};

                for (const auto& snackSet : snackCombinations) {
                    MealPlan candidatePlan;
                    candidatePlan.selectedRecipes = {breakfast, lunch, dinner};
                    candidatePlan.selectedRecipes.insert(candidatePlan.selectedRecipes.end(), snackSet.begin(), snackSet.end());

                    candidatePlan = calculator.computeMealPlanNutrition(candidatePlan);
                    double planScore = NutritionUtils::scorePlan(candidatePlan, user);

                    if (!found || planScore > highestScore) {
                        highestScore = planScore;
                        bestPlan = candidatePlan;
                        found = true;
                    }
                }
            }
        }
    }

    if (!found) {
        throw std::runtime_error("We tried every combination but couldn't hit your nutritional targets - try relaxing restrictions or adding more recipes.");
    }

    return bestPlan;
}
