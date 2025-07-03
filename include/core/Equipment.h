#ifndef EQUIPMENT_H
#define EQUIPMENT_H

#include <string>

namespace mealplanner::model {
    /// @brief Single piece of equipment, possibly optional
    struct Equipment {
        std::string name;
        bool optional = false;
    };
}

#endif // EQUIPMENT_H