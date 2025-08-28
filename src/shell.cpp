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
    std::string cmd;
    if (state) {
        std::cout << state->getPromptPrefix();
    }
    std::getline(std::cin, cmd);
    return cmd;
}

int Shell::run()
{
    while (std::cin.good())
    {
        std::string cmd = getCommand();
        if (fork())
        {
            wait(status);
        } else {
            char *cstr = new char[cmd.length() + 1]; // +1 for null terminator
            std::strcpy(cstr, cmd.c_str());
            char *args[] = {cstr, nullptr};
            execvp(cstr, args);
            exit(1);
        }
    }
    return 0;
}
