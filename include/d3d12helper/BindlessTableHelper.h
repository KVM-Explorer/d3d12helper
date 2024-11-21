#include <d3d12.h>
#pragma once
#include "d3d12helper/d3dx12.h"
#include <array>
#include "d3d12helper/Meta.h"
namespace d3d12helper {
const int StandardDescriptorTableCount = 7;

static inline auto GetStandardDescriptorTableRanges() -> std::array<CD3DX12_DESCRIPTOR_RANGE1, StandardDescriptorTableCount>
{
    auto ret = std::array<CD3DX12_DESCRIPTOR_RANGE1, StandardDescriptorTableCount>{};
    for (uint32 i = 0; i < StandardDescriptorTableCount; ++i) {
        ret[i].RangeType = D3D12_DESCRIPTOR_RANGE_TYPE_SRV;
        ret[i].NumDescriptors = D3D12_DESCRIPTOR_RANGE_OFFSET_APPEND; //
        ret[i].BaseShaderRegister = 0;
        ret[i].RegisterSpace = i;
        ret[i].OffsetInDescriptorsFromTableStart = 0;
        ret[i].Flags = D3D12_DESCRIPTOR_RANGE_FLAG_DATA_VOLATILE;
    }
    return ret;
}
} // namespace d3d12helper
