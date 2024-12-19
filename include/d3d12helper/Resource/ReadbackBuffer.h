#pragma once

#include "d3d12helper/Resource/Buffer.h"
#include <span>

namespace d3d12helper {
class ReadbackBuffer final : public Buffer {
private:
    ComPtr<ID3D12Resource> resource;
    uint64 byteSize;
    void *mappedAddress;
    bool isMapped = false;

public:
    ID3D12Resource *GetResource() const override { return resource.Get(); }
    D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const override { return resource->GetGPUVirtualAddress(); }
    void *GetCPUAddress() const { return mappedAddress; }
    uint64 GetByteSize() const override { return byteSize; }
    ReadbackBuffer(
        ID3D12Device *device,
        uint64 byteSize,
        std::string name = "");
    ~ReadbackBuffer();
    void Unmap();
    void *Map();

    D3D12_RESOURCE_STATES GetInitState() const override
    {
        return D3D12_RESOURCE_STATE_COPY_DEST;
    }
    ReadbackBuffer(ReadbackBuffer &&) = default;     // Move constructor
    ReadbackBuffer(ReadbackBuffer const &) = delete; // Copy constructor
    // void DelayDispose(FrameResource *frameRes) const override;
};
} // namespace d3d12helper