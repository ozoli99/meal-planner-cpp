#ifndef CUISINE_H
#define CUISINE_H

#include <optional>
#include <string>

namespace mealplanner::model {
    enum class Cuisine {
        American,
        Italian,
        Japanese,
        French,
        Chinese,
        Indian,
        Mexican,
        Mediterranean,
        Thai,
        Other,
        Unknown
    };

    inline std::string toString(Cuisine cuisine) {
        switch (cuisine) {
            case Cuisine::American: return "American";
            case Cuisine::Italian: return "Italian";
            case Cuisine::Japanese: return "Japanese";
            case Cuisine::French: return "French";
            case Cuisine::Chinese: return "Chinese";
            case Cuisine::Indian: return "Indian";
            case Cuisine::Mexican: return "Mexican";
            case Cuisine::Mediterranean: return "Mediterranean";
            case Cuisine::Thai: return "Thai";
            case Cuisine::Other: return "Other";
            default: return "Unknown";
        }
    }

    inline Cuisine cuisineFromString(const std::string& str) {
        std::string lower;
        lower.reserve(str.size());
        for (char c : str) {
            lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        if (lower == "american") return Cuisine::American;
        if (lower == "italian") return Cuisine::Italian;
        if (lower == "japanese") return Cuisine::Japanese;
        if (lower == "french") return Cuisine::French;
        if (lower == "chinese") return Cuisine::Chinese;
        if (lower == "indian") return Cuisine::Indian;
        if (lower == "mexican") return Cuisine::Mexican;
        if (lower == "mediterranean") return Cuisine::Mediterranean;
        if (lower == "thai") return Cuisine::Thai;
        if (lower == "other") return Cuisine::Other;
        return Cuisine::Unknown;
    }

    inline bool isKnownCuisine(const std::string& str) {
        Cuisine cuisine = cuisineFromString(str);
        return cuisine != Cuisine::Unknown;
    }
}

#endif // CUISINE_H