#ifndef TEXT_MEAL_PLAN_FORMATTER_H
#define TEXT_MEAL_PLAN_FORMATTER_H

#include "IMealPlanFormatter.h"

class TextMealPlanFormatter : public IMealPlanFormatter {
public:
    std::string format(const mealplanner::model::MealPlan& plan, bool verbose = false) const override;
};

#endif // TEXT_MEAL_PLAN_FORMATTER_H