#ifndef MEAL_PLANNER_CLI_H
#define MEAL_PLANNER_CLI_H

#include <string>
#include "application/IMealPlanner.h"
#include "infrastructure/IRecipeRepository.h"
#include "core/MealPlan.h"
#include "core/UserProfile.h"

class MealPlannerCLI {
public:
    MealPlannerCLI(IRecipeRepository& recipeRepository, IMealPlanner& planner);
    void run(const std::string& userFile, const std::string& recipesFile, const std::string& planType = "balanced", bool verbose = false, const std::string& outputPath = "", const std::string& format = "text");
    
private:
    void printMealPlan(const MealPlan& plan, const std::string& title, bool verbose = false, const std::string& format = "text");
    void exportMealPlan(const MealPlan& plan, const std::string& path);
    void exportMealPlanJson(const MealPlan& plan, const std::string& path);

    IRecipeRepository& m_recipeRepository;
    IMealPlanner& m_planner;
};

#endif // MEAL_PLANNER_CLI_H