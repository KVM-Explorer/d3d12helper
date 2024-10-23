#include "d3d12helper/StringHelper.h"
#include <codecvt>
#include <locale>
#include <string>

namespace d3d12helper {

std::wstring string2wstring(const std::string &str)
{
    std::wstring wstr(str.begin(), str.end());
    return wstr;
}

std::string wstring2string(const std::wstring &wstr)
{
    std::string str(wstr.begin(), wstr.end());
    return str;
}

} // namespace d3d12helper
