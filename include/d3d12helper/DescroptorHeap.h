#pragma once
#include "d3d12helper/DescroptorHeap.h"
#include "d3d12helper/Interface.h"
#include "d3d12helper/Meta.h"
#include "d3dx12.h"
#include <atomic>
#include <cassert>
#include <cstdint>
#include <d3d12.h>
#include "Utils.h"
#include <array>

namespace d3d12helper {

struct TempDescriptorAllocation {
    CD3DX12_CPU_DESCRIPTOR_HANDLE CPUHandle;
    CD3DX12_GPU_DESCRIPTOR_HANDLE GPUHandle;
    uint32_t Index;
};

struct DescriptorHeapInstance {
    ID3D12DescriptorHeapPtr mHeap;
    CD3DX12_CPU_DESCRIPTOR_HANDLE CPUBaseHandle;
    CD3DX12_GPU_DESCRIPTOR_HANDLE GPUBaseHandle;
};

class DescriptorHeap {
public:
    DescriptorHeap(const DescriptorHeap &) = delete;
    DescriptorHeap(DescriptorHeap &&) = default;
    DescriptorHeap &operator=(const DescriptorHeap &) = delete;
    DescriptorHeap &operator=(DescriptorHeap &&) = default;

    DescriptorHeap(ID3D12Device *device, D3D12_DESCRIPTOR_HEAP_TYPE heapType, uint32_t descriptorNum, bool isShaderVisiable = false);
    uint32 PersistentLength() const { return mPersistentNum; }

    ID3D12DescriptorHeap *Heap() { return mInstance[mCurrentIndex].mHeap.Get(); }
    CD3DX12_CPU_DESCRIPTOR_HANDLE CPUHandle(uint32_t index)
    {
        return CD3DX12_CPU_DESCRIPTOR_HANDLE(mInstance[mCurrentIndex].CPUBaseHandle, index, mDescriptorSize);
    }

    CD3DX12_GPU_DESCRIPTOR_HANDLE GPUHandle(uint32_t index)
    {
        assert(mIsShaderVisiable);
        return CD3DX12_GPU_DESCRIPTOR_HANDLE(mInstance[mCurrentIndex].GPUBaseHandle, index, mDescriptorSize);
    }

    ID3D12DescriptorHeap *Heap() const { return mInstance[mCurrentIndex].mHeap.Get(); }
    void MoveToNextFrame() { mCurrentIndex = (mCurrentIndex + 1) % mHeapNum; }

protected:
    CD3DX12_CPU_DESCRIPTOR_HANDLE CPUHandle(uint32_t heapIndex, uint32_t index)
    {
        assert(mIsShaderVisiable);
        return CD3DX12_CPU_DESCRIPTOR_HANDLE(mInstance[heapIndex].CPUBaseHandle, index, mDescriptorSize);
    }

    uint32_t mPersistentNum = 0;
    const uint32_t mDescriptorMaxNum;
    const uint32_t mDescriptorSize;
    uint32_t mCurrentIndex = 0;
    uint32_t mHeapNum = 1;
    bool mIsShaderVisiable = false;
    ID3D12Device *mDevice;
    DescriptorHeapInstance mInstance[FrameResourceMaxNum];
};

class RTVHeap : public DescriptorHeap {
public:
    RTVHeap(ID3D12Device *device, UINT descriptorMaxNum, bool isShaderVisiable = false) :
        DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_RTV, descriptorMaxNum, isShaderVisiable) {}
    uint32 AddPersistent(ID3D12Resource *resource, D3D12_RENDER_TARGET_VIEW_DESC *rtvDesc = nullptr);
};

class DSVHeap : public DescriptorHeap {
public:
    DSVHeap(ID3D12Device *device, UINT descriptorMaxNum, bool isShaderVisiable = false) :
        DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_DSV, descriptorMaxNum, isShaderVisiable) {}
    uint32 AddPersistent(ID3D12Resource *resource, D3D12_DEPTH_STENCIL_VIEW_DESC *dsvDesc = nullptr);
};

class SRVHeap : public DescriptorHeap {
public:
    SRVHeap(ID3D12Device *device, UINT descriptorMaxNum, bool isShaderVisiable = false);
    uint32 AddPersistent(ID3D12Resource *resource, D3D12_SHADER_RESOURCE_VIEW_DESC *srvDesc = nullptr);
    TempDescriptorAllocation AllocTempDescriptors(uint32_t num);
    void ResetTempDescriptors();

private:
    static const uint32_t mMaxTemporaryNum = 128;
    uint32_t mTempDescriptorIndex[FrameResourceMaxNum];
};

class UAVHeap : public DescriptorHeap {
public:
    UAVHeap(ID3D12Device *device, UINT descriptorMaxNum, bool isShaderVisiable = false) :
        DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorMaxNum, isShaderVisiable) {}
    uint32 AddPersistent(ID3D12Resource *resource, D3D12_UNORDERED_ACCESS_VIEW_DESC *uavDesc = nullptr);
};
} // namespace d3d12helper