# Shelly - the interactive shell that tracks your statistics

Shelly is an interactive shell that tracks irrelevant information, such as
typing speed and most used commands.

## Checklist

- [/] Simple command without arguments
- [/] Command with at least one arguments
- [ ] Serialize multithreaded command tracking
- [ ] Resolve path issues
- [ ] Handle `cd` `exit` `fg` and other command (And show not found if command not found)


Upon running commands, we also update the statistics by using `State::instrument`.
