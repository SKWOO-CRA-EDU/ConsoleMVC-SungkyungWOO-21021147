#pragma once
#include "../../ports/IOutputPort.h"

// IOutputPort 구현(View-B): 동일한 이벤트를 사람용 문구가 아닌
// key=value 형태로 렌더링한다. FR-05/FR-06 증명용 — main.cpp의 조립 지점
// 한 곳만 바꾸면 View-A(ConsoleOutputAdapter)와 교체 가능하며,
// AppController/도메인 코드는 이 파일의 존재 자체를 모른다.
class PlainConsoleOutputAdapter : public IOutputPort {
public:
    void ShowMainMenu() override;
    void ShowSampleForm() override;
    void OnSampleRegistered(const SampleRecord& sample) override;
    void OnError(const std::string& code, const std::string& detail) override;
    void OnExit() override;
};
