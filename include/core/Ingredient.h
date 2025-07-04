#ifndef INGREDIENT_H
#define INGREDIENT_H

#include <string>
#include <vector>
#include <unordered_map>
#include "Quantity.h"

namespace mealplanner::model {
    /**
     * @brief Represents an ingredient used in a specific recipe (with quantity and optional note).
     * @details Immutable, type-safe representation of a recipe ingredient.
     */
    struct Ingredient {
        std::string name;      ///< Ingredient name to match database.
        Quantity quantity;     ///< Amount to use.
        bool optional;         ///< If true, this ingredient can be skipped.

        Ingredient(std::string name_, Quantity quantity_, bool optional_ = false)
            : name(std::move(name_))
            , quantity(quantity_)
            , optional(optional_) {
            if (name.empty()) {
                throw std::invalid_argument("Ingredient name cannot be empty");
            }
        }

        bool operator==(const Ingredient& other) const {
            return name == other.name && quantity == other.quantity && optional == other.optional;
        }
    };
}

#endif // INGREDIENT_H