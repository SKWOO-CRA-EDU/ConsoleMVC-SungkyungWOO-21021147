#pragma once
#include "../../ports/IInputPort.h"

// IInputPort의 실제 구현: std::cin에서 한 줄을 읽는다.
// 저장소에서 iostream을 참조하는 두 곳(Input/Output Adapter) 중 하나.
class ConsoleInputAdapter : public IInputPort {
public:
    std::optional<std::string> NextLine() override;
};
