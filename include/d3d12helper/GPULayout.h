#pragma once
#include "d3d12helper/Meta.h"
#include "d3d12helper/Interface.h"
namespace d3d12helper {

class GPULayout {
public:
    static ID3D12RootSignaturePtr CreateRootSignature(ID3D12Device *device, const D3D12_ROOT_SIGNATURE_DESC1 &desc);
};

} // namespace d3d12helper