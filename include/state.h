#ifndef SHELLY_STATE_H
#define SHELLY_STATE_H

#include <string>

// Forwarding class
class Shell;

/**
 * Represents the global states of shelly
 */
class State
{
public:
    State(Shell * shell);
    ~State();
    static void loadState(char *filePath);
    void saveState();
    std::string getPromptPrefix(); 
private:
    State();
    std::string promptPrefix;
    Shell * shell;
};

#endif