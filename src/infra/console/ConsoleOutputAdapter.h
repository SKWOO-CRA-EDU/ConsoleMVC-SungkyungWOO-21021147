#pragma once
#include "../../ports/IOutputPort.h"

// IOutputPort 구현(View-A): 사람이 읽을 형식으로 콘솔에 출력한다.
// 저장소에서 iostream을 참조하는 두 곳(Input/Output Adapter) 중 하나.
class ConsoleOutputAdapter : public IOutputPort {
public:
    void ShowMainMenu() override;
    void ShowSampleForm() override;
    void OnSampleRegistered(const SampleRecord& sample) override;
    void OnError(const std::string& code, const std::string& detail) override;
    void OnExit() override;
};
