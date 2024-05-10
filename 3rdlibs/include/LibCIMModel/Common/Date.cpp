#include <chrono>
#include <ctime>
#include <sstream>
#include <iomanip>

#include "Date.hpp"


std::string NNU::OpenCIM::Common::Date::currentDate() {
    // 获取当前时间点
    std::chrono::system_clock::time_point now = std::chrono::system_clock::now();

    // 转换为 time_t（自纪元以来的秒数）
    std::time_t now_c = std::chrono::system_clock::to_time_t(now);

    // 转换为本地时间
    std::tm *now_tm;

    // 跨平台处理
#ifdef _WIN32
    std::tm now_tm_buf{};
    now_tm = &now_tm_buf;
    localtime_s(now_tm, &now_c);  // Windows 使用 localtime_s
#else
    std::tm now_tm_buf{};
    std::tm* now_tm_ptr = &now_tm_buf;
    now_tm = std::localtime_r(&now_c, now_tm_ptr);  // Linux 使用 localtime_r
#endif

    // 格式化为字符串
    std::stringstream ss;
    ss << std::put_time(now_tm, "%Y-%m-%d %H:%M:%S");
    std::string time_str = ss.str();

    return time_str;
}
