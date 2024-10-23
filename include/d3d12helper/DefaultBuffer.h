#pragma once
#include "d3dx12.h"
#include "utils.h"
#include <d3d12.h>


namespace d3d12helper {
class DefaultBuffer {
public:
  DefaultBuffer(const DefaultBuffer &) = delete;
  DefaultBuffer(DefaultBuffer &&) = default;
  DefaultBuffer &operator=(const DefaultBuffer &) = delete;
  DefaultBuffer &operator=(DefaultBuffer &&) = default;

  DefaultBuffer(ID3D12Device *device, ID3D12GraphicsCommandList *commandList,
                const void *data, UINT64 byteSize);

  ~DefaultBuffer();

  void ReleaseUploader();
  [[nodiscard]] ID3D12Resource *Resource() const {
    return mDefaultBuffer.Get();
  };

private:
  Microsoft::WRL::ComPtr<ID3D12Resource> mUploadBuffer;
  Microsoft::WRL::ComPtr<ID3D12Resource> mDefaultBuffer;
  bool mIsMap = false;
};

} // namespace D3D12Helper
