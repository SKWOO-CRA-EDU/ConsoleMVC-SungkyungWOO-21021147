#pragma once
#include <string>
#include "../domain/Records.h"

// 출력처 경계: 화면 문자열이 아니라 "무슨 일이 일어났는지"를 의미론적으로 전달한다.
// 주의: Print(std::string) 같은 범용 텍스트 메서드를 추가하지 말 것 —
// 그 순간 테스트는 다시 화면 문자열을 비교하게 된다.
class IOutputPort {
public:
    virtual ~IOutputPort() = default;
    virtual void ShowMainMenu() = 0;
    virtual void ShowSampleForm() = 0;
    virtual void OnSampleRegistered(const SampleRecord& sample) = 0;
    virtual void OnError(const std::string& code, const std::string& detail) = 0;
    virtual void OnExit() = 0;
};
