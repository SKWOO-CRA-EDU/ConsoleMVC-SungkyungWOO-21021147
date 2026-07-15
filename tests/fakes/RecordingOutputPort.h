#pragma once
#include <string>
#include <vector>
#include "../../src/ports/IOutputPort.h"

struct RecordedEvent {
    enum class Kind { MainMenuShown, SampleFormShown, SampleRegistered, Error, Exit };
    Kind kind{};
    SampleRecord sample{};
    std::string errorCode;
    std::string errorDetail;
};

// 테스트용 가짜 출력처: 화면에 아무것도 그리지 않고, 발생한 이벤트를
// 구조화된 값(RecordedEvent)으로만 기록한다. 테스트는 이 값을 단언한다 —
// 렌더링된 문자열을 비교하지 않는다.
class RecordingOutputPort : public IOutputPort {
public:
    void ShowMainMenu() override;
    void ShowSampleForm() override;
    void OnSampleRegistered(const SampleRecord& sample) override;
    void OnError(const std::string& code, const std::string& detail) override;
    void OnExit() override;

    std::vector<RecordedEvent> events;
};
