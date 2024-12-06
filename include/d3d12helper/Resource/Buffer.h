#pragma once
#include "d3d12helper/Resource/Resource.h"
#include "d3d12helper/DXRuntime/DxDevice.h"

class Buffer : public Resource{
public:
	Buffer(ID3D12Device* device);
	virtual D3D12_GPU_VIRTUAL_ADDRESS GetGPUAddress() const = 0;
	virtual uint64_t GetByteSize() const = 0;
	virtual ~Buffer();
	Buffer(Buffer&&) = default;
};
