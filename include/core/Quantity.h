#ifndef QUANTITY_H
#define QUANTITY_H

#include <string>

namespace mealplanner::model {
    /// @brief Represents an amount + unit + fallback note (e.g. "to taste")
    struct Quantity {
        double amount = 0.0; ///< Numeric amount (0 if none)
        std::string unit;    ///< e.g. "g", "ml", "piece"
        std::string note;    ///< e.g. "to taste" or prep hint

        bool operator==(const Quantity& other) const {
            return amount == other.amount && unit == other.unit && note == other.note;
        }
    };
}

#endif // QUANTITY_H