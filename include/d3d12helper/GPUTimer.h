//*********************************************************
//
// Copyright 2020 Intel Corporation
//
// Permission is hereby granted, free of charge, to any
// person obtaining a copy of this software and associated
// documentation files(the "Software"), to deal in the Software
// without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense,
// and/or sell copies of the Software, and to permit persons to
// whom the Software is furnished to do so, subject to the
// following conditions :
// The above copyright notice and this permission notice shall
// be included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
// EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF
// MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
// NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
// HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
// WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//
//*********************************************************
#pragma once

#include <cstdint>
#include <vector>
#include <string>
#include <utility>

#include "d3dx12.h"
#include "Utils.h"
namespace d3d12helper {

/*
 * @brief Gpu Timer class
 * @details This class is used to measure the time taken by the GPU to execute a command list. so the begin & end must be
            called in the same command list   before command list close. Besides, the resolve all timers must be called
            after the command list is executed. The time is measured in seconds.
            这个类用于测量GPU执行命令列表所花费的时间，所以begin和end必须在同一个命令列表中调用，然后在命令列表关闭并提交执行完毕后调用ResolveAllTimers接口
            读取数据并回写到CPU端。时间单位是秒。
 *
 */
class D3D12GpuTimer {
public:
    D3D12GpuTimer(
        ID3D12Device *in_pDevice,             // required to create internal resources
        ID3D12CommandQueue *in_pCommandQueue, // required for frequency query
        std::uint32_t in_numTimers, std::uint32_t in_averageOver = 20);

    void SetTimerName(std::uint32_t in_index, const std::string &in_name);

    void BeginTimer(ID3D12GraphicsCommandList *in_pCommandList, std::uint32_t in_index);
    void EndTimer(ID3D12GraphicsCommandList *in_pCommandList, std::uint32_t in_index);

    void ResolveAllTimers(ID3D12GraphicsCommandList *in_pCommandList);

    typedef std::vector<std::pair<float, std::string>> TimeArray;
    const TimeArray &GetTimes() const
    {
        return m_times;
    }
    ~D3D12GpuTimer()
    {
        m_buffer = nullptr;
        m_heap = nullptr;
    };

private:
    std::uint32_t m_numTimers; // how many we expose. we need double to record begin + end
    std::uint32_t m_totalTimers;
    TimeArray m_times;
    std::uint64_t m_gpuFrequency;
    const std::uint32_t m_averageOver;

    Microsoft::WRL::ComPtr<ID3D12QueryHeap> m_heap;
    Microsoft::WRL::ComPtr<ID3D12Resource> m_buffer;
    Microsoft::WRL::ComPtr<ID3D12CommandQueue> m_commandQueue;
};

} // namespace d3d12helper