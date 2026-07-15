#include "ConsoleOutputAdapter.h"
#include <iostream>

void ConsoleOutputAdapter::ShowMainMenu() {
    std::cout << "[MENU] 1) Register sample   0) Exit" << std::endl;
}

void ConsoleOutputAdapter::ShowSampleForm() {
    std::cout << "[SAMPLE] sampleId,name,avgProductionTime,yieldNumerator,stockQuantity  (back)"
               << std::endl;
}

void ConsoleOutputAdapter::OnSampleRegistered(const SampleRecord& sample) {
    std::cout << "[OK] registered sample " << sample.sampleId << " (" << sample.name << ")"
               << std::endl;
}

void ConsoleOutputAdapter::OnError(const std::string& code, const std::string& detail) {
    std::cout << "[ERROR] " << code << ": " << detail << std::endl;
}

void ConsoleOutputAdapter::OnExit() {
    std::cout << "bye" << std::endl;
}
