#ifndef UNIT_H
#define UNIT_H

#include <string>
#include <stdexcept>
#include <algorithm>

/**
 * @brief Supported units for ingredient measurement.
 */
enum class Unit {
    Gram,
    Milliliter,
    Tablespoon,
    Teaspoon,
    Piece,
    Unknown
};

inline std::string toString(Unit unit) {
    switch (unit) {
        case Unit::Gram: return "g";
        case Unit::Milliliter: return "ml";
        case Unit::Tablespoon: return "tbsp";
        case Unit::Teaspoon: return "tsp";
        case Unit::Piece: return "piece";
        default: return "unknown";
    }
}

inline Unit unitFromString(const std::string& s) {
    std::string lower = s;
    std::transform(lower.begin(), lower.end(), lower.begin(), ::tolower);
    if (lower == "g") return Unit::Gram;
    if (lower == "ml") return Unit::Milliliter;
    if (lower == "tbsp") return Unit::Tablespoon;
    if (lower == "tsp") return Unit::Teaspoon;
    if (lower == "piece") return Unit::Piece;
    return Unit::Unknown;
}

#endif // UNIT_H
