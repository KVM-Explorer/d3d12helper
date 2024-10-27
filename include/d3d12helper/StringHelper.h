#pragma once
#include <string>
namespace d3d12helper {
static std::wstring string2wstring(std::string str){
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

// 将wstring转换成string
static std::string wstring2string(std::wstring wstr){
    std::string str(wstr.begin(), wstr.end());
    return str;
}

} // namespace d3d12helper