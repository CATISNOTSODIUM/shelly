#ifndef SHELLY_UTIL_H
#define SHELLY_UTIL_H

#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>
#include <chrono>
#include <sstream>

std::string decorateString(std::string shellName, std::string userHost){
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
    return "\x1b[1;33m" + shellName + " ~ \x1b[1;31m" + userHost + "\x1b[1;0m";
}

std::string getShellPrefix()
{
    std::string shellName(std::getenv("SHELL"));
    char hostname[256];
    gethostname(hostname, sizeof(hostname));

    struct passwd *pw = getpwuid(getuid());
    std::string username = pw ? pw->pw_name : "user";
    std::string userHost = username + "@" + hostname + "$ ";
    return decorateString(shellName, userHost);
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