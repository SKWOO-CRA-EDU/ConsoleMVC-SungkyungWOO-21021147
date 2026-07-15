# ConsoleMVC PoC

## 이 PoC가 증명하는 명제

> 콘솔 앱을 사람 없이 headless로 자동 실행·검증할 수 있고, View 구현체를 교체해도 Model/Controller 소스는 한 줄도 바뀌지 않는다.

(근거: `docs/PRD.md` §0)

## 이 저장소가 담당하는 위치

이 계약(`docs/CONTRACT.md`)은 4개의 독립 PoC 저장소에 동일 사본으로 배포된다.

| 저장소 | 역할 |
|---|---|
| SampleOrderSystem | 계약 원본 확정·개정 (Repository 인터페이스, 데이터 모델, 상태 전이) |
| **ConsoleMVC (이 저장소)** | 계약을 **선언만** 그대로 가져와, Model/Controller/View 3계층 분리와 View 교체 가능성을 증명 |
| DataPersistence | 계약의 Repository 인터페이스를 실제 파일 영속화로 **구현** |
| DataMonitor | 계약의 Repository를 읽기 전용으로 조회하는 모니터링 도구 |
| DummyDataGenerator | 계약 포맷에 맞는 테스트 데이터 생성 |

이 저장소는 Repository의 **실제 동작**(파일 저장, CRUD 실행)에는 관여하지 않는다 — 계약 §7이 "선언만, 구현 금지"를 명시하기 때문이다. 이 저장소가 담당하는 것은 오직 **Model↔Controller↔View 분리**와 **headless 실행/검증 가능성**뿐이다.

## 빌드 · 테스트 · 실행

### 단일 커맨드 (빌드 → self-test → 두 View headless 실행까지 한 번에)

```
powershell -File scripts/run.ps1
```

성공 시 종료코드 0, 실패 시 0이 아닌 코드를 반환한다.

### 개별 실행 예시

MSBuild 직접 호출(디버깅용):
```
msbuild ConsoleMVC.vcxproj /p:Configuration=Release /p:Platform=x64
```

자가 테스트만 실행:
```
x64\Release\ConsoleMVC.exe --self-test
```

기본 View(사람이 읽는 형식)로 headless 실행:
```
x64\Release\ConsoleMVC.exe < NUL
```
```
[MENU] 1) Register sample   0) Exit
bye
```

대체 View(View-B, `event=` 형식)로 headless 실행 — Model/Controller 소스 변경 없이 View만 교체:
```
x64\Release\ConsoleMVC.exe --view=plain < NUL
```
```
event=main_menu
event=exit
```

## 무엇을 의도적으로 만들지 않았는가 (비범위)

`docs/PRD.md` §2에 근거한 비범위 목록. 각 항목은 "증명할 명제와 무관하거나, 계약이 이미 타 저장소 책임으로 확정했기 때문"에 제외한다.

| 항목 | 만들지 않은 이유 |
|---|---|
| CONTRACT.md §4 상태 전이(T1~T6) 실제 업무 로직 | 명제(headless 실행·View 교체)와 무관. 계약은 선언 참조만으로 충분 |
| CONTRACT.md §8 계산 규칙(수율/부족분/생산시간 등) | 동일 |
| 실제 파일 영속화(저장/로드/원자적 교체/스키마 마이그레이션) | 계약 §7이 Repository를 "선언만, 구현 금지"로 명시 — 인메모리 스텁으로 충분 |
| Repository 인터페이스의 실동작 구현 | DataPersistence 저장소의 책임 |
| 다중 사용자·동시성·멀티스레드 | 단일 프로세스 headless 실행이면 명제 증명에 충분 |
| 입력 검증/예외 처리 전반(복구, 재시도 UX) | 명제는 정상 경로의 자동 실행·검증만 다룸 |
| GUI/웹/네트워크 인터페이스 | 명제가 "콘솔 앱"으로 한정 |
| 인증/권한/보안 | 해당 명제와 무관 |
| 로깅 프레임워크·다국어·성능 최적화 | 명제와 무관한 비기능 요구 |
| CI/CD 파이프라인·배포 자동화 | 로컬 단일 커맨드(`scripts/run.ps1`)로 재현 가능하면 충분 |
| DataMonitor/DummyDataGenerator 등과의 실제 통합 | 각 PoC 저장소는 독립적으로 평가됨 |
| CONTRACT.md 자체의 수정·확장 | 타 저장소(SampleOrderSystem)에서만 개정되는 계약. 이 저장소는 읽기 전용 사본만 보유 |
| 3개 초과의 View 구현체 / 3개 초과의 Model 엔티티 | View 교체 가능성 증명에는 최소 2개 View면 충분 |
| Sample/Order 등록의 전량 CRUD 시나리오 | 자동 실행·검증 가능성 증명에는 대표 경로 1개면 충분 |

## 문서

- `docs/CONTRACT.md` — 데이터 모델/영속 포맷/Repository 인터페이스 계약(읽기 전용 사본, SampleOrderSystem에서 개정)
- `docs/PRD.md` — 이 저장소의 범위·기능 요구사항
- `CLAUDE.md` — 이 저장소에서 작업할 때 지켜야 할 규율(계약 수정 금지, 커밋 규칙, 범위 규율)
