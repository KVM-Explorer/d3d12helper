#pragma once
#include "d3dx12.h"
#include <d3d12.h>
#include "Utils.h"

namespace d3d12helper {
class DescriptorHeap {
public:
    DescriptorHeap(const DescriptorHeap &) = delete;
    DescriptorHeap(DescriptorHeap &&) = default;
    DescriptorHeap &operator=(const DescriptorHeap &) = delete;
    DescriptorHeap &operator=(DescriptorHeap &&) = default;

    DescriptorHeap(ID3D12Device *device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorNum, bool isShaderVisiable = false);
    UINT Length() const { return mDescriptorNum; }

    CD3DX12_CPU_DESCRIPTOR_HANDLE
    CPUHandle(int index)
    {
        return CD3DX12_CPU_DESCRIPTOR_HANDLE(mCPUHandle, index, mDescriptorSize);};
    CD3DX12_GPU_DESCRIPTOR_HANDLE GPUHandle(int index) { return CD3DX12_GPU_DESCRIPTOR_HANDLE(mGPUHandle, index, mDescriptorSize); };

    [[nodiscard]] ID3D12DescriptorHeap *Resource() const { return mHeap.Get(); }

    uint32_t AddRtvDescriptor(ID3D12Device *device, ID3D12Resource *resource, D3D12_RENDER_TARGET_VIEW_DESC *rtvDesc = nullptr);
    uint32_t AddDsvDescriptor(ID3D12Device *device, ID3D12Resource *resource, D3D12_DEPTH_STENCIL_VIEW_DESC *srvDesc = nullptr);
    uint32_t AddSrvDescriptor(ID3D12Device *device, ID3D12Resource *resource, D3D12_SHADER_RESOURCE_VIEW_DESC *srvDesc = nullptr);
    uint32_t AddUavDescriptor(ID3D12Device *device, ID3D12Resource *resource, D3D12_UNORDERED_ACCESS_VIEW_DESC *uavDesc = nullptr);

private:
    Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> mHeap;
    UINT mDescriptorNum = 0;
    UINT mDescriptorSize;
    CD3DX12_CPU_DESCRIPTOR_HANDLE mCPUHandle;
    CD3DX12_GPU_DESCRIPTOR_HANDLE mGPUHandle;
};
}