#ifndef SHELLY_UTIL_H
#define SHELLY_UTIL_H

#include <string>
#include <sys/types.h>
#include <pwd.h>
#include <unistd.h>

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

#endif