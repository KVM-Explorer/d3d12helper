#pragma once
#include <chrono>
#include <string>
#include <unordered_map>
#include <queue>

namespace d3d12helper {
using TimePoint = std::chrono::high_resolution_clock::time_point;
class CPUTimer {
public:
    CPUTimer() = default;
    CPUTimer(const CPUTimer &) = default;
    CPUTimer &operator=(const CPUTimer &) = default;
    CPUTimer(CPUTimer &&) = delete;
    CPUTimer &operator=(CPUTimer &&) = delete;

    uint32_t GetStaticTimeDuration(std::string name, TimePoint time);
    void SetStaticTime(std::string name, TimePoint time);
    void BeginTimer(std::string name);
    void EndTimer(std::string name);
    void UpdateTimer(std::string name);
    void UpdateAvgTimer(std::string name);
    uint32_t QueryDuration(std::string name);
    // ms
    std::unordered_map<std::string, uint32_t> GetAllTimer();

private:
    std::unordered_map<std::string, std::chrono::high_resolution_clock::time_point> mTimerPoints;
    std::unordered_map<std::string, uint32_t> mTimerState;
    std::unordered_map<std::string, uint32_t> mDuration;
    std::unordered_map<std::string, uint32_t> mTotalTime;
    std::unordered_map<std::string, std::queue<uint32_t>> mTimeQueue;
};
}
