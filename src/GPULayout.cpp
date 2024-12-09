#include "d3d12helper/GPULayout.h"
#include "d3d12helper/Utils.h"

d3d12helper::ID3D12RootSignaturePtr d3d12helper::GPULayout::CreateRootSignature(ID3D12Device *device, const D3D12_ROOT_SIGNATURE_DESC1 &desc)
{
    ID3DBlobPtr signature;
    ID3DBlobPtr error;
    D3D12_VERSIONED_ROOT_SIGNATURE_DESC versionedDesc = {};
    versionedDesc.Version = D3D_ROOT_SIGNATURE_VERSION_1_1;
    versionedDesc.Desc_1_1 = desc;

    auto hr = D3D12SerializeVersionedRootSignature(&versionedDesc, &signature, &error);

    if (FAILED(hr)) {
        if (error) {
            OutputDebugStringA((char *)error->GetBufferPointer());
        }
        ThrowIfFailed(hr);
    }

    ID3D12RootSignaturePtr ret;
    ThrowIfFailed(device->CreateRootSignature(0, signature->GetBufferPointer(), signature->GetBufferSize(), IID_PPV_ARGS(&ret)));

    return ret;
}
