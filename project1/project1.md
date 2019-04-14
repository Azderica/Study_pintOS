# Study_pintOS
School project. Using pintOS  project

운영체제 수업 및 프로젝트 진행을 위한 git입니다.<br>
This git is helpful for operating system and project progress.

------

## 1. Description

&nbsp; 이 프로젝트 과제의 목표는 간단한 운영 체제의 일부 기능을 구현하는 것입니다. 이 과제를 위해 우리는 80x86
아키텍처를위한 간단한 운영 체제 프레임 워크 인 Pintos 를 사용할 것입니다. Pintos 는 커널 스레드, 사용자
프로그램로드 및 실행, 파일 시스템과 같은 운영 체제의 주요 기능을 지원하지만 매우 간단한 방법으로 이러한
모든 기능을 구현합니다. 따라서 기능을 확장하고 가상 메모리를 구현하는 것이 목표입니다.

&nbsp; 세 가지 프로젝트가 있습니다. 첫 번째 프로젝트에서는 타이머가 적어도 x 타이머 틱까지 진행될 때까지 호출
스레드의 실행을 일시 중단하는 timer_sleep () 함수를 다시 구현합니다. 두 번째 프로젝트에서는 프로그램을
실행하는 데 필요한 인수 전달을 구현하고 시스템 호출 핸들러도 구현합니다. 세 번째 프로젝트에서는 페이징
및 스택 확장을 구현합니다. 이 프로젝트는 상당한 작업이 필요합니다. 각 프로젝트를 완료하는 평균 시간은 약
30-40 시간입니다. 모든 과제를 수행하는 것이 쉽지 않을지라도 운영 체제의 실제 구현에 대해 많은 것을 배울
수 있습니다.

## 2. Project Schedule
|  <center>Project</center> |  <center>Topic</center> |  <center>Sub-topic</center> |  <center>Due Date</center> |
|:--------|:--------|:--------|:--------|
|  <center>PJ1</center> |  <center>Threads</center> |  <center>Alarm clock</center> |  <center>04/19 </center> |
|  <center>PJ2</center> |  <center>User Program</center> |  <center>Augment passing, System call</center> |  <center>05/17</center> |
|  <center>PJ3</center> |  <center>Virtual Memory</center> |  <center>Paging, Stack Growing</center> |  <center>06/14</center> |

## 3. Pintos Resources
 >a. Stanford website for PintOS <br>
 >b. PintOS guides and tutorials will be available in LMS

## 4. 제출 지침
&nbsp; 제출을 위해 개인 git 저장소를 사용합니다. 그래서, git 에 대해 잘 알고 있어야합니다. 나중에 자세한 제출방법을 알려 드리겠습니다.

#### Late Day Policy
&nbsp; 이 프로젝트의 마감일은 오후 11 시 59 분입니다. 늦은 숙제에는 채점 벌칙이 적용됩니다..
늦게 제출 된 과제는 늦은 시간에 25 %의 벌점이 주어집니다.

#### Plagiarism
&nbsp; 표절은 용인되지 않습니다. 과제물이 독자적으로 작성되는 경우이를 존중하십시오. 강사가 그러한 사건 발생
가능성을 초과하는 상당한 유사성이 있다고 판단하면 2 명 (또는 그 이상)의 학생들에게 설명하고 아마도
강사의 재량에 따라 즉각적인 시험을 보게 됩니다. 그 학생의 능력은 문제가 되는 일과 관련이 있습니다.


------

## 1. Project 1: Thread

### 1. Description
>&nbsp;이 프로젝트에서 당신의 임무는 최소 기능 스레드 시스템의 기능을 확장하는 것입니다. 이 프로젝트의
"threads"디렉토리에서 주로 작업하게 될 것입니다. 자세한 정보는 PintOS 의 스레드 구현을 알기 위해
https://web.stanford.edu/~ouster/cgi-bin/cs140-winter13/pintos/pintos.pdf 의 배경 섹션 (2.1)을
읽으십시오.

>&nbsp;확장해야 할 함수는 'devices / timer.c'에 정의 된 timer_sleep ()입니다. time_sleep () 함수의 현재 버전이 작동
중입니다. 그러나 "busy waits"는 현재 시간을 확인하고 thread_yield ()를 호출 함을 의미합니다. 따라서 "busy
waiting"을 피하려면 timer_sleep ()을 다시 구현해야합니다.
void timer_sleep (int64_t ticks)

> 1. 시간이 적어도 x 타이머 틱까지 진행될 때까지 호출 스레드의 실행을 일시 중단합니다.
> 1. 시스템이 유휴 상태가 아니면, 스레드는 정확히 x tick 후에 깨어날 필요가 없습니다. 그들이 적당한 시간동안 기다린 후에는 대기열에 놓으십시오.
> 1. imer_sleep ()의 인수는 밀리 초 또는 다른 단위가 아닌 타이머 틱 단위로 표시됩니다. 초당 TIMER_FREQ
타이머 틱이 있습니다. TIMER_FREQ 는 devices / timer.h 에 정의 된 매크로입니다. 기본값은
100 입니다.이 값을 변경하면 많은 테스트가 실패하게 될 가능성이 있기 때문에이 값을 변경하지 않는
것이 좋습니다.

### 2. What you need to submit, 제출해야 할 사항
> 디자인 문서 (아래 5 절 참조)와 PintOS 소스 코드. Git Repository 로 제출할 때 PintOS 소스 코드의 "src /
threads"디렉토리에 디자인 문서를 복사해야한다.

### 3. How to evaluate your code.
> 1. We will evaluate your code with the following steps
 $ cd src/threads
 $ make
 $ cd build
 $ make check
> 1. Test results should be..
 alarm-single PASSED
 alarmmultiple PASSED
 alarmsimultaneous PASSED
 alarmzero PASSED
 alarm-negative PASSED

### 4. Useful Resource is available in LMS
> 1. PintOS installation tutorial (slides)
> 1. Project 1 guide (slides)

### 5. Documentation template
```
 ---- GROUP ----
 >> Fill in the names and email addresses of your group members.
 FirstName LastName <email@domain.example>
 FirstName LastName <email@domain.example> 
 FirstName LastName <email@domain.example>
 ---- PRELIMINARIES ----
 >> Describe briefly which parts of the assignment were implemented by each
 member of your team and specify the contribution between your member, say
 3:3:4, or 1:3:6.
 FirstName LastName: contribution
 FirstName LastName: contribution
 FirstName LastName: contribution
 ALARM CLOCK
 ===========
 ---- DATA STRUCTURES ----
 >> A1: Copy here the declaration of each new or changed `struct' or
 >> `struct' member, global or static variable, `typedef', or
 >> enumeration. Identify the purpose of each in 25 words or less.
 ---- ALGORITHMS ----
 >> A2: Briefly describe what happens in a call to timer_sleep(),
 >> including the effects of the timer interrupt handler.
 >> A3: What steps are taken to minimize the amount of time spent in
 >> the timer interrupt handler?
 ```
------

## 2. Project 2: User Program

------

## 3. Project 3: Virtual Memory

------
