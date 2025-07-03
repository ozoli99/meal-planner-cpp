#ifndef JSON_MEAL_PLAN_FORMATTER_H
#define JSON_MEAL_PLAN_FORMATTER_H

#include "IMealPlanFormatter.h"

class JsonMealPlanFormatter : public IMealPlanFormatter {
public:
    std::string format(const mealplanner::model::MealPlan& plan, bool verbose = false) const override;
};

#endif // JSON_MEAL_PLAN_FORMATTER_H
