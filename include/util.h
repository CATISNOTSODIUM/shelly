#ifndef SHELLY_UTIL_H
#define SHELLY_UTIL_H

#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <chrono>
#include <sstream>
#include <filesystem>

std::string getTruncatedCwd(int depth = 2) {
    namespace fs = std::filesystem;
    fs::path cwd = fs::current_path();
    std::vector<std::string> parts;
    for (const auto& part : cwd) {
        parts.push_back(part.string());
    }
    std::string result;
    int count = std::min(depth, static_cast<int>(parts.size()));
    for (int i = parts.size() - count; i < parts.size(); ++i) {
        std::string name = parts[i];
        if (i == parts.size() - 2 && depth == 2) {
            name = name.empty() ? "" : std::string(1, name[0]);
        }
        result += name;
        if (i < parts.size() - 1) result += "/";
    }
    return result;
}


std::string decorateString(std::string & shellName, std::string & userHost, std::string & path){
    if (shellName.find("zsh") != std::string::npos) {
        shellName = "zsh";
    }
    else if (shellName.find("bash") != std::string::npos)
    {
        shellName = "bash";
    }
    else
    {
        shellName = "";
    }
    return "\x1b[1;31m" + userHost + "\x1b[1;32m > " + path + " $ \x1b[1;0m";
}

std::string getShellPrefix()
{
    std::string shellName(std::getenv("SHELL"));
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    struct passwd *pw = getpwuid(getuid());
    std::string username = pw ? pw->pw_name : "user";
    std::string userHost = username + "@" + hostname;
    std::string currentPath = getTruncatedCwd();
    return decorateString(shellName, userHost, currentPath);
}

std::string formatTimeReadable(std::chrono::steady_clock::duration duration)
{
    using namespace std::chrono;

    auto totalMs = duration_cast<milliseconds>(duration).count();
    auto ms = totalMs % 1000;
    auto totalSec = totalMs / 1000;
    auto sec = totalSec % 60;
    auto min = totalSec / 60;

    std::vector<std::string> parts;
    if (min > 0)
        parts.push_back(std::to_string(min) + " m");
    if (sec > 0)
        parts.push_back(std::to_string(sec) + " s");
    if (ms > 0)
        parts.push_back(std::to_string(ms) + " ms");

    // Show only the first two non-zero units
    std::ostringstream oss;
    for (size_t i = 0; i < parts.size() && i < 2; ++i)
    {
        if (i > 0)
            oss << " ";
        oss << parts[i];
    }
    return oss.str();
}

#endif