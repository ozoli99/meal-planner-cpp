#ifndef MEAL_PLAN_PRESENTER_H
#define MEAL_PLAN_PRESENTER_H

#include "core/MealPlan.h"
#include <string>
#include <memory>
#include "IMealPlanFormatter.h"

class MealPlanPresenter {
public:
    static void PrintToConsole(const MealPlan& plan, const std::string& format = "text", bool verbose = false);
    static void ExportToFile(const MealPlan& plan, const std::string& path, const std::string& format = "text", bool verbose = false);

private:
    static std::unique_ptr<IMealPlanFormatter> createFormatter(const std::string& format = "text");
};

#endif // MEAL_PLAN_PRESENTER_H
