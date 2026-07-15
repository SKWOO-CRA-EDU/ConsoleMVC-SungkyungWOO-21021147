#include "ControllerScenarioTests.h"
#include <iostream>
#include "fakes/FakeInputPort.h"
#include "fakes/RecordingOutputPort.h"
#include "../src/app/AppController.h"
#include "../src/infra/repository/InMemorySampleRepository.h"
#include "../src/infra/repository/InMemoryOrderRepository.h"

namespace {

int g_failures = 0;

void Expect(bool condition, const std::string& message) {
    if (!condition) {
        std::cerr << "[FAIL] " << message << std::endl;
        ++g_failures;
    }
}

// 시나리오: 메인 메뉴 -> 샘플 등록 -> 종료. Controller가 저장소에 정확히
// 반영하고, 출력 Port에 SampleRegistered 이벤트를 통지했는지 단언한다.
void TestValidSampleRegistration() {
    FakeInputPort input({"1", "S1,Sample One,2.5,9000,10", "0"});
    RecordingOutputPort output;
    InMemorySampleRepository samples;
    InMemoryOrderRepository orders;
    AppController controller(input, output, samples, orders);

    controller.Run();

    Expect(samples.Exists("S1"), "sample S1 should be registered in repository");

    bool foundRegisteredEvent = false;
    for (const auto& e : output.events) {
        if (e.kind == RecordedEvent::Kind::SampleRegistered && e.sample.sampleId == "S1") {
            foundRegisteredEvent = true;
            Expect(e.sample.name == "Sample One", "registered sample name mismatch");
            Expect(e.sample.yieldNumerator == 9000, "registered sample yieldNumerator mismatch");
            Expect(e.sample.stockQuantity == 10, "registered sample stockQuantity mismatch");
        }
    }
    Expect(foundRegisteredEvent, "OnSampleRegistered event should be emitted for S1");
    Expect(!output.events.empty() && output.events.back().kind == RecordedEvent::Kind::Exit,
           "last event should be Exit");
}

// 시나리오: 메인 메뉴에서 잘못된 명령 -> UNKNOWN_COMMAND 에러 이벤트.
void TestUnknownCommandAtMainMenu() {
    FakeInputPort input({"zzz", "0"});
    RecordingOutputPort output;
    InMemorySampleRepository samples;
    InMemoryOrderRepository orders;
    AppController controller(input, output, samples, orders);

    controller.Run();

    bool foundError = false;
    for (const auto& e : output.events) {
        if (e.kind == RecordedEvent::Kind::Error && e.errorCode == "UNKNOWN_COMMAND") {
            foundError = true;
            Expect(e.errorDetail == "zzz", "error detail should echo the offending input");
        }
    }
    Expect(foundError, "unknown command should raise UNKNOWN_COMMAND error event");
}

// 시나리오: 샘플 등록 폼에서 'back' -> 메인 메뉴로 복귀, 저장소 변경 없음.
void TestBackNavigation() {
    FakeInputPort input({"1", "back", "0"});
    RecordingOutputPort output;
    InMemorySampleRepository samples;
    InMemoryOrderRepository orders;
    AppController controller(input, output, samples, orders);

    controller.Run();

    Expect(samples.FindAll().empty(), "back navigation should not register any sample");

    int mainMenuShownCount = 0;
    for (const auto& e : output.events) {
        if (e.kind == RecordedEvent::Kind::MainMenuShown) ++mainMenuShownCount;
    }
    Expect(mainMenuShownCount >= 2, "main menu should be shown again after 'back'");
}

// 시나리오: 잘못된 형식의 샘플 입력 -> INVALID_SAMPLE_INPUT, 이후 올바른 입력은 정상 등록.
void TestInvalidSampleInputThenValid() {
    FakeInputPort input({"1", "bad-data", "S2,Two,1.0,10000,0", "0"});
    RecordingOutputPort output;
    InMemorySampleRepository samples;
    InMemoryOrderRepository orders;
    AppController controller(input, output, samples, orders);

    controller.Run();

    bool foundInvalid = false;
    bool foundRegistered = false;
    for (const auto& e : output.events) {
        if (e.kind == RecordedEvent::Kind::Error && e.errorCode == "INVALID_SAMPLE_INPUT") {
            foundInvalid = true;
        }
        if (e.kind == RecordedEvent::Kind::SampleRegistered && e.sample.sampleId == "S2") {
            foundRegistered = true;
        }
    }
    Expect(foundInvalid, "malformed sample line should raise INVALID_SAMPLE_INPUT");
    Expect(foundRegistered, "subsequent valid line should still register S2");
}

}  // namespace

int RunControllerScenarioTests() {
    g_failures = 0;
    TestValidSampleRegistration();
    TestUnknownCommandAtMainMenu();
    TestBackNavigation();
    TestInvalidSampleInputThenValid();
    return g_failures;
}
