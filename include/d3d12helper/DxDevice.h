#pragma once

#include "Utils.h"
#include "d3dx12.h"
#include <d3d12.h>
#include <dxgi1_6.h>


namespace d3d12helper {
class DxDevice {
public:
  static auto GetDeviceInfo(IDXGIFactory6 *factory)
      -> std::vector<std::wstring> {
    UINT dxgiFactoryFlags = 0;
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    std::vector<std::wstring> devices;

    CreateDXGIFactory2(dxgiFactoryFlags, IID_PPV_ARGS(&factory));

    DXGI_ADAPTER_DESC1 adapterDesc = {};

    for (UINT i = 0;
         DXGI_ERROR_NOT_FOUND !=
         factory->EnumAdapterByGpuPreference(
             i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
         i++) {
      adapter->GetDesc1(&adapterDesc);
      if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
        continue;
      devices.push_back(adapterDesc.Description);
    }

    return devices;
  }

  ID3D12Device *Device() const { return mDevice.Get(); }

  static auto CreateDevice(IDXGIFactory6 *factory, int index)
      -> ComPtr<ID3D12Device> {
    ComPtr<ID3D12Device> device;
    DXGI_ADAPTER_DESC1 adapterDesc = {};
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    for (UINT i = 0;
         DXGI_ERROR_NOT_FOUND !=
         factory->EnumAdapterByGpuPreference(
             i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
         i++) {
      adapter->GetDesc1(&adapterDesc);
      if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
        continue;
      if (i == index) {
        auto message =
            std::format(L"Id:{} {}\n", index, adapterDesc.Description);
        OutputDebugString(message.c_str());
        D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0,
                          IID_PPV_ARGS(&device));
      }
    }
    return device;
  }

  DxDevice(IDXGIFactory6 *factory, int index = 0) {
    DXGI_ADAPTER_DESC1 adapterDesc = {};
    Microsoft::WRL::ComPtr<IDXGIAdapter1> adapter;
    for (UINT i = 0;
         DXGI_ERROR_NOT_FOUND !=
         factory->EnumAdapterByGpuPreference(
             i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
         i++) {
      adapter->GetDesc1(&adapterDesc);
      if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE)
        continue;
      if (i == index) {
        D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0,
                          IID_PPV_ARGS(&mDevice));
      }
    }
  }

  ~DxDevice() { mDevice->Release(); };

private:
  ComPtr<ID3D12Device> mDevice;
};
} // namespace D3D12Helper
