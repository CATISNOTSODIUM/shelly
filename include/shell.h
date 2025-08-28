#ifndef SHELLY_SHELL_H
#define SHELLY_SHELL_H

#include "state.h"

class Shell
{
public:
    Shell();
    ~Shell();
    int run();
    int *status;

private:
    State *state;
    std::string getCommand();
    
};

#endif
