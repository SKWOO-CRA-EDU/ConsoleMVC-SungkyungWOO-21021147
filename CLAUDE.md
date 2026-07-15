# CLAUDE.md — ConsoleMVC PoC

이 저장소는 개인과제 PoC이며 독립적으로 평가된다. 근거 문서: `docs/CONTRACT.md`, `docs/PRD.md`.

## 빌드/테스트 (단일 커맨드)

```
powershell -File scripts/run.ps1
```

`scripts/run.ps1`은 (구현 단계에서 작성) MSBuild 빌드 → headless 실행 → 출력 자동 검증까지 수행하고,
성공 시 종료코드 0, 실패 시 0이 아닌 코드를 반환한다(PRD FR-07). 이 스크립트가 존재하기 전까지는
이 문서에 기재된 계약일 뿐 구현 완료를 의미하지 않는다.

MSBuild 직접 호출이 필요한 경우(디버깅용):
```
msbuild ConsoleMVC.vcxproj /p:Configuration=Release /p:Platform=x64
```

## 계약 수정 금지

`docs/CONTRACT.md`는 타 저장소(SampleOrderSystem 등)에서 확정되어 4개 PoC 저장소에 동일 사본으로
배포된 문서다. **이 저장소에서 CONTRACT.md의 내용을 수정하지 않는다.** 필드명·타입·열거값·포맷·
인터페이스 시그니처는 계약을 글자 그대로 따른다.

계약을 고쳐야 할 이유를 발견하면(예: 계약이 PRD의 명제를 만족시키기 불가능하게 만드는 경우) 코드로
우회하지 말고, 그 사실을 사용자에게 보고하고 작업을 멈춘다.

## 커밋 규칙

- Conventional Commits 형식 사용: `feat:`, `fix:`, `docs:`, `refactor:`, `test:` 등.
- 1커밋 = 1논리적 변경. 여러 FR을 한 커밋에 섞지 않는다.
- 커밋 메시지 또는 본문에 관련 FR-ID를 명시한다 (예: `feat: add IView interface (FR-03)`).

## 범위 규율

- `docs/PRD.md`의 In scope(S1~S6)만 구현한다.
- **PRD의 비범위(Out of scope) 목록에 있는 것을 구현하면 실패다.** 특히 CONTRACT.md §4/§6의 업무
  로직, 실제 파일 영속화, Repository 구현체는 이 저장소의 책임이 아니다(계약 §5: "선언만, 구현
  금지").
- 구현 중 PRD에 없는 요구를 발견하면 임의로 범위를 넓히지 말고 먼저 보고한다.
