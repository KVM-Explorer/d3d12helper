#include "d3d12helper/GPUTimer.h"
// #include <iostream>
using namespace d3d12helper;

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
D3D12GpuTimer::D3D12GpuTimer(
    ID3D12Device *in_pDevice,
    ID3D12CommandQueue *in_pCommandQueue,
    std::uint32_t in_numTimers,
    std::uint32_t in_averageOver) :
    m_numTimers(in_numTimers),
    m_totalTimers(in_numTimers * 2) // begin + end, so we can take a difference
    ,
    m_gpuFrequency(0), m_averageOver(in_averageOver), m_commandQueue(in_pCommandQueue)
{
    m_times.resize(m_numTimers);

    const UINT64 bufferSize = m_totalTimers * sizeof(UINT64);

    const auto heapProps = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
    const auto resourceDesc = CD3DX12_RESOURCE_DESC::Buffer(bufferSize);

    ThrowIfFailed(in_pDevice->CreateCommittedResource(
        &heapProps,
        D3D12_HEAP_FLAG_NONE,
        &resourceDesc,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&m_buffer)));
    m_buffer->SetName(L"GPUTimeStamp Buffer");

    D3D12_QUERY_HEAP_DESC QueryHeapDesc = {};
    QueryHeapDesc.Type = D3D12_QUERY_HEAP_TYPE_TIMESTAMP;
    QueryHeapDesc.Count = m_totalTimers;

    ThrowIfFailed(in_pDevice->CreateQueryHeap(&QueryHeapDesc, IID_PPV_ARGS(&m_heap)));
    m_heap->SetName(L"GpuTimeStamp Direct QueryHeap");

    ThrowIfFailed(in_pCommandQueue->GetTimestampFrequency(&m_gpuFrequency));
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void D3D12GpuTimer::SetTimerName(std::uint32_t in_index, const std::string &in_name)
{
    if (in_index < m_times.size()) {
        m_times[in_index].second = in_name;
    }
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void D3D12GpuTimer::BeginTimer(ID3D12GraphicsCommandList *in_pCommandList, std::uint32_t in_index)
{
    const UINT index = in_index * 2;
    in_pCommandList->EndQuery(m_heap.Get(), D3D12_QUERY_TYPE_TIMESTAMP, index);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void D3D12GpuTimer::EndTimer(ID3D12GraphicsCommandList *in_pCommandList, std::uint32_t in_index)
{
    const UINT index = (in_index * 2) + 1;
    in_pCommandList->EndQuery(m_heap.Get(), D3D12_QUERY_TYPE_TIMESTAMP, index);
}

//-----------------------------------------------------------------------------
//-----------------------------------------------------------------------------
void D3D12GpuTimer::ResolveAllTimers(ID3D12GraphicsCommandList *in_pCommandList)
{
    in_pCommandList->ResolveQueryData(m_heap.Get(), D3D12_QUERY_TYPE_TIMESTAMP, 0, m_totalTimers, m_buffer.Get(), 0);
    // FIXME? gpu frequency can fluctuate over time. Does this query reflect current clock rate? according to the experiment, it fixed. but delta time is not fixed 
    // so delta time means the time between two timestamps,  not current frame time. it is the time last frame time
    d3d12helper::ThrowIfFailed(m_commandQueue->GetTimestampFrequency(&m_gpuFrequency));

    // std::cout << "GPU Frequency: " << m_gpuFrequency << std::endl;

    void *pData = nullptr;
    const auto range = CD3DX12_RANGE(0, m_totalTimers);
    d3d12helper::ThrowIfFailed(m_buffer->Map(0, &range, &pData));

    const UINT64 *pTimestamps = reinterpret_cast<UINT64 *>(pData);
    for (std::uint32_t i = 0; i < m_numTimers; i++) {
        UINT64 deltaTime = pTimestamps[1] - pTimestamps[0];
        if (pTimestamps[1] < pTimestamps[0]) {
            deltaTime = pTimestamps[0] - pTimestamps[1];
        }

        const float delta = float(deltaTime) / float(m_gpuFrequency);
        const float t = m_times[i].first * (m_averageOver - 1);
        m_times[i].first = (t + delta) / m_averageOver;
        // std::cout << "deltaTime: " << deltaTime << std::endl;
        pTimestamps += 2;
    }

    // Unmap with an empty range (written range).
    m_buffer->Unmap(0, nullptr);
}