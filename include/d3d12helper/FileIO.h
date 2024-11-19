#pragma once

#include <filesystem>
#include <string>
#include <algorithm>

namespace d3d12helper {

// C++17 Check if file exists
inline bool FileExist(const std::string &path)
{
    if (path.empty())
        return false;
    std::filesystem::path p(path);
    // print absolute path

    return std::filesystem::exists(p);
}

inline std::string GetCurrentPath()
{
    return std::filesystem::current_path().string();
}

/// return file extension in uppercase (e.g. "DDS")
inline std::string GetFileExtension(const std::string &path)
{
    std::filesystem::path p(path);

    auto ret = p.extension().string();
    if (ret.starts_with("."))
        ret = ret.substr(1);
    std::transform(ret.begin(), ret.end(), ret.begin(), ::toupper);
    return ret;
}

inline std::string GetFileDirectory(const std::string &path)
{
    std::filesystem::path p(path);
    return p.parent_path().string();
}

inline std::string ConvertToWindowsPath(const std::string &path)
{
    std::string ret = path;
    std::replace(ret.begin(), ret.end(), '/', '\\');
    return ret;
}

} // namespace d3d12helper