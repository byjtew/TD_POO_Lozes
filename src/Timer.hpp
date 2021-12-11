#pragma once

#include <unistd.h>

#include <chrono>
#include <ctime>
#include <utility>

using chrono_pt = std::chrono::time_point<std::chrono::high_resolution_clock>;

namespace timer {

class Timer {
   private:
    static chrono_pt get_zero_chrono_pt() {
        return std::chrono::high_resolution_clock::from_time_t(0);
    }
    static size_t chrono_pt_to_us(const chrono_pt &pt) {
        return std::chrono::duration_cast<std::chrono::microseconds>(
                   pt.time_since_epoch())
            .count();
    }

    std::pair<chrono_pt, chrono_pt> timepoints = {get_zero_chrono_pt(),
                                                  get_zero_chrono_pt()};

    chrono_pt get_current_time() const {
        return std::chrono::high_resolution_clock::now();
    }

   public:
    Timer();
    ~Timer();
    void start() { timepoints.first = get_current_time(); }

    void stop() { timepoints.second = get_current_time(); }

    size_t getStartTime() const { return chrono_pt_to_us(timepoints.first); }
    size_t getStopTime() const { return chrono_pt_to_us(timepoints.second); }
    size_t print() const { return getStopTime() - getStartTime(); }
};

}  // namespace timer
