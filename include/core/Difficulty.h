#ifndef DIFFICULTY_H
#define DIFFICULTY_H

#include <optional>
#include <string>

namespace mealplanner::model {
    enum class Difficulty {
        Easy,
        Intermediate,
        Hard,
        Unknown
    };

    inline std::string toString(Difficulty difficulty) {
        switch (difficulty) {
            case Difficulty::Easy: return "easy";
            case Difficulty::Intermediate: return "intermediate";
            case Difficulty::Hard: return "hard";
            default: return "unknown";
        }
    }

    inline Difficulty difficultyFromString(const std::string& str) {
        std::string lower;
        lower.reserve(str.size());
        for (char c : str) {
            lower += static_cast<char>(std::tolower(static_cast<unsigned char>(c)));
        }
        if (lower == "easy") return Difficulty::Easy;
        if (lower == "intermediate") return Difficulty::Intermediate;
        if (lower == "hard") return Difficulty::Hard;
        return Difficulty::Unknown;
    }

    inline bool isKnownDifficulty(const std::string& str) {
        return difficultyFromString(str) != Difficulty::Unknown;
    }
}

#endif // DIFFICULTY_H