#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

namespace mealplanner::model {
    /**
     * @brief Single piece of equipment, possibly optional.
     * @details Immutable, type-safe representation of a kitchen equipment item.
     */
    struct Equipment {
        std::string name;
        bool optional;

        Equipment(std::string name_, bool optional_ = false)
            : name(std::move(name_))
            , optional(optional_) {
            if (name.empty()) {
                throw std::invalid_argument("Equipment name cannot be empty");
            }
        }

        bool operator==(const Equipment& other) const {
            return name == other.name && optional == other.optional;
        }
    };
}

#endif // EQUIPMENT_H