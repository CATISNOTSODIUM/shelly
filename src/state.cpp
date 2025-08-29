#include "state.h"
#include "shell.h"
#include "util.h"
#include <chrono>
#include <iostream>

State::State(Shell * _shell) {
    shell = _shell;
    promptPrefix = getShellPrefix();
}

State::~State() {
    
}

std::string State::getPromptPrefix() {
    int * status = shell->status;
    std::string appendedStatus =
        (status && (*status)) ? "\033[31m<!> \033[0m" : "";
    return appendedStatus + promptPrefix;
}

void State::instrument(std::function<void(State *state)> runner)
{
    auto start = std::chrono::steady_clock::now();
    runner(this);
    auto end = std::chrono::steady_clock::now();
    std::cout << formatTimeReadable(end - start) << std::endl;
}

void State::updateCmdStatistics(std::string & cmd)
{
}