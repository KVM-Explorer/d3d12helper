#include "d3d12helper/DXRuntime/DxDevice.h"
#include "d3d12helper/DXRuntime/DxFactory.h"
#include "d3d12helper/StringHelper.h"
#include <iostream>

using namespace d3d12helper;

Device::Device(uint32_t adapterIndex)
{
    auto instance = DxFactory::GetInstance();
    dxgiFactory = instance->GetFactory();

    DXGI_ADAPTER_DESC1 adapterDesc = {};
    for (UINT i = 0; DXGI_ERROR_NOT_FOUND != dxgiFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter)); i++) {
        adapter->GetDesc1(&adapterDesc);
        if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) continue;
        if (i == adapterIndex) {
            std::string name = d3d12helper::wstring2string(std::wstring(adapterDesc.Description));
            OutputDebugStringA(("Adapter: " + name + "\n").c_str());
            std::cout << std::format("Index: {} Name: {}", adapterIndex, name) << std::endl;
            D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&dxDevice));
            break;
        }
    }

#ifdef D3D12HELPER_DEBUG

    ID3D12InfoQueuePtr infoQueue;
    if (SUCCEEDED(dxDevice->QueryInterface(IID_PPV_ARGS(&infoQueue)))) {
        infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_ERROR, true);
        infoQueue->SetBreakOnSeverity(D3D12_MESSAGE_SEVERITY_WARNING, true);
    }
#endif
}

Device::~Device()
{
    dxDevice.Reset();
    adapter.Reset();
}
