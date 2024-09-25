#include <thread>
#include <timeapi.h>
#include <chrono>

namespace d3d12helper {

/**
 * @brief 线程休眠
 *@details 在 Windows 10 版本 2004 前此函数可能影响整个系统，，现在仅影响当前进程
 */
// Win11 下各种sleep精度都不高，包括std::this_thread::sleep_for，Sleep，WaitForSingleObject等
inline void ThreadSleep(std::chrono::microseconds time)
{
    // 详情说明见 https://learn.microsoft.com/zh-cn/windows/win32/api/timeapi/nf-timeapi-timebeginperiod
    timeBeginPeriod(1); // set Minimum timer resolution. 精度为1ms，测试结果基本准确，不会出现明显的波动，看来主要和，
    std::this_thread::sleep_for(time);
    timeEndPeriod(1);

    // Sleep(time.count()); // 不准确 给定21ms 实际可能时28,23,29ms

    // WaitForSingleObject(CreateEvent(NULL, FALSE, FALSE, NULL), time.count()); // 不精确测试同Sleep
}
} // namespace d3d12helper