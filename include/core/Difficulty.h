#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <optional>
#include <string>

namespace mealplanner::model {
    enum class Difficulty {
        Easy,
        Intermediate,
        Hard
    };

    inline std::optional<Difficulty> difficultyFromString(const std::string& str) {
        if (str == "easy") {
            return Difficulty::Easy;
        }
        if (str == "intermediate") {
            return Difficulty::Intermediate;
        }
        if (str == "hard") {
            return Difficulty::Hard;
        }
        return std::nullopt;
    }
}

#endif // DIFFICULTY_H