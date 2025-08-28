#ifndef SHELLY_STATE_H
#define SHELLY_STATE_H

#include <string>
#include <functional>

// Forwarding class
class Shell;

/**
 * Represents the global states of shelly
 */
class State
{
public:
    State(Shell *shell);
    ~State();
    static void loadState(char *filePath);
    std::string getPromptPrefix();
    // Run the function and store the state if necessary
    void instrument(std::function<void(State * state)>);

private:
    State();
    std::string promptPrefix;
    Shell *shell;
};

#endif