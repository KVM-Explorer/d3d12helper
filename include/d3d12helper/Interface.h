#pragma once
#include "d3d12helper/d3dx12.h"
#include <d3d12shader.h>
#include <dxgi.h>
#include <dxgi1_6.h>
namespace d3d12helper {
// Common
using ID3DBlobPtr = Microsoft::WRL::ComPtr<ID3DBlob>;

// DXGI
using IDXGIAdapterPtr = Microsoft::WRL::ComPtr<IDXGIAdapter>;
using IDXGIAdapter1Ptr = Microsoft::WRL::ComPtr<IDXGIAdapter1>;
using IDXGIDevicePtr = Microsoft::WRL::ComPtr<IDXGIDevice>;
using IDXGIDevice1Ptr = Microsoft::WRL::ComPtr<IDXGIDevice1>;
using IDXGIDeviceSubObjectPtr = Microsoft::WRL::ComPtr<IDXGIDeviceSubObject>;
using IDXGIFactoryPtr = Microsoft::WRL::ComPtr<IDXGIFactory>;
using IDXGIFactory1Ptr = Microsoft::WRL::ComPtr<IDXGIFactory1>;
using IDXGIKeyedMutexPtr = Microsoft::WRL::ComPtr<IDXGIKeyedMutex>;
using IDXGIObjectPtr = Microsoft::WRL::ComPtr<IDXGIObject>;
using IDXGIOutputPtr = Microsoft::WRL::ComPtr<IDXGIOutput>;
using IDXGIResourcePtr = Microsoft::WRL::ComPtr<IDXGIResource>;
using IDXGISurface1Ptr = Microsoft::WRL::ComPtr<IDXGISurface1>;
using IDXGIFactory4Ptr = Microsoft::WRL::ComPtr<IDXGIFactory4>;
using IDXGIFactory6Ptr = Microsoft::WRL::ComPtr<IDXGIFactory6>;
using IDXGISwapChainPtr = Microsoft::WRL::ComPtr<IDXGISwapChain>;
using IDXGISwapChain3Ptr = Microsoft::WRL::ComPtr<IDXGISwapChain3>;


// D3D12
using ID3D12CommandAllocatorPtr = Microsoft::WRL::ComPtr<ID3D12CommandAllocator>;
using ID3D12CommandListPtr = Microsoft::WRL::ComPtr<ID3D12CommandList>;
using ID3D12CommandQueuePtr = Microsoft::WRL::ComPtr<ID3D12CommandQueue>;
using ID3D12CommandSignaturePtr = Microsoft::WRL::ComPtr<ID3D12CommandSignature>;
using ID3D12DescriptorHeapPtr = Microsoft::WRL::ComPtr<ID3D12DescriptorHeap>;
using ID3D12DevicePtr = Microsoft::WRL::ComPtr<ID3D12Device>;
using ID3D12DeviceChildPtr = Microsoft::WRL::ComPtr<ID3D12DeviceChild>;
using ID3D12FencePtr = Microsoft::WRL::ComPtr<ID3D12Fence>;
using ID3D12GraphicsCommandListPtr = Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList>;
using ID3D12HeapPtr = Microsoft::WRL::ComPtr<ID3D12Heap>;
using ID3D12ObjectPtr = Microsoft::WRL::ComPtr<ID3D12Object>;
using ID3D12PageablePtr = Microsoft::WRL::ComPtr<ID3D12Pageable>;
using ID3D12PipelineStatePtr = Microsoft::WRL::ComPtr<ID3D12PipelineState>;
using ID3D12QueryHeapPtr = Microsoft::WRL::ComPtr<ID3D12QueryHeap>;
using ID3D12ResourcePtr = Microsoft::WRL::ComPtr<ID3D12Resource>;
using ID3D12RootSignaturePtr = Microsoft::WRL::ComPtr<ID3D12RootSignature>;
using ID3D12RootSignatureDeserializerPtr = Microsoft::WRL::ComPtr<ID3D12RootSignatureDeserializer>;

using ID3D12FunctionParameterReflectionPtr = Microsoft::WRL::ComPtr<ID3D12FunctionParameterReflection>;
using ID3D12FunctionReflectionPtr = Microsoft::WRL::ComPtr<ID3D12FunctionReflection>;
using ID3D12LibraryReflectionPtr = Microsoft::WRL::ComPtr<ID3D12LibraryReflection>;
using ID3D12ShaderReflectionPtr = Microsoft::WRL::ComPtr<ID3D12ShaderReflection>;
using ID3D12ShaderReflectionConstantBufferPtr = Microsoft::WRL::ComPtr<ID3D12ShaderReflectionConstantBuffer>;
using ID3D12ShaderReflectionTypePtr = Microsoft::WRL::ComPtr<ID3D12ShaderReflectionType>;
using ID3D12ShaderReflectionVariablePtr = Microsoft::WRL::ComPtr<ID3D12ShaderReflectionVariable>;

using ID3D12DebugPtr = Microsoft::WRL::ComPtr<ID3D12Debug>;
using ID3D12Debug1Ptr = Microsoft::WRL::ComPtr<ID3D12Debug1>;
using ID3D12DebugDevicePtr = Microsoft::WRL::ComPtr<ID3D12DebugDevice>;
using ID3D12DebugCommandListPtr = Microsoft::WRL::ComPtr<ID3D12DebugCommandList>;
using ID3D12DebugCommandQueuePtr = Microsoft::WRL::ComPtr<ID3D12DebugCommandQueue>;
using ID3D12InfoQueuePtr = Microsoft::WRL::ComPtr<ID3D12InfoQueue>;
}