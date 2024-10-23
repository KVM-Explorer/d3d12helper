#pragma once
#include <string>
namespace d3d12helper {
std::wstring string2wstring(std::string str);

// 将wstring转换成string
std::string wstring2string(std::wstring wstr);

} // namespace d3d12helper