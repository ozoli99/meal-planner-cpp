#ifndef I_MEAL_PLAN_FORMATTER_H
#define I_MEAL_PLAN_FORMATTER_H

#include <string>
#include "core/MealPlan.h"

class IMealPlanFormatter {
public:
    virtual ~IMealPlanFormatter() = default;

    virtual std::string format(const mealplanner::model::MealPlan& plan, bool verbose = false) const = 0;
};

#endif // I_MEAL_PLAN_FORMATTER_H