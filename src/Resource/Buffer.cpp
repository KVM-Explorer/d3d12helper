#pragma once
#include "d3d12helper/Resource/Buffer.h"
#include "d3d12helper/Resource/BufferView.h"

BufferView::BufferView(Buffer const* buffer)
	: buffer(buffer),
	  byteSize(buffer ? buffer->GetByteSize() : 0),
	  offset(0) {
}
BufferView::BufferView(
	Buffer const* buffer,
	uint64 offset,
	uint64 byteSize)
	: buffer(buffer),
	  offset(offset),
	  byteSize(byteSize) {}
Buffer::Buffer(
	ID3D12Device* device)
	: Resource(device){
}
Buffer::~Buffer() {
}
