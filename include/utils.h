#pragma once
#include <d3dcommon.h>
#include <dxgi.h>
#include <stdexcept>
#include <string>
#include <wrl/client.h>
#include <format>

namespace D3D12Helper {

using Microsoft::WRL::ComPtr;

inline std::string HrToString(HRESULT hr) {
  char s_str[64] = {};
  sprintf_s(s_str, "HRESULT of 0x%08X", static_cast<uint32_t>(hr));
  return std::string(s_str);
}

class HandleException : public std::runtime_error {
public:
  HandleException(HRESULT handle)
      : std::runtime_error(HrToString(handle)), mHandle(handle) {}

private:
  const HRESULT mHandle;
};

inline void ThrowIfFailed(HRESULT handler) {
  if (FAILED(handler)) {
    throw HandleException(handler);
  }
}



inline UINT CalculateConstantBufferByteSize(UINT byteSize) {
  return (byteSize + 255) & ~255;
}

inline void SetDXGIDebug(IDXGIObject *object, std::string name) {
  object->SetPrivateData(WKPDID_D3DDebugObjectName, name.size(), name.data());
}

inline uint32_t UpperMemorySize(uint32_t size, uint32_t alignment) {
  return (size + alignment - 1) & ~(alignment - 1);
}

} // namespace d3dhelper