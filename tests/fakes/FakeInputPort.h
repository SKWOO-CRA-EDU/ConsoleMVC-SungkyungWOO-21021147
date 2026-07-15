#pragma once
#include <deque>
#include <string>
#include <vector>
#include "../../src/ports/IInputPort.h"

// 테스트용 가짜 입력원: 미리 정해진 "키 입력 시퀀스"를 그대로 재생한다.
class FakeInputPort : public IInputPort {
public:
    explicit FakeInputPort(std::vector<std::string> lines);
    std::optional<std::string> NextLine() override;

private:
    std::deque<std::string> lines_;
};
