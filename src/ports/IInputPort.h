#pragma once
#include <optional>
#include <string>

// 입력원 경계: 콘솔이든 테스트든 "다음 한 줄"만 제공하면 된다.
// 도메인/Controller는 이 인터페이스만 알고, 입력이 어디서 오는지 알지 못한다.
class IInputPort {
public:
    virtual ~IInputPort() = default;
    virtual std::optional<std::string> NextLine() = 0;
};
