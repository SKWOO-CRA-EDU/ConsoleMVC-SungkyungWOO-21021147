#include "ConsoleInputAdapter.h"
#include <iostream>

std::optional<std::string> ConsoleInputAdapter::NextLine() {
    std::string line;
    if (!std::getline(std::cin, line)) {
        return std::nullopt;
    }
    return line;
}
