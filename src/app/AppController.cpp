#include "AppController.h"
#include <sstream>
#include <vector>

AppController::AppController(IInputPort& input, IOutputPort& output,
                              ISampleRepository& samples, IOrderRepository& orders)
    : input_(input), output_(output), samples_(samples), orders_(orders) {
}

void AppController::Run() {
    output_.ShowMainMenu();
    bool running = true;
    while (running) {
        auto line = input_.NextLine();
        if (!line.has_value()) {
            output_.OnExit();
            break;
        }
        running = HandleLine(*line);
    }
}

bool AppController::HandleLine(const std::string& line) {
    switch (state_) {
        case State::MainMenu:
            return HandleMainMenu(line);
        case State::SampleForm:
            return HandleSampleForm(line);
    }
    return true;
}

bool AppController::HandleMainMenu(const std::string& line) {
    if (line == "1") {
        state_ = State::SampleForm;
        output_.ShowSampleForm();
        return true;
    }
    if (line == "0" || line == "exit") {
        output_.OnExit();
        return false;
    }
    output_.OnError("UNKNOWN_COMMAND", line);
    return true;
}

bool AppController::HandleSampleForm(const std::string& line) {
    if (line == "back") {
        state_ = State::MainMenu;
        output_.ShowMainMenu();
        return true;
    }
    if (line == "0" || line == "exit") {
        output_.OnExit();
        return false;
    }

    SampleRecord record;
    if (!TryParseSample(line, record)) {
        output_.OnError("INVALID_SAMPLE_INPUT", line);
        return true;
    }

    WriteOutcome outcome = samples_.Add(record);
    if (outcome != WriteOutcome::Ok) {
        output_.OnError("DUPLICATE_SAMPLE_ID", record.sampleId);
        state_ = State::MainMenu;
        output_.ShowMainMenu();
        return true;
    }

    output_.OnSampleRegistered(record);
    state_ = State::MainMenu;
    output_.ShowMainMenu();
    return true;
}

bool AppController::TryParseSample(const std::string& line, SampleRecord& out) {
    std::vector<std::string> fields;
    std::stringstream ss(line);
    std::string field;
    while (std::getline(ss, field, ',')) {
        fields.push_back(field);
    }
    if (fields.size() != 5) return false;

    try {
        out.sampleId = fields[0];
        out.name = fields[1];
        out.avgProductionTime = std::stod(fields[2]);
        out.yieldNumerator = std::stoi(fields[3]);
        out.stockQuantity = std::stoll(fields[4]);
    } catch (...) {
        return false;
    }

    if (out.sampleId.empty() ||
        out.avgProductionTime <= 0 ||
        out.yieldNumerator <= 0 || out.yieldNumerator > YIELD_DENOMINATOR ||
        out.stockQuantity < 0) {
        return false;
    }
    return true;
}
