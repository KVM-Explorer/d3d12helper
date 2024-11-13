#include "d3d12helper/DXRuntime/DxFactory.h"
#include "d3d12helper/Interface.h"
using namespace d3d12helper;
#include <dxgi1_6.h>

std::shared_ptr<DxFactory> DxFactory::instance = nullptr;

std::shared_ptr<DxFactory> DxFactory::GetInstance()
{
    if (instance == nullptr) {
        instance = std::shared_ptr<DxFactory>(new DxFactory());
        instance->CreateFactory();
    }
    return instance;
}

auto DxFactory::GetFactory() -> IDXGIFactory6 *
{
    return m_factory.Get();
}

auto DxFactory::GetDeviceInfo() -> std::vector<DeviceInfo>
{
    UINT dxgiFactoryFlags = 0;
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    std::vector<DeviceInfo> devices;

    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_factory));

    DXGI_ADAPTER_DESC1 adapterDesc = {};

    for (UINT i = 0;
         DXGI_ERROR_NOT_FOUND != m_factory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
         i++) {
        adapter->GetDesc1(&adapterDesc);
        if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
            continue;

        DeviceInfo info;
        info.description = adapterDesc.Description;
        devices.push_back(info);
    }

    return devices;
}

void DxFactory::CreateFactory()
{
    UINT dxgiFactoryFlags = 0;

// debugController
#ifdef D3D12HELPER_DEBUG
    d3d12helper::ID3D12DebugPtr debugController;
    if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
        debugController->EnableDebugLayer();
    }

    d3d12helper::ID3D12Debug1Ptr debug1;
    debugController->QueryInterface(IID_PPV_ARGS(&debug1));
    // debug1->SetEnableGPUBasedValidation(true);

    dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&m_factory));
}