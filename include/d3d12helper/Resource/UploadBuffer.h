#pragma once
#include "d3d12helper/Resource/Buffer.h"
#include <span>
namespace d3d12helper {

class UploadBuffer final : public Buffer {
private:
    ComPtr<ID3D12Resource> resource;
    uint64 byteSize;
    void *mappedAddress;

public:
    ID3D12Resource *GetResource() const override { return resource.Get(); }
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const override { return resource->GetGPUVirtualAddress(); }
    void *GetCPUAddress() const { return mappedAddress; }
    uint64 GetByteSize() const override { return byteSize; }
    UploadBuffer(
        ID3D12Device *device,
        uint64 byteSize,
        std::string name = "");
    ~UploadBuffer();
    void CopyData(uint64 offset, std::span<vbyte const> data) const;
    D3D12_RESOURCE_STATES GetInitState() const override
    {
        return D3D12_RESOURCE_STATE_GENERIC_READ;
    }
    UploadBuffer(UploadBuffer &&) = default;     // Move constructor
    UploadBuffer(UploadBuffer const &) = delete; // Copy constructor
    // void DelayDispose(FrameResource *frameRes) const override;
};

} // namespace d3d12helper