#pragma once
#include "d3d12helper/d3dx12.h"
#include "d3d12helper/Utils.h"
#include <dxgi1_6.h>

namespace d3d12helper {
class DxFactory {
public:
    struct DeviceInfo {
        uint32_t adapterIndex;
        std::wstring description;
    };

    static std::shared_ptr<DxFactory> GetInstance();

    auto GetFactory() -> IDXGIFactory6 *;

    auto GetDeviceInfo() -> std::vector<DeviceInfo>;

private:
    DxFactory() = default;

    void CreateFactory();

    static std::shared_ptr<DxFactory> instance;
    Microsoft::WRL::ComPtr<IDXGIFactory6> m_factory;
};
} // namespace d3d12helper