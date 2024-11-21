#include "d3d12helper/StaticSampler.h"
#include "d3d12helper/DXMath/DXMath.h"
#include <cassert>

D3D12_STATIC_SAMPLER_DESC d3d12helper::GetStaticSamplerState(SamplerState samplerState, uint32 shaderRegister,
                                                             uint32 registerSpace, D3D12_SHADER_VISIBILITY visibility)
{
    assert(uint64(samplerState) < uint64(SamplerState::NumValues));
    return ConvertToStaticSampler(SamplerStateDescs[uint64(samplerState)], shaderRegister, registerSpace, visibility);
}

D3D12_STATIC_SAMPLER_DESC d3d12helper::ConvertToStaticSampler(const D3D12_SAMPLER_DESC &samplerDesc, uint32 shaderRegister,
                                                              uint32 registerSpace, D3D12_SHADER_VISIBILITY visibility)
{
    D3D12_STATIC_SAMPLER_DESC staticDesc = {};
    staticDesc.Filter = samplerDesc.Filter;
    staticDesc.AddressU = samplerDesc.AddressU;
    staticDesc.AddressV = samplerDesc.AddressV;
    staticDesc.AddressW = samplerDesc.AddressW;
    staticDesc.MipLODBias = samplerDesc.MipLODBias;
    staticDesc.MaxAnisotropy = samplerDesc.MaxAnisotropy;
    staticDesc.ComparisonFunc = samplerDesc.ComparisonFunc;
    staticDesc.MinLOD = samplerDesc.MinLOD;
    staticDesc.MaxLOD = samplerDesc.MaxLOD;
    staticDesc.ShaderRegister = shaderRegister;
    staticDesc.RegisterSpace = registerSpace;
    staticDesc.ShaderVisibility = visibility;

    Math::Vector4 borderColor = Math::Vector4(samplerDesc.BorderColor[0], samplerDesc.BorderColor[1], samplerDesc.BorderColor[2], samplerDesc.BorderColor[3]);
    if (equal(borderColor, Math::Vector4(1.0f, 1.0f, 1.0f, 1.0f), 0.0001f))
        staticDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_WHITE;
    else if (equal(borderColor, Math::Vector4(0, 0, 0, 1.0f), 0.0001f))
        staticDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_OPAQUE_BLACK;
    else
        staticDesc.BorderColor = D3D12_STATIC_BORDER_COLOR_TRANSPARENT_BLACK;

    return staticDesc;
}