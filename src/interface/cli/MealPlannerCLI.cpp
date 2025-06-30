#include "interface/cli/MealPlannerCLI.h"
#include "interface/presenter/MealPlanPresenter.h"
#include "infrastructure/JsonDataLoader.h"
#include <iostream>

MealPlannerCLI::MealPlannerCLI(IRecipeRepository& recipeRepository, IMealPlanner& planner)
    : m_recipeRepository(recipeRepository)
    , m_planner(planner) {}

void MealPlannerCLI::run(const std::string& userFile, const std::string& recipeFile, const std::string& planType, bool verbose, const std::string& outputPath, const std::string& format) {
    if (userFile == "--help" || recipeFile == "--help" || planType == "--help" || outputPath == "--help") {
        std::cout << "📘 Meal Planner CLI Usage:\n";
        std::cout << "  mealplanner.exe --user <user.json> --recipes <recipes.json> [--plan <type>] [--verbose true|false] [--output <path>]\n\n";
        std::cout << "Options:\n";
        std::cout << "  --user       Path to user profile JSON file.\n";
        std::cout << "  --recipes    Path to recipes JSON file.\n";
        std::cout << "  --plan       Planning strategy (default: balanced).\n";
        std::cout << "  --verbose    Show detailed output (default: false).\n";
        std::cout << "  --output     Export the result to a file.\n";
        std::cout << "  --help       Show this help message.\n";
        return;
    }

    try {
        UserProfile user = m_recipeRepository.loadUserProfile(userFile);
        std::vector<Recipe> recipes = m_recipeRepository.loadRecipes(recipeFile);

        if (verbose) {
            std::cout << "✅ Loaded " << recipes.size() << " recipes.\n";
            std::cout << "👤 User: " << user.name << " (" << user.calorieTarget << " kcal target)\n";
        }

        MealPlan plan = m_planner.generateMealPlan(recipes, user);

        MealPlanPresenter::printToConsole(plan, format, verbose);

        if (!outputPath.empty()) {
            MealPlanPresenter::exportToFile(plan, outputPath, format, verbose);
            std::cout << "📄 Meal plan exported to " << outputPath << "\n";
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
}
