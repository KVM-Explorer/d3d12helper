#include "StringHelper.h"
#include <codecvt>
#include <locale>
#include <string>
namespace D3D12Helper {

namespace D3D12Helper {

std::wstring string2wstring(const std::string& str) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.from_bytes(str);
}

std::string wstring2string(const std::wstring& wstr) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

} // namespace D3D12Helper

} // namespace D3D12Helper