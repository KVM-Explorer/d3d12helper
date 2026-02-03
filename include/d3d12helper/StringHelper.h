#pragma once
#include <string>
#include <sstream>
#include <codecvt>
#include <locale>
namespace d3d12helper {
static std::wstring string2wstring(std::string str)
{
    if (str.empty()) return L"";
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.from_bytes(str);
}

// 将wstring转换成string
static std::string wstring2string(std::wstring wstr)
{
    if (wstr.empty()) return "";
    std::wstring_convert<std::codecvt_utf8<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

template <std::size_t N>
std::string joinWith(const std::array<std::string_view, N> &arr, std::string_view delimiter = "")
{
    std::ostringstream oss; // 使用 std::ostringstream 来高效拼接字符串
    for (std::size_t i = 0; i < N; ++i) {
        oss << arr[i]; // 添加当前 string_view
        if (i < N - 1) {
            oss << delimiter; // 添加分隔符（如果不是最后一个元素）
        }
    }
    return oss.str(); // 返回拼接后的字符串
}

} // namespace d3d12helper