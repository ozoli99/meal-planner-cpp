#include "interface/cli/MealPlannerCLI.h"
#include "interface/presenter/MealPlanPresenter.h"
#include "infrastructure/JsonDataLoader.h"
#include <iostream>
#include <stdexcept>
#include "util/DataValidation.h"

using namespace mealplanner::model;
using namespace mealplanner::application;
using namespace mealplanner::infrastructure;

MealPlannerCLI::MealPlannerCLI(IRecipeRepository& recipeRepository, IMealPlanner& planner)
    : m_recipeRepository(recipeRepository)
    , m_planner(planner) {}

void MealPlannerCLI::run(const std::string& userFile, const std::string& recipeFile, const std::string& planType, bool verbose, const std::string& outputPath, const std::string& format) {
    try {
        if (planType != "balanced") {
            throw std::runtime_error("Only 'balanced' plan is supported for now");
        }

        UserProfile user;
        try {
            user = m_recipeRepository.loadUserProfile(userFile);
        } catch (const std::exception& e) {
            std::cerr << "❌ Failed to load user profile: " << e.what() << "\n";
            return;
        }
        auto userErrors = mealplanner::util::validateUserProfile(user);
        if (!userErrors.empty()) {
            std::cerr << "❌ Invalid user profile:" << std::endl;
            for (const auto& err : userErrors) {
                std::cerr << "  - " << err << std::endl;
            }
            return;
        }

        std::vector<Recipe> recipes;
        try {
            recipes = m_recipeRepository.loadRecipes(recipeFile);
        } catch (const std::exception& e) {
            std::cerr << "❌ Failed to load recipes: " << e.what() << "\n";
            return;
        }
        bool anyRecipeInvalid = false;
        for (const auto& recipe : recipes) {
            auto errs = mealplanner::util::validateRecipe(recipe);
            if (!errs.empty()) {
                if (!anyRecipeInvalid) {
                    std::cerr << "❌ Invalid recipes found:" << std::endl;
                    anyRecipeInvalid = true;
                }
                std::cerr << "  - Recipe '" << recipe.name << "' (id: " << recipe.id << "):" << std::endl;
                for (const auto& err : errs) {
                    std::cerr << "      * " << err << std::endl;
                }
            }
        }
        if (anyRecipeInvalid) {
            return;
        }

        if (verbose) {
            std::cout << "✅ Loaded " << recipes.size() << " recipes.\n";
            std::cout << "👤 User: " << user.name << " (" << user.calorieTarget << " kcal target)\n";
        }

        auto planOpt = m_planner.generateMealPlan(recipes, user);
        if (planOpt) {
            const MealPlan& plan = *planOpt;
            MealPlanPresenter::PrintToConsole(plan, format, verbose);
            if (!outputPath.empty()) {
                MealPlanPresenter::ExportToFile(plan, outputPath, format, verbose);
                std::cout << "📄 Meal plan exported to " << outputPath << "\n";
            }
        } else {
            std::cerr << "❌ Could not generate a valid meal plan for the given user and recipes.\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
