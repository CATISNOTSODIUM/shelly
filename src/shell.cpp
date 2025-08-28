#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include "shell.h"
#include <sys/wait.h>

Shell::Shell()
{
    state = new State(this);
    status = (int *) malloc(sizeof(int));
    *status = 0;
}

Shell::~Shell()
{
    delete state;
    delete status;
}



std::string Shell::getCommand()
{
    if (!state) {
        return "TODO";
    }
    std::string cmd;
    std::cout << state->getPromptPrefix();
    std::getline(std::cin, cmd);
    return cmd;
}

inline std::string trim(std::string &str)
{
    str.erase(str.find_last_not_of(' ') + 1);
    str.erase(0, str.find_first_not_of(' ')); 
    return str;
}

int Shell::run()
{
    while (std::cin.good())
    {
        std::string cmd = getCommand();
        cmd = trim(cmd);
        auto runner = [&](State *state)
        {
            if (fork())
            {
                wait(status);
            }
            else
            {
                char *cstr = new char[cmd.length() + 1]; // +1 for null terminator
                std::strcpy(cstr, cmd.c_str());
                char *args[] = {cstr, nullptr};
                execvp(cstr, args);
                exit(1);
            }
        };
        state->instrument(runner);
        }
    return 0;
}
