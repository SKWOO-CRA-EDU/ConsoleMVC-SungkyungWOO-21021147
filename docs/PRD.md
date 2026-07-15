# PRD — ConsoleMVC PoC

> 근거: 아래 명제(가설), `docs/CONTRACT.md`. 그 외 문서/추정 근거 없음.
> 본 저장소는 개인과제 PoC이며 독립적으로 평가된다. CONTRACT.md는 타 저장소에서 확정된 계약으로 본 저장소에서 수정 금지.

## 0. 증명할 명제

> 콘솔 앱을 사람 없이 자동 실행하고 결과를 검증할 수 있다.
> View를 교체해도 Model과 Controller는 한 줄도 바뀌지 않는다.

이 PoC는 위 두 가지 성질(headless 자동 실행·검증 가능성, View 교체에 대한 Model/Controller 불변성)만 증명한다. 그 외 모든 것은 비범위다.

## 1. 범위 (In scope)

| ID | 항목 |
|---|---|
| S1 | 콘솔 앱을 사람의 개입 없이 실행하고, 표준출력/종료코드로 결과를 확인 가능한 최소 실행 경로 |
| S2 | 그 결과를 자동화된 스크립트/테스트로 검증(assert) 가능한 형태로 출력 |
| S3 | Model, Controller, View를 별도 컴파일 단위(클래스/인터페이스)로 분리한 최소 MVC 골격 |
| S4 | CONTRACT.md에 정의된 SampleRecord/OrderRecord 필드명·타입, ISampleRepository/IOrderRepository 시그니처를 그대로 사용하는 Model 계층 |
| S5 | 최소 2개의 View 구현체(예: 콘솔 출력 View, 테스트용/대체 View)를 교체하여 실행 — 교체 시 Model/Controller 소스 diff가 0줄임을 증명 |
| S6 | 위 내용을 재현하는 단일 빌드 명령 |

## 2. 비범위 (Out of scope)

| ID | 항목 | 사유 |
|---|---|---|
| O1 | CONTRACT.md §4 상태 전이표(T1~T6)의 실제 업무 로직 구현 | 명제와 무관, 계약은 선언 참조만으로 충분 |
| O2 | CONTRACT.md §6 계산 규칙(ShortageQuantity, ActualProductionQuantity, TotalProductionTime, 재고 반영량) 구현 | 동일 |
| O3 | 실제 파일 영속화(저장/로드, 원자적 교체, schemaVersion 마이그레이션) | Repository는 계약상 "구현 금지"(선언만) — 인메모리/스텁으로 충분 |
| O4 | Repository 인터페이스의 실동작 구현(DataPersistence 등 타 저장소 책임) | 계약 §5는 "선언만, 구현 금지" 명시 |
| O5 | 다중 사용자·동시성·멀티스레드 처리 | 단일 프로세스 headless 실행으로 충분 |
| O6 | 입력 검증·예외 처리 전반(잘못된 입력 복구, 재시도 UX) | 명제는 정상 경로 자동 실행/검증만 다룸 |
| O7 | GUI/웹/네트워크 인터페이스 | "콘솔 앱" 한정 |
| O8 | 인증/권한/보안 | 해당 없음 |
| O9 | 로깅 프레임워크, 다국어 지원, 성능 최적화 | 명제와 무관한 비기능 요구 |
| O10 | CI/CD 파이프라인, 배포 자동화 | 로컬 빌드/테스트 1커맨드로 충분 |
| O11 | DataMonitor/DummyDataGenerator 등 타 3개 PoC 저장소와의 실제 통합 | 각 저장소 독립 평가 대상 |
| O12 | CONTRACT.md 자체의 수정·확장 | 타 저장소 확정 계약, 본 저장소에서 변경 금지 |
| O13 | 3개 초과의 View 구현체, 3개 초과의 Model 엔티티 | 명제 증명에 필요한 최소 개수(2개 View)면 충분 |
| O14 | Sample/Order 등록 UI의 다양한 시나리오(전량 CRUD) | 자동 실행·검증 가능성 증명에는 대표 경로 1개면 충분 |

## 3. 기능 요구사항 (FR)

### FR-01 콘솔 앱 headless 실행
사람의 키보드 입력 없이 프로세스가 시작되어 종료된다.

- **Given** 빌드된 실행 파일이 존재한다
- **When** 표준입력을 연결하지 않고(또는 빈 입력으로) 실행한다
- **Then** 프로세스는 대기(hang) 없이 0(성공) 또는 정의된 0이 아닌 종료코드로 종료한다

### FR-02 자동 검증 가능한 출력
실행 결과를 사람이 육안으로 보지 않고도 스크립트가 판정할 수 있다.

- **Given** FR-01의 headless 실행이 완료되었다
- **When** 표준출력을 캡처한다
- **Then** 사전에 정의된 문자열/패턴이 출력에 포함되어 있는지를 스크립트(exit code 또는 문자열 비교)로 판정할 수 있다

### FR-03 Model/Controller/View 분리
Model, Controller, View는 서로 다른 컴파일 단위(클래스)로 존재하며, View는 인터페이스를 통해서만 Controller와 연결된다.

- **Given** 소스 트리에 Model, Controller, View 클래스가 각각 존재한다
- **When** View 인터페이스를 조회한다
- **Then** Controller는 View의 구체 타입이 아닌 View 인터페이스(추상 타입)에만 의존한다

### FR-04 CONTRACT.md 데이터 모델 준수
Model 계층은 CONTRACT.md §1.2/§1.3/§5에 정의된 필드명·타입·시그니처를 글자 그대로 사용한다.

- **Given** CONTRACT.md의 SampleRecord/OrderRecord 구조체, ISampleRepository/IOrderRepository 선언이 존재한다
- **When** 본 저장소의 Model 코드를 CONTRACT.md와 대조한다
- **Then** 필드명, 타입, 인터페이스 시그니처가 한 글자도 다르지 않다

### FR-05 View 교체 시 Model/Controller 불변
View 구현체를 교체해도 Model과 Controller 소스 파일은 수정되지 않는다.

- **Given** View 인터페이스를 구현하는 View-A(콘솔 출력)와 View-B(대체 구현) 두 개가 존재한다
- **When** 실행 시 사용하는 View를 View-A에서 View-B로 교체한다(교체 지점은 View 생성/주입 코드 1곳으로 한정)
- **Then** Model/Controller 소스 파일의 git diff는 0줄이다

### FR-06 두 View 각각에 대한 headless 자동 검증
View-A, View-B 각각으로 실행했을 때도 FR-01/FR-02가 성립한다.

- **Given** View-A 또는 View-B로 빌드/실행 설정이 되어 있다
- **When** 각각 headless로 실행하고 출력을 캡처한다
- **Then** 두 경우 모두 정의된 종료코드와 검증 가능한 출력을 만족한다

### FR-07 단일 명령 재현
전체 증명 과정(빌드→headless 실행→자동 검증)은 문서화된 단일 명령으로 재현 가능하다.

- **Given** 저장소를 새로 clone한 환경이다
- **When** CLAUDE.md에 기술된 빌드/테스트 명령 1개를 실행한다
- **Then** 빌드, headless 실행, 자동 검증까지 사람의 추가 개입 없이 완료되고 성공/실패가 종료코드로 드러난다
