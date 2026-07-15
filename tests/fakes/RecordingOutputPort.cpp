#include "RecordingOutputPort.h"

void RecordingOutputPort::ShowMainMenu() {
    events.push_back(RecordedEvent{RecordedEvent::Kind::MainMenuShown, {}, "", ""});
}

void RecordingOutputPort::ShowSampleForm() {
    events.push_back(RecordedEvent{RecordedEvent::Kind::SampleFormShown, {}, "", ""});
}

void RecordingOutputPort::OnSampleRegistered(const SampleRecord& sample) {
    events.push_back(RecordedEvent{RecordedEvent::Kind::SampleRegistered, sample, "", ""});
}

void RecordingOutputPort::OnError(const std::string& code, const std::string& detail) {
    events.push_back(RecordedEvent{RecordedEvent::Kind::Error, {}, code, detail});
}

void RecordingOutputPort::OnExit() {
    events.push_back(RecordedEvent{RecordedEvent::Kind::Exit, {}, "", ""});
}
