#include "FakeInputPort.h"

FakeInputPort::FakeInputPort(std::vector<std::string> lines)
    : lines_(lines.begin(), lines.end()) {
}

std::optional<std::string> FakeInputPort::NextLine() {
    if (lines_.empty()) return std::nullopt;
    std::string line = lines_.front();
    lines_.pop_front();
    return line;
}
