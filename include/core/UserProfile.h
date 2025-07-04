#ifndef USER_PROFILE_H
#define USER_PROFILE_H

#include <vector>
#include <string>
#include <stdexcept>
#include "Time.h"
#include "MacroRatios.h"

namespace mealplanner::model {
    struct UserProfile {
        std::string name;
        int calorieTarget;
        int mealsPerDay;
        int snackSlots;
        Minutes maxPrepTime;
        MacroRatios macroRatios;
        std::vector<std::string> dietaryRestrictions;

        UserProfile(std::string name_, int calorieTarget_, int mealsPerDay_ = 3, int snackSlots_ = 1, Minutes maxPrepTime_ = Minutes{30}, MacroRatios macroRatios_ = MacroRatios{}, std::vector<std::string> dietaryRestrictions_ = {})
            : name(std::move(name_))
            , calorieTarget(calorieTarget_)
            , mealsPerDay(mealsPerDay_)
            , snackSlots(snackSlots_)
            , maxPrepTime(maxPrepTime_)
            , macroRatios(macroRatios_)
            , dietaryRestrictions(std::move(dietaryRestrictions_)) {
            if (name.empty()) {
                throw std::invalid_argument("UserProfile needs name");
            }
            if (calorieTarget <= 0) {
                throw std::invalid_argument("calorieTarget > 0");
            }
            if (mealsPerDay <= 0) {
                throw std::invalid_argument("mealsPerDay > 0");
            }
            if (snackSlots < 0) {
                throw std::invalid_argument("snackSlots >= 0");
            }
            if (maxPrepTime.count() < 0) {
                throw std::invalid_argument("maxPrepTime >= 0");
            }
        }

        // Remove default constructor to enforce valid construction
        UserProfile() = default;
    };
}

#endif // USER_PROFILE_H