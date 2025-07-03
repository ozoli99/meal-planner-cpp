#ifndef MEAL_PLANNER_CLI_H
#define MEAL_PLANNER_CLI_H

#include <string>
#include "application/IMealPlanner.h"
#include "infrastructure/IRecipeRepository.h"
#include "core/MealPlan.h"
#include "core/UserProfile.h"

class MealPlannerCLI {
public:
    MealPlannerCLI(mealplanner::infrastructure::IRecipeRepository& recipeRepository, mealplanner::application::IMealPlanner& planner);
    void run(const std::string& userFile, const std::string& recipesFile, const std::string& planType = "balanced", bool verbose = false, const std::string& outputPath = "", const std::string& format = "text");
    
private:
    mealplanner::infrastructure::IRecipeRepository& m_recipeRepository;
    mealplanner::application::IMealPlanner& m_planner;
};

#endif // MEAL_PLANNER_CLI_H