# 언리얼 엔진 5 - C++ 인터페이스(Interface) 학습 일지

## 1. 프로젝트 개요
- **프로젝트명**: InterfacePractice
- **목표**: 캐릭터 체력이 감소할 때, 위젯과 인터페이스(`IHealthUIInterface`)를 통해 연동하는 시스템 구현
- **핵심 목표**: 객체지향 설계(느슨한 결합 / Decoupling)의 원리 이해 및 언리얼 C++ 인터페이스 활용법 체득

---

## 2. 핵심 개념 정리

### ① 인터페이스(Interface) vs 델리게이트(Delegate)
- **인터페이스 (Interface)**:
  - **비유**: C타입 충전 케이블, 리모컨
  - **방식**: 1 : 1 직통 명령 및 규격 강제.
  - **장점**: 반환값(Return Value)을 받을 수 있음, 다양한 액터와의 상호작용(E키 상호작용, 피격 시스템 등)에 최적.
  - **특징**: 호출자(캐릭터)가 대상 객체의 포인터를 알고 있어야 함.
- **델리게이트 (Delegate)**:
  - **비유**: 라디오 방송국, 유튜브 알림 설정 (옵저버 패턴)
  - **방식**: 1 : N 브로드캐스팅.
  - **장점**: 극강의 결합도 분리 (캐릭터는 위젯의 존재 자체를 몰라도 됨), 사운드/이펙트/업적 시스템 동시 구독 가능.
  - **특징**: 일방통행(반환값 받기 어려움), 구독(Bind) 및 해제(Unbind) 관리 필요.

---

### ② 언리얼 인터페이스의 이중 구조
- **`UHealthUIInterface` (`UInterface`)**:
  - 언리얼 엔진의 리플렉션, 가비지 컬렉션, 블루프린트 시스템 인식을 위한 메타데이터 클래스. 본체는 비워둠.
- **`IHealthUIInterface`**:
  - 개발자가 순수 C++에서 실제 가상 함수를 선언하고, 대상 클래스에서 다중 상속받아 구현하는 진짜 인터페이스 본체.

---

### ③ `BlueprintNativeEvent`와 `_Implementation` 규칙
- 인터페이스 헤더에서 `UFUNCTION(BlueprintNativeEvent)`로 선언 시:
  - **C++ 오버라이딩**: 함수명 뒤에 `_Implementation`을 반드시 붙여야 컴파일됨.
    - 예: `virtual void UpdateHealth_Implementation(...) override;`
  - **호출 방식**: 정적 헬퍼 함수인 `IHealthUIInterface::Execute_함수명(TargetObject, ...)` 형태로 호출.
  - **장점**: C++ 클래스뿐만 아니라 블루프린트 위젯(WBP)에서도 동일한 인터페이스 이벤트를 바로 구현 가능.

---

### ④ UMG 위젯 바인딩 (`meta = (BindWidgetOptional)`)
- C++ 위젯 클래스에 `UPROPERTY(meta = (BindWidgetOptional))`로 포인터 선언 시, 블루프린트 위젯(WBP) 디자이너에서 이름이 같은 위젯 컴포넌트(ProgressBar, TextBlock 등)가 자동으로 C++ 변수에 바인딩됨.

---

## 3. 진행 상황 체크리스트

- [x] **1단계**: `InterfacePractice.Build.cs`에 `"UMG"` 모듈 추가
- [x] **2단계**: `HealthUIInterface` 인터페이스 생성
  - `UpdateHealth(float CurrentHealth, float MaxHealth)`
  - `OnLowHealthWarning(bool bIsLowHealth)`
- [x] **3단계**: `MyCharacter` 구현
  - 체력 변수(`CurrentHealth`, `MaxHealth`) 관리
  - `ApplyDamageToSelf(float DamageAmount)` 로직 구현
  - `HealthWidgetInstance`에 `IHealthUIInterface::Execute_...`를 통해 신호 전달
- [ ] **4단계**: `HealthWidget` (C++ `UUserWidget`) 구현
  - `public IHealthUIInterface` 다중 상속
  - `UpdateHealth_Implementation`: 프로그레스바 및 텍스트 갱신
  - `OnLowHealthWarning_Implementation`: 체력 30% 이하 시 경고 텍스트 표시
- [ ] **5단계**: 에디터 및 인게임 테스트
  - `HealthWidget`을 부모로 하는 `WBP_HealthBar` 블루프린트 위젯 생성
  - 캐릭터에 위젯 클래스 지정 후 플레이(PIE)하여 피격 및 경고 동작 검증

---

## 4. 이후 작업 가이드 (다른 환경에서 이어갈 때)
- 본 문서를 확인한 후, **4단계 C++ 위젯(`HealthWidget`) 구현**부터 계속 진행합니다.
- 사용자가 직접 타이핑하며 실습할 수 있도록 코드 수정 권한은 사용자에게 위임하고, AI는 가이드 및 피드백 역할을 수행합니다.
