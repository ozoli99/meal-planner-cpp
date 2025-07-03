#ifndef TIME_H
#define TIME_H

#include <chrono>

namespace mealplanner::model {
    /// Explicit minute type for prep / cook / rest times
    using Minutes = std::chrono::minutes;
}

#endif // TIME_H