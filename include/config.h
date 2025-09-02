#ifndef PAWERSHELE_CONFIG_H
#define PAWERSHELE_CONFIG_H

#include <bits/stdc++.h>

// Some general (and static) text
static const char CMD_FREQUENCY_CONFIG[] = "===CMD_FREQUENCY_CONFIG===";

bool loadFile(State *state, const std::string &filePath)
{
    enum LoadStatus {
        READ_CMD_FREQ,
        DEFAULT
    };

    std::ifstream infile(filePath);
    std::string currentLine;
    std::string header;
    LoadStatus status = DEFAULT;
    int lineCount = 1;
    while (std::getline(infile, currentLine)) {
        if (currentLine.empty()) break;
        std::istringstream iss(currentLine);
        // Main logic
        switch (status)
        {
        case READ_CMD_FREQ:
            {
                std::string cmd;
                long freq;
                if (!(iss >> cmd >> freq))
                {
                    std::cerr << "Parsing error at line " << 
                        lineCount << std::endl;
                    break;
                }
                state->cmdFrequency[cmd] = freq;
                break;
            }
        
        default:
            {
                // parse header
                if (!(iss >> header))
                    break;
                if (header == CMD_FREQUENCY_CONFIG)
                {
                    status = READ_CMD_FREQ;
                }
                break;
            }
        }
        lineCount++;
    }
    return true;
}

bool saveFile(State *state, const std::string &filePath)
{
    if (!state) return false;

    std::ofstream outfile(filePath);
    // Write cmd frequency configuration
    outfile << CMD_FREQUENCY_CONFIG << "\n";
    
    for (const auto& pair: state->cmdFrequency) {
        outfile << pair.first << " " << pair.second << "\n";
    }
    outfile.close();
    return true;
}

#endif