#pragma once
#include <string>
#include "../ports/IInputPort.h"
#include "../ports/IOutputPort.h"
#include "../ports/ISampleRepository.h"
#include "../ports/IOrderRepository.h"

// Controller: 입력 한 줄을 받아 메뉴 상태를 전이시키고, 결과를 IOutputPort로 통지한다.
// Port 인터페이스에만 의존하며 iostream을 알지 못한다.
class AppController {
public:
    AppController(IInputPort& input, IOutputPort& output,
                  ISampleRepository& samples, IOrderRepository& orders);

    // NextLine()이 더 이상 값을 주지 않거나(EOF) exit 명령을 받을 때까지 반복한다.
    void Run();

private:
    enum class State { MainMenu, SampleForm };

    bool HandleLine(const std::string& line);
    bool HandleMainMenu(const std::string& line);
    bool HandleSampleForm(const std::string& line);
    static bool TryParseSample(const std::string& line, SampleRecord& out);

    IInputPort& input_;
    IOutputPort& output_;
    ISampleRepository& samples_;
    IOrderRepository& orders_;
    State state_ = State::MainMenu;
};
