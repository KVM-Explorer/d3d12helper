#pragma once
#include "d3d12helper/d3dx12.h"
#include "d3d12helper/Utils.h"
#include <dxgi1_6.h>
#include <iostream>
class DxFactory {
public:
    struct DeviceInfo {
        uint32_t adapterIndex;
        std::wstring description;
    };

    static DxFactory *GetInstance()
    {
        if (!instance) {
            instance = std::make_unique<DxFactory>();
            instance->CreateFactory();
        }
        return instance.get();
    }

    auto GetFactory() -> IDXGIFactory6 *
    {
        return m_factory.Get();
    }



    auto
    GetDeviceInfo() -> std::vector<DeviceInfo>
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
            devices.push_back({i, adapterDesc.Description});
        }
        return devices;
    }

private:
    auto CreateFactory() -> void
    {
        UINT dxgiFactoryFlags = 0;

// debugController
#ifdef D3D12HELPER_DEBUG
        ID3D12DebugPtr debugController;
        if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController)))) {
            debugController->EnableDebugLayer();
        }

        ID3D12Debug1Ptr debug1;
        debugController->QueryInterface(IID_PPV_ARGS(&debug1));
        // debug1->SetEnableGPUBasedValidation(true);

        dxgiFactoryFlags |= DXGI_CREATE_FACTORY_DEBUG;
#endif

        d3d12helper::ThrowIfFailed(CreateDXGIFactory2(0, IID_PPV_ARGS(&m_factory)));
    }

private:
    static std::unique_ptr<DxFactory> instance;
    Microsoft::WRL::ComPtr<IDXGIFactory6> m_factory;
};

std::unique_ptr<DxFactory> DxFactory::instance = nullptr;