#pragma once
#include "d3d12helper/DXRuntime/DxFactory.h"
#include "d3d12helper/Interface.h"
namespace d3d12helper {
class Device {
    IDXGIAdapter1Ptr adapter;
    ComPtr<ID3D12Device> dxDevice;
    IDXGIFactory6Ptr dxgiFactory;

public:
    IDXGIAdapter1 *Adapter() const { return adapter.Get(); }
    ID3D12Device *DxDevice() const { return dxDevice.Get(); }
    IDXGIFactory6 *Factory() const { return dxgiFactory.Get(); }
    Device(uint32_t adapterIndex = 0);
    ~Device();
};

} // namespace d3d12helper
