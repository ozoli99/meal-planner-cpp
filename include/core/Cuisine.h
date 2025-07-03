#ifndef CUISINE_H
#define CUISINE_H

#include <optional>
#include <string>

namespace mealplanner::model {
    enum class Cuisine {
        American,
        Italian,
        Japanese,
        Other
    };

    inline std::optional<Cuisine> cuisineFromString(const std::string& str) {
        if (str == "American") {
            return Cuisine::American;
        }
        if (str == "Italian") {
            return Cuisine::Italian;
        }
        if (str == "Japanese") {
            return Cuisine::Japanese;
        }
        return Cuisine::Other;
    }
}

#endif // CUISINE_H