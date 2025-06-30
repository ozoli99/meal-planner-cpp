#ifndef MEAL_PLAN_PRESENTER_H
#define MEAL_PLAN_PRESENTER_H

#include "core/MealPlan.h"

class MealPlanPresenter {
public:
    static void printToConsole(const MealPlan& plan, const std::string& format = "text", bool verbose = false);
    static void exportToFile(const MealPlan& plan, const std::string& path, const std::string& format = "text", bool verbose = false);
};

#endif // MEAL_PLAN_PRESENTER_H
