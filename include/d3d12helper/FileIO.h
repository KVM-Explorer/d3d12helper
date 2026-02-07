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

inline std::string GetFileName(const std::string &path)
{
    std::filesystem::path p(path);
    return p.filename().string();
}

inline std::string GetFileNameOnly(const std::string &path)
{
    std::filesystem::path p(path);
    return p.filename().stem().string();
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

inline void PreparePath(const std::string& filePath) {
    namespace fs = std::filesystem;
    fs::path p(filePath);
    
    // 获取父目录路径 (例如 "logs/v1/test.json" -> "logs/v1")
    fs::path dir = p.parent_path();

    // 如果目录不为空且不存在，则递归创建所有级别的目录
    if (!dir.empty() && !fs::exists(dir)) {
        fs::create_directories(dir); 
    }
}

} // namespace d3d12helper