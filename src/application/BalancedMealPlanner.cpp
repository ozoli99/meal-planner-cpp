#include "application/BalancedMealPlanner.h"
#include "core/NutritionUtils.h"
#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <stdexcept>

BalancedMealPlanner::BalancedMealPlanner() {
    std::srand(static_cast<unsigned int>(std::time(nullptr)));
}

MealPlan BalancedMealPlanner::generateMealPlan(const std::vector<Recipe>& allRecipes, const UserProfile& user) {
    std::vector<Recipe> breakfasts;
    std::vector<Recipe> lunches;
    std::vector<Recipe> dinners;
    std::vector<Recipe> snacks;

    for (const auto& r : allRecipes) {
        if (!NutritionUtils::isRecipeCompliant(r, user.dietaryRestrictions) || r.prepTimeMinutes > user.maxPrepTimeMinutes) {
            continue;
        }

        if (r.type == "breakfast") {
            breakfasts.push_back(r);
        } else if (r.type == "lunch") {
            lunches.push_back(r);
        } else if (r.type == "dinner") {
            dinners.push_back(r);
        } else if (r.type == "snack") {
            snacks.push_back(r);
        }
    }

    MealPlan bestPlan;
    double bestScore = -1e9;

    for (const auto& b : breakfasts) {
        for (const auto& l : lunches) {
            for (const auto& d : dinners) {
                std::vector<std::vector<Recipe>> snackCombos = {{}};

                if (user.snackSlots > 0 && !snacks.empty()) {
                    snackCombos.clear();
                    int n = snacks.size();
                    int limit = 1 << n;
                    for (int mask = 0; mask < limit; ++mask) {
                        if (__builtin_popcount(mask) != user.snackSlots) {
                            continue;
                        }
                        std::vector<Recipe> combo;
                        for (int i = 0; i < n; ++i) {
                            if (mask & (1 << i)) {
                                combo.push_back(snacks[i]);
                            }
                        }
                        snackCombos.push_back(combo);
                    }
                }

                for (const auto& snackSet : snackCombos) {
                    MealPlan candidate;
                    candidate.selectedRecipes = {b, l, d};
                    candidate.selectedRecipes.insert(candidate.selectedRecipes.end(), snackSet.begin(), snackSet.end());

                    candidate.totalKcal = 0;
                    candidate.totalProtein = 0;
                    candidate.totalCarbs = 0;
                    candidate.totalFats = 0;

                    for (auto& r : candidate.selectedRecipes) {
                        const auto rWithMacros = NutritionUtils::computeNutritionFromIngredients(r);
                        candidate.totalKcal += rWithMacros.kcal;
                        candidate.totalProtein += rWithMacros.protein;
                        candidate.totalCarbs += rWithMacros.carbs;
                        candidate.totalFats += rWithMacros.fat;
                    }

                    double score = NutritionUtils::scorePlan(candidate, user);
                    if (score > bestScore) {
                        bestScore = score;
                        bestPlan = candidate;
                    }
                }
            }
        }
    }

    return bestPlan;
}
