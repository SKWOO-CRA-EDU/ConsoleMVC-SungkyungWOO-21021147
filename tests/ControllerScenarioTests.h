#pragma once

// 키 입력 시퀀스를 FakeInputPort로 주입하고, RecordingOutputPort/Repository에
// 무엇이 일어났는지를 단언하는 시나리오 테스트 모음.
// 반환값: 실패한 단언(assert) 개수. 0이면 전체 통과.
int RunControllerScenarioTests();
