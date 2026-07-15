#include "PlainConsoleOutputAdapter.h"
#include <iostream>

void PlainConsoleOutputAdapter::ShowMainMenu() {
    std::cout << "event=main_menu" << std::endl;
}

void PlainConsoleOutputAdapter::ShowSampleForm() {
    std::cout << "event=sample_form" << std::endl;
}

void PlainConsoleOutputAdapter::OnSampleRegistered(const SampleRecord& sample) {
    std::cout << "event=sample_registered sampleId=" << sample.sampleId
               << " name=" << sample.name << std::endl;
}

void PlainConsoleOutputAdapter::OnError(const std::string& code, const std::string& detail) {
    std::cout << "event=error code=" << code << " detail=" << detail << std::endl;
}

void PlainConsoleOutputAdapter::OnExit() {
    std::cout << "event=exit" << std::endl;
}
