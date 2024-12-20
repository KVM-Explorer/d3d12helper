#include "d3d12helper/Resource/ReadbackBuffer.h"
#include "d3d12helper/StringHelper.h"
#include <cassert>

using namespace d3d12helper;

ReadbackBuffer::ReadbackBuffer(
    ID3D12Device *device,
    uint64 byteSize, std::string name) :
    Buffer(device),
    byteSize(byteSize)
{
    auto prop = CD3DX12_HEAP_PROPERTIES(D3D12_HEAP_TYPE_READBACK);
    auto buffer = CD3DX12_RESOURCE_DESC::Buffer(byteSize);
    ThrowIfFailed(device->CreateCommittedResource(
        &prop,
        D3D12_HEAP_FLAG_NONE,
        &buffer,
        D3D12_RESOURCE_STATE_COPY_DEST,
        nullptr,
        IID_PPV_ARGS(&resource)));
    if (!name.empty()) {
        resource->SetName(string2wstring(name).c_str());
    }

    D3D12_RANGE range;
    range.Begin = 0;
    range.End = byteSize;
}

ReadbackBuffer::~ReadbackBuffer()
{
    if (isMapped) {
        Unmap();
    }
}

void ReadbackBuffer::Unmap()
{
    assert(isMapped);
    resource->Unmap(0, nullptr);
    isMapped = false;
}

void *ReadbackBuffer::Map()
{
    assert(!isMapped);
    ThrowIfFailed(resource->Map(0, nullptr, &mappedAddress));
    isMapped = true;
    return mappedAddress;
}
