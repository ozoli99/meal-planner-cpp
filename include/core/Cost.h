#ifndef COST_H
#define COST_H

#include <string>

namespace mealplanner::model {
    /// Monetary cost with explicit currency code
    struct Cost {
        double value = 0.0;   ///< Numeric cost
        std::string currency; ///< ISO currency, e.g. "EUR", "USD"
    };
}

#endif // COST_H