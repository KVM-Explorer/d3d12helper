#include "d3d12helper/DescroptorHeap.h"
#include "d3d12helper/Interface.h"
#include "d3d12helper/Meta.h"
#include "d3d12helper/StringHelper.h"
#include <cassert>
#include <d3d12.h>

using namespace d3d12helper;

DescriptorHeap::DescriptorHeap(ID3D12Device *device, D3D12_DESCRIPTOR_HEAP_TYPE type, UINT descriptorNum, bool isShaderVisiable) :
    mDescriptorSize(device->GetDescriptorHandleIncrementSize(type)),
    mDescriptorMaxNum(descriptorNum),
    mIsShaderVisiable(isShaderVisiable),
    mDevice(device)
{
    D3D12_DESCRIPTOR_HEAP_DESC heapDesc = {};
    heapDesc.NumDescriptors = descriptorNum;
    heapDesc.Type = type;
    heapDesc.Flags = isShaderVisiable ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
    heapDesc.NodeMask = 0;

    if (isShaderVisiable) {
        mHeapNum = FrameResourceMaxNum;
    }
    for (uint32_t i = 0; i < mHeapNum; i++) {
        mDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&mInstance[i].mHeap));
        mInstance[i].CPUBaseHandle = CD3DX12_CPU_DESCRIPTOR_HANDLE(mInstance[i].mHeap->GetCPUDescriptorHandleForHeapStart());
        if (isShaderVisiable)
            mInstance[i].GPUBaseHandle = CD3DX12_GPU_DESCRIPTOR_HANDLE(mInstance[i].mHeap->GetGPUDescriptorHandleForHeapStart());
        else
            mInstance[i].GPUBaseHandle.ptr = 0;

        int heapType = static_cast<int>(type);
        std::string name = std::string("DescriptorHeap") + "_" + std::to_string(heapType) + "_" + std::to_string(i);

        mInstance[i].mHeap->SetName(string2wstring(name).c_str());
    }
}

uint32_t RTVHeap::AddPersistent(ID3D12Resource *resource, D3D12_RENDER_TARGET_VIEW_DESC *rtvDesc)
{
    assert(mPersistentNum < mDescriptorMaxNum);

    D3D12_RENDER_TARGET_VIEW_DESC desc;
    if (rtvDesc == nullptr) {
        desc.Format = resource->GetDesc().Format;
        desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipSlice = 0;
        desc.Texture2D.PlaneSlice = 0;
    } else {
        desc = *rtvDesc;
    }
    auto cpuHandle = CPUHandle(mPersistentNum);
    mDevice->CreateRenderTargetView(resource, &desc, cpuHandle);
    return mPersistentNum++;
}

uint32_t DSVHeap::AddPersistent(ID3D12Resource *resource, D3D12_DEPTH_STENCIL_VIEW_DESC *dsvDesc)
{
    assert(mPersistentNum < mDescriptorMaxNum);

    D3D12_DEPTH_STENCIL_VIEW_DESC desc;
    if (dsvDesc == nullptr) {
        desc.Format = resource->GetDesc().Format;
        desc.ViewDimension = D3D12_DSV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipSlice = 0;
        desc.Flags = D3D12_DSV_FLAG_NONE;
    } else {
        desc = *dsvDesc;
    }
    auto cpuHandle = CPUHandle(mPersistentNum);
    mDevice->CreateDepthStencilView(resource, &desc, cpuHandle);
    return mPersistentNum++;
}

SRVHeap::SRVHeap(ID3D12Device *device, UINT descriptorMaxNum, bool isShaderVisiable) :
    DescriptorHeap(device, D3D12_DESCRIPTOR_HEAP_TYPE_CBV_SRV_UAV, descriptorMaxNum, isShaderVisiable)
{
    assert(mMaxTemporaryNum <= descriptorMaxNum);
}
uint32_t SRVHeap::AddPersistent(ID3D12Resource *resource, D3D12_SHADER_RESOURCE_VIEW_DESC *srvDesc)
{
    assert(mPersistentNum < mDescriptorMaxNum - mMaxTemporaryNum);

    D3D12_SHADER_RESOURCE_VIEW_DESC desc;
    if (srvDesc == nullptr) {
        desc.Format = resource->GetDesc().Format;
        desc.ViewDimension = D3D12_SRV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipLevels = 1;
        desc.Texture2D.MostDetailedMip = 0;
        desc.Texture2D.PlaneSlice = 0;
        desc.Texture2D.ResourceMinLODClamp = 0.0f;
        desc.Shader4ComponentMapping = D3D12_DEFAULT_SHADER_4_COMPONENT_MAPPING;
    } else {
        desc = *srvDesc;
    }
    for (int i = 0; i < mHeapNum; i++) {
        auto cpuHandle = CPUHandle(i, mPersistentNum);
        mDevice->CreateShaderResourceView(resource, &desc, cpuHandle);
    }

    return mPersistentNum++;
}

uint32_t UAVHeap::AddPersistent(ID3D12Resource *resource, D3D12_UNORDERED_ACCESS_VIEW_DESC *uavDesc)
{
    assert(mPersistentNum < mDescriptorMaxNum);

    D3D12_UNORDERED_ACCESS_VIEW_DESC desc;
    if (uavDesc == nullptr) {
        desc.Format = resource->GetDesc().Format;
        desc.ViewDimension = D3D12_UAV_DIMENSION_TEXTURE2D;
        desc.Texture2D.MipSlice = 0;
        desc.Texture2D.PlaneSlice = 0;
    } else {
        desc = *uavDesc;
    }
    auto cpuHandle = CPUHandle(mPersistentNum);
    mDevice->CreateUnorderedAccessView(resource, nullptr, &desc, cpuHandle);
    return mPersistentNum++;
}

void SRVHeap::ResetTempDescriptors()
{
    mTempDescriptorIndex[mCurrentIndex] = 0;
}

TempDescriptorAllocation SRVHeap::AllocTempDescriptors(uint32_t num)
{
    assert(mTempDescriptorIndex[mCurrentIndex] + num <= mPersistentNum);

    TempDescriptorAllocation ret;
    auto curIndex = mTempDescriptorIndex[mCurrentIndex] + mPersistentNum;

    ret.Index = curIndex;
    ret.CPUHandle = CPUHandle(curIndex);
    ret.GPUHandle = GPUHandle(curIndex);

    mTempDescriptorIndex[mCurrentIndex] += num;
    return ret;
}