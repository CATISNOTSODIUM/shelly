#include "state.h"
#include "shell.h"
#include "util.h"

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