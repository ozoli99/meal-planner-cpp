#ifndef MACRO_RATIOS_H
#define MACRO_RATIOS_H

namespace mealplanner::model {
    /// @brief Protein / carb / fat relative ratios
    struct MacroRatios {
        double protein = 0.0;
        double carbs = 0.0;
        double fat = 0.0;
    };
}

#endif // MACRO_RATIOS_H
