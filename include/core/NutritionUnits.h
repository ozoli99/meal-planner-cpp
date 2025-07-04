#ifndef NUTRITION_UNITS_H
#define NUTRITION_UNITS_H

#include <stdexcept>
#include <ostream>

namespace mealplanner::model {
    struct Calories {
        int value;
        explicit Calories(int v)
            : value(v) {
            if (v < 0) {
                throw std::invalid_argument("Calories must be >= 0");
            }
        }
        operator int() const { return value; }
    };
    inline std::ostream& operator<<(std::ostream& os, const Calories& calories) { return os << calories.value; }
    inline Calories operator+(const Calories& a, const Calories& b) {
        return Calories{ a.value + b.value };
    }
    inline Calories& operator+=(Calories& a, const Calories& b) {
        a = a + b;
        return a;
    }

    struct Grams {
        int value;
        explicit Grams(int v)
            : value(v) {
            if (v < 0) {
                throw std::invalid_argument("Grams must be >= 0");
            }
        }
        operator int() const { return value; }
    };
    inline std::ostream& operator<<(std::ostream& os, const Grams& grams) { return os << grams.value; }
    inline Grams operator+(const Grams& a, const Grams& b) {
        return Grams{ a.value + b.value };
    }
    inline Grams& operator+=(Grams& a, const Grams& b) {
        a = a + b;
        return a;
    }

    struct Servings {
        int value;
        explicit Servings(int v)
            : value(v) {
            if (v <= 0) {
                throw std::invalid_argument("Servings must be > 0");
            }
        }
        operator int() const { return value; }
    };
    inline std::ostream& operator<<(std::ostream& os, const Servings& servings) { return os << servings.value; }
}

#endif // NUTRITION_UNITS_H
