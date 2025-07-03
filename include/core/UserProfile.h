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
        int calorieTarget = 2000;
        int mealsPerDay = 3;
        int snackSlots = 1;
        Minutes maxPrepTime = Minutes{30};
        MacroRatios macroRatios;
        std::vector<std::string> dietaryRestrictions;

        UserProfile(std::string name_, int calorieTarget_)
            : name(std::move(name_)), calorieTarget(calorieTarget_) {
            if (name.empty()) {
                throw std::invalid_argument("UserProfile needs name");
            }
            if (calorieTarget <= 0) {
                throw std::invalid_argument("calorieTarget > 0");
            }
        }
        UserProfile() = default;
    };
}

#endif // USER_PROFILE_H