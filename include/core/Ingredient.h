#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Quantity.h"

namespace mealplanner::model {
    /**
     * @brief Represents an ingredient used in a specific recipe (with quantity and optional note).
     */
    struct Ingredient {
        std::string name;      ///< Ingredient name to match database.
        Quantity quantity;     ///< Amount to use.
        bool optional = false; ///< If true, this ingredient can be skipped.
    };
}

#endif // INGREDIENT_H