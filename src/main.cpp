#include <iostream>
#include <memory>
#include <csignal>
#include "shell.h"

std::shared_ptr<Shell> mainShell = nullptr;

void handleSigInt(int signal) {
  std::cout << "\nInterrupt signal (" << signal << ") received.\n";

  if (mainShell) {
    std::cout << "Shutting down Shell ...\n";
    mainShell.reset(); 
  }

  std::exit(signal);
}

int main(int argc, const char *argv[])
{
  std::signal(SIGINT, handleSigInt);
  mainShell = std::make_shared<Shell>();
  mainShell->run();

  return 0;
}
