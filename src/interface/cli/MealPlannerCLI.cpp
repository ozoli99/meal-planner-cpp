#include "interface/cli/MealPlannerCLI.h"
#include "interface/presenter/MealPlanPresenter.h"
#include "infrastructure/JsonDataLoader.h"
#include <iostream>

MealPlannerCLI::MealPlannerCLI(IRecipeRepository& recipeRepository, IMealPlanner& planner)
    : m_recipeRepository(recipeRepository)
    , m_planner(planner) {}

void MealPlannerCLI::run(const std::string& userFile, const std::string& recipeFile, const std::string& planType, bool verbose, const std::string& outputPath, const std::string& format) {
    try {
        UserProfile user = m_recipeRepository.loadUserProfile(userFile);
        std::vector<Recipe> recipes = m_recipeRepository.loadRecipes(recipeFile);

        if (verbose) {
            std::cout << "✅ Loaded " << recipes.size() << " recipes.\n";
            std::cout << "👤 User: " << user.name << " (" << user.calorieTarget << " kcal target)\n";
        }

        MealPlan plan = m_planner.generateMealPlan(recipes, user);

        MealPlanPresenter::PrintToConsole(plan, format, verbose);

        if (!outputPath.empty()) {
            MealPlanPresenter::ExportToFile(plan, outputPath, format, verbose);
            std::cout << "📄 Meal plan exported to " << outputPath << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
