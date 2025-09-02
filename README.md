# Pawershele - the interactive shell that tracks your statistics

Pawershele is an interactive shell that tracks irrelevant information, such as
typing speed and most used commands.

## Quick start
Pawershele uses CMake to generate a build environment in a new directory. First, create a new directory `build` and execute the following. Make sure that you have your `cmake` installed in your device.
```sh
mkdir build
cd build
cmake ..
```
Then, run `make` to build your executable. Your final executable `pawershele` should be present in the `build` directory.
## Checklist

- [x] Simple command without arguments
- [x] Command with at least one arguments
- [ ] Serialize multithreaded command tracking
- [ ] Resolve path issues
- [ ] Handle `cd` `exit` `fg` and other command (And show not found if command not found)


Upon running commands, we also update the statistics by using `State::instrument`.
