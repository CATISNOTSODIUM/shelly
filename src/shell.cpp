#include <iostream>
#include <unistd.h>
#include <string>
#include <cstring>
#include "shell.h"
#include <sys/wait.h>
#include <sstream>

Shell::Shell()
{
    state = new State(this);
    status = (int *)malloc(sizeof(int));
    *status = 0;
}

Shell::~Shell()
{
    delete state;
    delete status;
}

std::string Shell::getCommand()
{
    if (!state)
    {
        return "TODO";
    }
    std::string cmd;
    std::cout << state->getPromptPrefix();
    std::getline(std::cin, cmd);
    return cmd;
}

inline std::string trim(std::string &str)
{
    size_t start = str.find_first_not_of(" \t\n\r");
    if (start == std::string::npos)
        return "";

    size_t end = str.find_last_not_of(" \t\n\r");
    return str.substr(start, end - start + 1);
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
                // TODO: Add proper parser to handle special commands
                std::vector<std::string> tokens;
                std::vector<char *> args;
                std::istringstream iss(cmd);
                std::string token;
                while (iss >> token)
                {
                    tokens.push_back(trim(token));
                }
                for (auto &arg : tokens)
                {
                    args.push_back(&arg[0]);
                }
                args.push_back(NULL);
                state->updateCmdStatistics(tokens[0]);
                int status = execvp(args[0], args.data());
                exit(status);
            }
        };
        state->instrument(runner);
    }
    return 0;
}
