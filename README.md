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
### 1. Description
>&nbsp;이 프로젝트에서 사용자 프로그램을 실행하기 위해 PintOS를 확장하는 것이 당신의 임무입니다. PintOS에서 한 번에 하나 이상의 프로세스를 실행할 수 있습니다. PintOS는 한 번에 여러 프로세스를 로드하고 실행할 수 있어야합니다. 프로젝트 1에서는 테스트 코드를 커널에 직접 컴파일했습니다. 그래서 우리는 PintOS를 확장하여 특정 사용자 프로그램 인터페이스 (시스템 호출 인터페이스)를 제공해야합니다. 자세한 내용은 다음 웹 사이트의 공식 Pintos 설명서를 참조하십시오.<br>
https://web.stanford.edu/class/cs140/projects/pintos/pintos_1.html 

### 2. What to do
#### a. Part 1 : 
>&nbsp; 인수 전달 및 설치 스택 사용자 프로그램의 파일 이름을 분석하고 스택을 올바르게 설정하는 기능을 지원하십시오. 주로 src / userprog / process.c에서 작업하게 될 것입니다.

#### b. Part 2 :
>&nbsp; 시스템 호출 src / usrprog / syscall.h 및 src / usrprog / syscall.c에 필요한 기능을 구현합니다

### 3. Recommended order of implementation for this project
##### a. 무한 루프로 process_wait () 변경
##### b. 인수 전달 및 설정 스택 
##### c. 시스템 콜 인프라 사용자 스택에서 시스템 호출 번호를 읽고 이를 기반으로 시스템 호출 핸들러를 호출하는 코드를 구현하십시오.
##### d. exit () 시스템 호출  
##### e. write () 시스템 호출  
##### f. 다른 시스템 호출
>&nbsp; 'useprog / syscall.c'에 시스템 호출 핸들러를 구현하십시오. 파일의 각 시스템 호출에 대한 골격 구현이 있습니다. 시스템 호출 번호, 시스템 호출 인수를 검색하고 적절한 조치를 취하는 방식으로 각 시스템 호출 핸들러를 구현해야 합니다. 각 시스템 호출에 대한 시스템 호출 번호는 'lib / syscall-nr.h'에 정의되어 있습니다.
###### 구현해야 하는 시스템 호출 목록
>&nbsp; halt(), exit(), exec(), wait(), create(), remove(), open(), filesize(), read(), write(), seek(), tell(), close() 시스템 호출에 대한 자세한 내용은 Stanford Pintos 문서의 3.3.4 섹션 <br>
(https://web.stanford.edu/~ouster/cgi-bin/cs140-winter13/pintos/pintos.pdf).
##### g. 실행 파일에 쓰기 거부
>&nbsp; 실행 파일로 사용 중인 파일에 대한 쓰기를 거부하는 코드를 추가하십시오. file_deny_write ()를 사용하여 열린 파일에 대한 쓰기를 방지할 수 있습니다. 

### 4. Background (Contents are mainly from Stanford Pintos documents)
#### 1. 파일시스템 사용
>&nbsp; 이 프로젝트의 경우 사용자 프로그램이 파일 시스템에서 로드되기 때문에 파일 시스템에 인터페이스 해야 합니다. 'filesys.h'와 'file.h'인터페이스를 살펴봄으로써 파일 시스템을 사용하는 방법을 알 수 있습니다. 파일 시스템의 현재 구현은 매우 간단하며 몇 가지 제한 사항이 있습니다. 그러나 이 프로젝트만으로 충분합니다. <br>
>&nbsp; 이 프로젝트의 경우 파일 시스템 파티션이 있는 시뮬레이트 된 디스크가 필요합니다. 따라서 파일 시스템이 있는 시뮬레이션 된 디스크를 만들고 파일 시스템으로 포맷하고 새 디스크에 프로그램을 복사한 후 다음 명령 줄을 사용하여 프로그램을 실행해야 합니다. <br>

```
$ cd userprog/build
$ pintos-mkbuild filesys.dsk --filesys-size=2 //create a simulated disk
$ pintos -f -q //format
$ pintos -p ../../examples/echo -a echo -- -q //copy “echo” program into the new disk
$ pintos -q run ‘echo x’ //run the “echo” program 
```

#### b. 사용자 프로그램 작동 방법
>&nbsp; Pintos는 메모리에 맞고 이 프로젝트에서 구현 한 시스템 호출 만 사용하면 일반 C 프로그램을 실행할 수 있습니다. <br>
>&nbsp; 'src / examples'디렉토리에는 Pintos에서 실행할 수 있는 일부 사용자 프로그램이 들어 있습니다. 디렉토리에 제공된 Makefile을 사용하여 예제 프로그램을 컴파일 할 수 있습니다. <br>
>&nbsp; Pintos는 'userprog / process.c'에 제공된 로더로 ELF 실행 파일을 로드 할 수 있습니다. ELF는 오브젝트 파일, 공유 라이브러리 및 실행 파일에 대해 Linux, Solaris 및 기타 여러 운영 체제에서 사용되는 파일 형식입니다. <br>

#### c. 가상 메모리 레이아웃
>&nbsp; Pintos의 가상 메모리는 사용자 가상 메모리와 커널 가상 메모리의 두 영역으로 구분됩니다. 사용자 가상 메모리의 범위는 가상 주소 0에서 'threads / vaddr.h'에 정의 된 PHYS_BASE까지입니다. <br>
>&nbsp; 커널 가상 메모리의 범위는 PHYS_BASE에서 4GB입니다. 사용자 가상 메모리는 프로세스별로 있습니다. 따라서 컨텍스트 전환 시 Pintos는 프로세서의 페이지 디렉토리 기준 레지스터를 변경하여 사용자 가상 주소 공간을 전환합니다. 반면에 커널 가상 메모리는 전역 적입니다. 즉, 실행중인 사용자 프로세스에 관계없이 물리적 메모리에 일대일로 매핑됩니다. <br>
>&nbsp; Pintos에서 가상 주소 PHYS_BASE는 실제 주소 0에 액세스하고 가상 주소 PHYS_BASE + 0x1234는 실제 COMP312005 Operating System, Spring 2019  주소 0x1234에 액세스합니다.   사용자 프로세스는 자체 가상 메모리에만 액세스 할 수 있습니다. 커널 스레드는 커널 가상 메모리와 사용자 가상 메모리에 모두 액세스 할 수 있습니다. 다음 그림은 일반적인 사용자 가상 메모리 레이아웃을 보여줍니다.  이 프로젝트에서는 사용자 스택과 초기화되지 않은 데이터 세그먼트의 크기가 고정되어 있습니다. Pintos의 코드 세그먼트는 사용자 가상 주소 0x08048000에서 시작합니다 (주소 공간의 맨 아래에서 약 128MB).  <br>

### 5. What you need to submit
#### a. 디자인 문서
>&nbsp; (아래 섹션 7 참조) 디자인 문서를 제출해야 합니다. 설계 문서는 채점을 위한 중요한 부분 중 하나입니다. 따라서 설계 문서를 잘 작성하십시오. 프로젝트의 솔루션을 더 잘 이해하고 Pintos에 대한 이해를 테스트하는 데 도움이 됩니다. 7 절에서 디자인 문서 템플릿을 찾을 수 있습니다. <br>

#### b. PintOS 소스 코드.
>&nbsp; * 주의! * : 사용자 프로세스가 종료 될 때마다 종료 메시지를 인쇄합니다. 최종 제출 된 코드는 종료 메시지를 제외한 다른 메시지 (예 : 디버깅 메시지)를 인쇄해서는 안됩니다..  <br>

### 6. How to evaluate your code
```
$ cd src/userprog
$ make
$ cd build
$ make SIMULATOR=--boch check

Expected result
tests/userprog/args-none
tests/userprog/args-single
tests/userprog/args-multiple
tests/userprog/args-many
tests/userprog/args-dbl-space
tests/userprog/sc-bad-sp
tests/userprog/sc-bad-arg
tests/userprog/sc-boundary
tests/userprog/sc-boundary-2
tests/userprog/halt
tests/userprog/exit
tests/userprog/create-normal
tests/userprog/create-empty
tests/userprog/create-null
tests/userprog/create-bad-ptr
tests/userprog/create-long
tests/userprog/create-exists
tests/userprog/create-bound
tests/userprog/open-normal
tests/userprog/open-missing
tests/userprog/open-boundary
tests/userprog/open-empty
tests/userprog/open-null
tests/userprog/open-bad-ptr
tests/userprog/open-twice
tests/userprog/close-normal
tests/userprog/close-twice
tests/userprog/close-stdin
tests/userprog/close-stdout
tests/userprog/close-bad-fd
tests/userprog/read-normal
tests/userprog/read-bad-ptr
tests/userprog/read-boundary
tests/userprog/read-zero
tests/userprog/read-stdout
tests/userprog/read-bad-fd
tests/userprog/write-normal
tests/userprog/write-bad-ptr
tests/userprog/write-boundary
tests/userprog/write-zero
tests/userprog/write-stdin
tests/userprog/write-bad-fd
tests/userprog/exec-once
tests/userprog/exec-arg
tests/userprog/exec-multiple
tests/userprog/exec-missing
tests/userprog/exec-bad-ptr
tests/userprog/wait-simple
tests/userprog/wait-twice
tests/userprog/wait-killed
tests/userprog/wait-bad-pid
 ```
 
### 7. How to evaluate your code
 ```
---- GROUP ----
Fill in the names and email addresses of your group members.
FirstName LastName <email@domain.example>
FirstName LastName <email@domain.example>
FirstName LastName email@domain.example
---- PRELIMINARIES ----
Describe briefly which parts of the assignment were implemented by each member
of your team and specify the contribution between your member, say 3:3:4, or
1:3:6.
FirstName LastName: contribution
FirstName LastName: contribution
FirstName LastName: contributionCOMP312005 Operating System, Spring 2019
ARGUMENT PASSING
================
---- DATA STRUCTURES ----
A1: Copy here the declaration of each new or changed `struct' or `struct'
member, global or static variable, `typedef', or enumeration. Identify the
purpose of each in 25 words or less.
---- ALGORITHMS ----
A2: Briefly describe how you implemented argument parsing. How do you arrange
for the elements of argv[] to be in the right order? How do you avoid
overflowing the stack page?
SYSTEM CALLS
============
---- DATA STRUCTURES ----
B1: Copy here the declaration of each new or changed `struct' or `struct'
member, global or static variable, `typedef', or enumeration. Identify the
purpose of each in 25 words or less.
B2: Describe how file descriptors are associated with open files. Are file
descriptors unique within the entire OS or just within a single process?
---- ALGORITHMS ----
B3: Describe your code for reading and writing user data from the kernel.
B4: Briefly describe your implementation of each system call.
 ```
------

## 3. Project 3: Virtual Memory
### 1. Description
>&nbsp;이제 Pintos의 내부 동작에 대해 어느 정도 익숙해 져야 합니다. OS는 적절한 동기화로 여러 스레드 실행을 적절히 처리 할 수 ​​있으며 여러 사용자 프로그램을 동시에 로드 할 수 있습니다.<br>
그러나 실행할 수있는 프로그램의 수와 크기는 시스템의 주 메모리 크기에 의해 제한됩니다. <br>
이 과제에서는 해당 제한을 제거합니다.<br>
이 과제는 마지막 과제 위에(즉, 프로젝트 2에 이어서) 작성하게 됩니다. <br>
프로젝트 2의 테스트 프로그램도 프로젝트 3에서 작동해야 합니다. 그러므로 프로젝트 3에서 작업을 시작하기 전에 프로젝트 2 제출의 모든 버그를 수정해야 할 것입니다. 왜냐하면 그 버그가 프로젝트 3에서 동일한 문제를 일으킬 가능성이 크기 때문입니다.<br>
이전 할당에서와 같은 방법으로 Pintos 디스크 및 파일 시스템을 계속 처리합니다 (섹션 3.1.2 [파일 시스템 사용], 23 페이지 참조).<br>

### 2. Background (Contents are mainly from Stanford Pintos documents)
#### 1. Source Files
>&nbsp; 이 프로젝트의 'vm' 디렉토리 에서 작업하게 됩니다. 'vm' 디렉토리는 'Makefile'만 포함합니다. 'userprog'의 유일한 변경 사항은 이 새로운 'Makefile'이 '-DVM' 설정을 활성화한다는 것입니다.<br>
작성한 모든 코드는 새 파일이나 이전 프로젝트에 도입된 파일에 있습니다. 아마도 처음에는 몇 개의 파일 만 보게 될 것입니다 : <br>
'devices / block.h'<br>
'devices / block.c'<br>
블록 장치에 대한 섹터 기반 읽기 및 쓰기 액세스를 제공합니다. 이 인터페이스를 사용하여 스왑 파티션에 블록 장치로 액세스합니다.<br>

#### 2.메모리 용어
>&nbsp; 가상 메모리에 대한 논의가 혼동되지 않도록 주의 깊게 정의해야합니다. 따라서 우리는 메모리와 스토리지에 대한 용어를 제시하는 것으로 시작합니다. 이 용어 중 일부는 프로젝트 2에서 익숙하면 좋겠지만 (섹션 3.1.4 [가상 메모리 레이아웃], 25 페이지 참조), 그 외에 많은 부분은 새로운 것입니다.

##### 1. 페이지
>&nbsp; 가상 페이지라고도하는 페이지는 가상 메모리의 연속 영역으로 4,096 바이트 (페이지 크기)의 길이입니다. 페이지는 페이지 정렬 되어야합니다. 즉, 페이지 크기로 균등하게 나눌 수 있는 가상 주소에서 시작해야합니다.<br>
따라서 32 비트 가상 주소는 다음과 같이 20 비트 페이지 번호와 12 비트 페이지 오프셋 (또는 단지 오프셋)으로 나눌 수 있습니다.<br>
>&nbsp; 각 프로세스는 독립적인 사용자 (가상) 페이지 집합을 가지고 있는데, 이 페이지는 가상 주소 PHYS_BASE (일반적으로 0xc0000000 (3GB)) 아래에 있는 페이지입니다.<br>
>&nbsp; 반면, 커널 (가상) 페이지 세트는 전역이며, 어떤 스레드 또는 프로세스가 활성 상태이든 관계없이 동일합니다.<br>
>&nbsp; 커널은 사용자 및 커널 페이지에 모두 액세스 할 수 있지만 사용자 프로세스는 자체 사용자 페이지에만 액세스 할 수 있습니다. 자세한 내용은 섹션 3.1.4 [가상 메모리 레이아웃], 25 페이지를 참조하십시오.<br>
Pintos는 가상 주소로 작업하기 위한 몇 가지 유용한 기능을 제공합니다. 자세한 내용은 A.6 절 [가상 주소], 77 페이지를 참조하십시오.<br>

##### 2. 프레임
>&nbsp; 물리적 프레임 또는 페이지 프레임이라고도 하는 프레임은 physical memory의 연속 영역입니다. 페이지와 마찬가지로 프레임도 page-size 와 page-aligned 이어야합니다. 따라서 32 비트 물리적 주소는 다음과 같이 20 비트 프레임 번호와 12 비트 프레임 오프셋 (또는 그냥 오프셋)으로 나눌 수 있습니다.<br>
31                     12 11            0<br>
+ ------------------- + ----------- +<br>
|     프레임 넘버         |      오프셋     |<br>
+ ------------------- + ----------- +<br>
Physical Address<br>

>&nbsp; 80x86은 실제 주소의 메모리에 직접 액세스 할 수있는 방법을 제공하지 않습니다. 그래서, Pintos는 커널 가상 메모리를 실제 메모리에 직접 매핑하여 이 문제를 해결합니다.<br>
>&nbsp; 커널 가상 메모리의 첫 번째 페이지는 실제 메모리의 첫 번째 프레임에 매핑되고, 두 번째 페이지는 두 번째 프레임에 매핑됩니다. 따라서 프레임은 커널 가상 메모리를 통해 액세스 할 수 있습니다.<br>
>&nbsp; Pintos는 물리적 주소와 커널 가상 주소 간의 변환 기능을 제공합니다. 자세한 내용은 A.6 절 [가상 주소], 77 페이지를 참조하십시오.<br>

##### 3. 페이지 테이블
>&nbsp; Pintos에서 페이지 테이블은 CPU가 가상 주소를 실제 주소, 즉 페이지에서 프레임으로 변환하는 데 사용하는 데이터 구조입니다. 페이지 테이블 형식은 80x86 아키텍처에 의해 결정됩니다. Pintos는 'pagedir.c'에 페이지 테이블 관리 코드를 제공합니다 (A.7 절 [Page Table], 79 쪽).<br>
>&nbsp; 아래 다이어그램은 페이지와 프레임 간의 관계를 보여줍니다. 왼쪽의 가상 주소는 페이지 번호와 오프셋으로 구성됩니다. 페이지 테이블은 page number를 frame number로 변환합니다. 이 번호는 수정되지 않은 오프셋과 결합되어 오른쪽의 실제 주소를 가져옵니다.<br>

##### 4. 슬롯 교환(Swap Slots)
>&nbsp;  Swap slot은 스왑 파티션에 있는 디스크 공간의 연속적인 페이지 크기 영역입니다. 슬롯 배치를 지정하는 하드웨어 제한 사항은 페이지 및 프레임보다 느슨하더라도, 스왑 슬롯은 페이지 정렬 해야 합니다. 이유는 그러한 과정에 딱히 단점이 없기 때문입니다.<br>

#### b. 사용자 프로그램 작동 방법
>&nbsp; Pintos는 메모리에 맞고 이 프로젝트에서 구현 한 시스템 호출 만 사용하면 일반 C 프로그램을 실행할 수 있습니다. <br>
>&nbsp; 'src / examples'디렉토리에는 Pintos에서 실행할 수 있는 일부 사용자 프로그램이 들어 있습니다. 디렉토리에 제공된 Makefile을 사용하여 예제 프로그램을 컴파일 할 수 있습니다. <br>
>&nbsp; Pintos는 'userprog / process.c'에 제공된 로더로 ELF 실행 파일을 로드 할 수 있습니다. ELF는 오브젝트 파일, 공유 라이브러리 및 실행 파일에 대해 Linux, Solaris 및 기타 여러 운영 체제에서 사용되는 파일 형식입니다. <br>

#### 3. 자원 관리 개관
다음과 같은 데이터 구조를 설계해야 합니다.
보충 페이지 테이블
	hadrware 페이지 테이블을 보완하여 페이지 오류 처리를 가능하게 합니다. 42 페이지, 4.1.4 		[보충 페이지 테이블 관리하기]를 참조하십시오.
프레임 테이블
	퇴거 정책을 효율적으로 구현할 수 있습니다. 42 페이지의 4.1.5 절 [프레임 테이블 관리]를 참		조하십시오.
스왑 테이블
	스왑 슬롯 사용량을 추적합니다. 43 페이지의 4.1.6 절 [스왑 테이블 관리]를 참조하십시오.
파일 매핑 테이블
	프로세스는 파일을 가상 메모리 공간으로 매핑 할 수 있습니다. 어떤 파일이 어떤 페이지에 매핑		되는지 추적하려면 표가 필요합니다.
반드시 네 가지 완전히 다른 데이터 구조를 구현할 필요는 없습니다. 관련 리소스를 전체적으로 또는 부분적으로 병합하여 단일 데이터 구조로 만드는 것이 편리할 수 ​​있습니다.
각 데이터 구조에 대해 각 요소에 포함해야 하는 정보를 결정해야합니다.
또한 데이터 구조의 범위, 로컬 (프로세스 별) 또는 전역 (전체 시스템에 적용) 및 해당 범위 내에서 필요한 인스턴스 수를 결정해야합니다.
디자인을 단순화하기 위해 페이지 구조가 아닌 메모리에 이러한 데이터 구조를 저장할 수 있습니다.
즉, 그 중 포인터가 유효하게 유지될 수 있습니다.
데이터 구조의 가능한 선택은 배열,리스트, 비트 맵 및 해시 테이블을 포함합니다. 배열은 가장 간단한 접근 방법이지만, 공간이 부족한 배열은 메모리를 낭비합니다.
목록도 간단하지만 특정 위치를 찾기 위해 긴 목록을 횡단하면 시간이 낭비됩니다. 배열과 목록 모두 크기를 조정할 수 있지만 중간에 삽입 및 삭제를 효율적으로 지원하는 목록이 더 효율적입니다.
Pintos는 'lib / kernel / bitmap.c'에 비트 맵 데이터 구조를 포함하고 있습니다.
'lib / kernel / bitmap.h'. 비트 맵은 각 비트가 true 또는 false 일 수있는 비트 배열입니다.
비트 맵은 일반적으로 (동일한) 자원 세트에서 사용량을 추적하는 데 사용됩니다. 자원 n이 사용 중이면 비트 맵의 ​​비트 n이 참입니다. 핀토스 비트 맵은 크기가 고정되어 있지만 크기 조정을 지원하기 위해 구현을 확장 할 수 있습니다.
Pintos에는 해시 테이블 데이터 구조도 포함됩니다 (섹션 A.8 [해시 테이블], 84 페이지 참조).
Pintos 해시 테이블은 광범위한 테이블 크기에 대해 삽입 및 삭제를 효율적으로 지원합니다.
 보다 복잡한 데이터 구조가 성능이나 기타 이점을 얻을 수도 있지만 구현을 불필요하게 복잡하게 만들 수 있습니다. 따라서 디자인의 일부로 고급 데이터 구조 (예 : 균형 이진 이진 트리)를 구현하지 않는 것이 좋습니다.
 
#### 4. 보충 페이지 테이블 관리(Managing the Supplemental Page Table)
4.1.4 보충 페이지 테이블 관리
 보충 페이지 테이블은 각 페이지에 대한 추가 데이터로 페이지 테이블을 보완합니다.
 그것은 페이지 테이블의 형식에 의해 부과된 한계 때문에 필요합니다. 이러한 데이터 구조는 종종 "페이지 테이블"이라고도합니다. 우리는 혼란을 줄이기 위해 "supplemental"이라는 단어를 추가합니다.
 보충 페이지 테이블은 적어도 두 가지 목적으로 사용됩니다. 가장 중요한 것은 페이지 폴트(page fault) 시 커널이 보충 페이지 테이블에서 오류가 발생한 가상 페이지를 검색하여 어떤 데이터가 있는지 찾아냅니다. 둘째, 프로세스가 종료되면 커널은 보충 페이지 테이블을 참조하여 해제할 리소스를 결정합니다.
 원하는 경우 보충 페이지 테이블을 구성 할 수 있습니다. 조직에 대한 최소한 두 가지 기본 접근 방식이 있습니다. 세그먼트 또는 페이지 측면입니다.(in terms of segments or in terms of pages)
 선택적으로 페이지 테이블 자체를 인덱스로 사용하여 보충 페이지 테이블의 멤버를 추적할 수 있습니다.
 이렇게 하려면 'pagedir.c'에서 Pintos 페이지 테이블 구현을 수정해야 합니다. 숙련된 학생만 이 방법을 권장합니다. 자세한 내용은 82 페이지, 섹션 A.7.4.2 [페이지 테이블 항목 형식]을 참조하십시오.
 보충 페이지 테이블의 가장 중요한 user는 페이지 폴트 핸들러입니다. 프로젝트 2에서 페이지 폴트는 항상 커널이나 사용자 프로그램에 버그를 표시합니다. 프로젝트 3에서는 더 이상 사실이 아닙니다. 이제 페이지 폴트는 파일 또는 스왑에서 페이지를 가져와야 함을 나타냅니다. 이러한 경우를 처리하기 위해보다 정교한 페이지 폴트 처리기를 구현해야 합니다.
'userprog / exception.c'에서 page_fault()를 수정하여 구현해야 하는 페이지 폴트 처리기는 대략 다음을 수행해야 합니다.
1. 보충 페이지 테이블에서 오류가 발생한 페이지를 찾으십시오. 메모리 참조가 유효하면 보충 페이지 테이블 항목을 사용하여 페이지에 들어갈 데이터를 찾습니다. 파일 시스템이나 스왑 슬롯에 있거나 단순히 모두 0 인 페이지 일 수 있습니다. 공유를 구현하면 페이지 데이터가 이미 페이지 프레임에는 있지만 페이지 테이블에는없는 경우도 있습니다. 보충 페이지 테이블이 사용자 프로세스가 액세스하려는 주소의 데이터를 기대해서는 안되거나 페이지가 커널 가상 메모리 내에 있는 경우 또는 액세스가 읽기 전용 페이지에 쓰려고 할 경우, 액세스가 유효하지 않습니다. 무효 액세스가 있으면 프로세스가 종료되고 모든 리소스가 해제됩니다.
2. 페이지를 저장할 프레임을 얻습니다. 자세한 내용은 섹션 4.1.5 [프레임 테이블 관리], 42 페이지를 참조하십시오. 공유를 구현하는 경우 필요한 데이터가 이미 프레임에있을 수 있습니다.이 경우 해당 프레임을 찾을 수 있어야합니다.
3. 파일 시스템에서 데이터를 읽거나 스왑하고 제로화하여 프레임에 데이터를 가져옵니다. 공유(sharing)를 구현하면 필요한 페이지가 이미 프레임에 있을 수 있는데, 그러한 경우 이 단계에서는 아무런 조치가 필요하지 않습니다.
4. 오류가 있는 가상 주소의 페이지 테이블 항목을 물리적 페이지로 지정합니다. 'userprog / pagedir.c'에 있는 함수를 사용할 수 있습니다.

#### 5. 프레임 테이블 관리
 프레임 테이블에는 사용자 페이지가 들어있는 각 프레임마다 하나의 항목이 있습니다. 프레임 테이블의 각 항목에는 현재 페이지를 차지하고 있는 페이지 (있는 경우) 및 선택한 다른 데이터에 대한 포인터가 들어 있습니다. 프레임 테이블을 사용하면 Pintos가 자유로운 프레임이 없을 때 Evict 시킬 페이지를 선택하여 Eviction 정책을 효율적으로 구현할 수 있습니다.
 사용자 페이지에 사용된 프레임은 palloc_get_page (PAL_USER)를 호출하여 "사용자 풀"에서 가져와야합니다. "커널 풀"에서 할당을 피하려면 PAL_USER를 사용해야합니다. 그러면 일부 테스트 케이스가 예기치 않게 실패 할 수 있습니다 (49 페이지 [PAL 사용자가 필요한 이유] 참조). 프레임 테이블 구현의 일부로 'palloc.c'를 수정하는 경우 두 풀 사이의 구별을 유지해야합니다.
프레임 테이블에서 가장 중요한 작업은 사용하지 않는 프레임을 얻는 것입니다. 이것은 프레임이 비어있다면(When a frame is free) 쉽습니다. When none is free,(즉 해석하면 frame이 비어 있지 않으면) 프레임에서 일부 페이지를 제거하여 프레임을 비워야 합니다.
 스왑 슬롯을 할당하지 않고 프레임을 제거할 수 없지만 스왑이 가득차면 커널을 패닉 상태로 만듭니다. 실제 OS는 이러한 상황을 복구하거나 방지하기 위해 광범위한 정책을 적용하지만 이러한 정책은 이 프로젝트의 범위를 벗어납니다.
 축출 과정(The process of eviction)은 대략 다음 단계로 구성됩니다.
 
 1. 페이지 교체 알고리즘을 사용하여 축출 할 프레임을 선택하십시오. 아래에 설명 된 페이지 테이블의  "액세스 된"비트와 "dirty"비트가 편리 할 것입니다.
2. 참조하는 모든 페이지 테이블에서 프레임에 대한 참조를 제거하십시오. 공유를 구현하지 않는 한, 한 페이지 만 주어진 시간에 프레임을 참조해야합니다.
3. 필요한 경우 페이지를 파일 시스템에 쓰거나 바꿉니다. 퇴거 된 프레임은 다른 페이지를 저장하는 데 사용될 수 있습니다.

##### 1. Accessed 및 더티 비트
 80x86 하드웨어는 각 페이지의 PTE (페이지 테이블 항목)에있는 한 쌍의 비트를 통해 페이지 교체 알고리즘을 구현하는 데 도움을줍니다.
 페이지에 대한 읽기 또는 쓰기에서 CPU는 액세스 된 비트를 페이지의 PTE에 1로 설정하고 모든 쓰기시 CPU는 더티 비트를 1로 설정합니다. CPU는이 비트를 0으로 재설정하지 않지만 OS가 수행 할 수 있습니다 그래서.
 aliases, 즉 동일한 프레임을 참조하는 두 페이지 이상을 알아야합니다. 앨리어스 된 프레임에 액세스 할 때 액세스 및 더티 비트는 하나의 페이지 테이블 항목 (액세스에 사용되는 페이지의 항목)에서만 업데이트됩니다. 다른 aliases(해석상 별칭이라고 됨)에 대한 액세스 및 더티 비트는 업데이트되지 않습니다.

 핀토스에서는 모든 사용자 가상 페이지가 커널 가상 페이지의 별칭이됩니다. 이러한 별칭을 어떻게 든 관리해야 합니다. 예를 들어, 코드가 두 주소의 액세스 및 더티 비트를 확인하고 업데이트 할 수 있습니다. 또는 커널이 문제를 피할 수 있습니다.
사용자 가상 주소를 통해 사용자 데이터에 액세스합니다. 다른 별칭은 추가 extra credit을 구현하는 경우 혹은 코드에 버그가 있는 경우에만 발생해야 합니다 (49 페이지 [VM Extra Credit] 참조). 
 액세스 된 비트 및 더티 비트에 대해 작업하는 기능에 대한 자세한 내용은 섹션 A.7.3 [페이지 테이블 액세스 및 더티 비트] (80 페이지)를 참조하십시오.

#### 6. 스왑 테이블 관리하기
 스왑핑을 위해 BLOCK_SWAP 블록 디바이스를 사용할 수 있으며, block_get_role ()을 호출하여이를 나타내는 struct 블록을 얻습니다. 
‘vm / build' 디렉토리에서 ,
pintos-mkdisk swap.dsk --swap-size = n 
명령을 사용하여 n-MB 스왑 파티션이 포함 된 'swap.dsk'라는 디스크를 만듭니다.
 이후, 핀토스를 실행할 때 'swap.dsk'가 자동으로 추가 디스크로 연결됩니다.
 또는, '--swap-size = n'을 사용하여 단일 실행을 위해 임시 n-MB 스왑 디스크를 사용하도록 핀토스에 지시 할 수 있습니다.
 스왑 슬롯은 느슨하게 할당해야 합니다. 즉, 실제로 Eviction 의해 필요할 때만 슬롯을 할당해야 합니다. 실행 파일에서 데이터 페이지를 읽고 프로세스 시작 시 즉시 스왑에 쓰는 것은 게으른 것이 아닙니다. 스왑 슬롯은 특정 페이지를 저장하도록 예약되어서는 안됩니다. 내용을 프레임으로 다시 읽을 때 스왑 슬롯을 비우십시오.
 
#### 7. 메모리 매핑 파일 관리
파일 시스템은 읽기 및 쓰기 시스템 호출로 가장 일반적으로 액세스됩니다. 보조 인터페이스는 mmap 시스템 호출을 사용하여 파일을 가상 페이지로 "맵핑"하는 것입니다.
그런 다음 프로그램은 파일 데이터에 직접 메모리 명령어를 사용할 수 있습니다.
'foo'파일이 0x1000 바이트 (4KB 또는 1 페이지)라고 가정합니다. 'foo'가 주소 0x5000에서 시작하여 메모리에 매핑되면 모든 메모리는 0x5000 위치에 액세스합니다. . .0x5fff는 'foo'의 해당 바이트에 액세스합니다. 다음은 mmap을 사용하여 파일을 콘솔에 인쇄하는 프로그램입니다. 명령 줄에 지정된 파일을 열고 가상 주소 0x10000000에 매핑하고 매핑 된 데이터를 콘솔 (fd 1)에 기록한 다음 파일의 매핑을 해제합니다.

완전한 오류 처리 기능을 가진 비슷한 프로그램이 'examples' 디렉토리에 'mcat.c'로 포함되어 있습니다.이 디렉토리에는 mmap의 두 번째 예제 인 'mcp.c'가 들어 있습니다.
제출한 내용은 메모리 매핑 된 파일이 사용하는 메모리를 추적 할 수 있어야 합니다. 이는 매핑 된 영역에서 페이지 오류를 올바르게 처리하고 매핑 된 파일이 프로세스 내의 다른 세그먼트와 겹치지 않도록 하는 데 필요합니다.

### 2. 구현 순서
다음 구현 순서를 제안합니다.
1. 프레임 테이블 (42 페이지, 4.1.5 절 [프레임 테이블 관리] 참조).
- 'process.c'를 변경하여 프레임 테이블 할당자를 사용하십시오. 스와핑을 아직 구현하지 마십시오. 프레임이 부족한 경우, 할당자를 실패시키거나 커널을 패닉시킵니다.
이 단계 후에도 커널은 모든 프로젝트 2 테스트 케이스를 통과해야 합니다.
2. 보충 페이지 테이블 및 페이지 오류 처리기 (42 페이지, 4.1.4 [보충 페이지 테이블 관리] 참조).
- 실행 파일을 로드하고 스택을 설정할 때 보충 페이지 테이블에 필요한 정보를 기록하려면 'process.c'를 변경하십시오. 페이지 폴트 처리기에서 코드 및 데이터 세그먼트 로드를 구현합니다. 지금은 유효한 액세스만 고려하십시오. 이 단계가 끝나면 커널은 모든 프로젝트 2 기능 테스트 케이스를 통과해야 하지만 몇 가지 견고성 테스트만 통과해야 합니다. (=> 모호해서 영어도 남김 : After this step, your kernel should pass all of the project 2 functionality test cases, but only some of the robustness tests.)
여기에서 스택 확장, 매핑 된 파일 및 프로세스 종료시 페이지 교정을 병렬로 구현할 수 있습니다.
다음 단계는 축출(Eviction)을 구현하는 것입니다 (42 페이지, 섹션 4.1.5 [프레임 테이블 관리] 참조). 처음에는 임의로(randomly) Evict 시킬 페이지를 선택할 수 있습니다. 이 시점에서 사용자 및 커널 페이지의 액세스 및 더티 비트 및 앨리어싱을 관리하는 방법을 고려해야 합니다. 동기화 또한 관심사입니다. 프로세스 A가 프레임 프로세스 B가 evict 중인 페이지에서 오류가 발생하면 어떻게 처리합니까? 마지막으로 시계 알고리즘(clock algorithm)과 같은 축출 전략을 구현하십시오.

### 3. 요구 사항
 이 과제는 제한 없는(an open-ended) 디자인 문제입니다. 우리는 일을 하는 법을 가능한 한 적게 말할 것입니다. 대신 OS에서 지원해야 하는 기능에 초점을 맞출 것입니다. 우리는 당신이 의미 있는 디자인을 생각해 낼 것으로 기대합니다. 페이지 폴트 처리 방법, 스왑 파티션 구성 방법, 페이징 구현 방법 등을 자유롭게 선택할 수 있습니다.
 
 #### 1. 디자인 문서
 프로젝트를 시작하기 전에 프로젝트 3 디자인 문서 템플릿을 다음으로 복사해야합니다.
'pintos/src/vm/DESIGNDOC' 라는 이름으로 소스 트리를 만들고 입력하십시오. 프로젝트 작업을 시작하기 전에 디자인 문서 서식 파일을 읽는 것이 좋습니다. 가상 프로젝트와 함께 사용되는 샘플 디자인 문서는 부록 D [프로젝트 문서], 99 페이지를 참조하십시오.

#### 2. 페이징
실행 파일에서로드 된 세그먼트에 대해 페이징을 구현합니다. 이 모든 페이지는 지연 적으로로드해야합니다. 즉, 커널이 페이지 폴트를 가로 채는 경우에만로드해야합니다. 축출시,로드 이후에 수정 된 페이지 (예 : "더티 비트"로 표시)는 스왑에 기록해야합니다.
읽기 전용 페이지를 포함한 수정되지 않은 페이지는 항상 실행 파일에서 다시 읽을 수 있기 때문에 스왑에 쓰지 않아야합니다.
LRU를 근사화하는 전역 페이지 교체 알고리즘을 구현하십시오. 귀하의 알고리즘은 적어도 "두 번째 기회"또는 "시계"알고리즘의 단순한 변형을 수행해야합니다.
디자인에서 병렬 처리가 가능해야합니다. 한 페이지 폴트가 I / O를 필요로하는 경우, 폴트하지 않는 프로세스는 계속 실행되어야하고 I / O를 필요로하지 않는 다른 페이지 폴트는 완료 될 수 있어야합니다. 동기화 작업이 필요합니다.
'userprog / process.c'에서 load_segment()의 루프(loop)인 프로그램 로더의 코어를 수정해야 합니다. 루프를 돌 때마다 page_read_bytes는 실행 파일에서 읽을 바이트 수를 받고 page_zero_bytes는 읽은 바이트 다음에 0으로 초기화 할 바이트 수를 받습니다. 이 두 값은 항상 PGSIZE (4,096)의 합계입니다. 페이지 처리는 다음 변수의 값에 따라 다릅니다.
• page_read_bytes가 PGSIZE와 같으면 페이지는 첫 번째 액세스시 기본 파일에서 요구 페이징되어야합니다.
• page_zero_bytes가 PGSIZE와 같으면 페이지가 모두 0이기 때문에 페이지를 디스크에서 읽을 필요가 없습니다. 첫 번째 페이지 오류시 모든 0으로 구성된 새 페이지를 작성하여 이러한 페이지를 처리해야합니다.
• 그렇지 않으면 page_read_bytes와 page_zero_bytes는 PGSIZE와 동일하지 않습니다. 이 경우 페이지의 초기 부분이 기본 파일에서 읽히고 나머지 부분은 0으로 표시됩니다.

#### 3 Stack Growth
스택 증가(Stack Growth)를 구현합니다. 프로젝트 2에서 스택은 사용자 가상 주소 공간의 맨 위에 있는 단일 페이지였고 프로그램은 많은 스택으로 제한되었습니다. 이제 스택이 현재 크기보다 커지면 필요에 따라 추가 페이지를 할당하십시오.
스택 액세스인 것처럼 보이는 경우에만 추가 페이지를 할당하십시오. 스택 액세스를 다른 액세스와 구별하려는 경험적 방법을 고안합니다. 일반적인 실제 OS는 스택에 데이터를 푸시하는 "신호"를 전달하기 위해 언제든지 프로세스를 중단시킬 수 있기 때문에 스택 포인터 아래의 스택에 쓰면 사용자 프로그램이 버그가 발생합니다.
 그러나 80x86 PUSH 명령은 스택 포인터를 조정하기 전에 액세스 권한을 확인하므로 스택 포인터 아래로 4 바이트의 페이지 오류가 발생할 수 있습니다. (그렇지 않으면, PUSH는 직설적인 방식으로 재시작 할 수 없습니다./Otherwise, PUSH would not be restartable in a straightforward fashion.) 
 마찬가지로 PUSHA 명령은 한 번에 32 바이트를 푸시하므로 스택 포인터보다 32 바이트 잘못 될 수 있습니다.(Similarly, the PUSHA instruction pushes 32 bytes at once, so it can fault 32 bytes below the stack pointer.)
 당신은, 사용자 프로그램의 스택 포인터의 현재 값을 얻을 수 있어야 합니다. 사용자 프로그램에 의해 생성 된 시스템 호출 또는 페이지 오류 내에서 'syscall_handler ()'또는 'page_fault ()'에 전달된 struct intr_frame의 esp 멤버에서 각각 검색 할 수 있습니다.

 사용자 포인터에 액세스하기 전에 사용자 포인터를 검증하면 (섹션 3.1.5 [사용자 메모리 액세스], 27 페이지 참조), 이는 처리해야 할 유일한 경우입니다.
 반면, 잘못된 메모리 액세스를 감지하기 위해 페이지 폴트를 사용하는 경우, 커널에서 페이지 폴트가 발생하는 또 다른 경우를 처리해야 합니다.
 예외가 사용자가 커널 모드로 전환 할 때 프로세서가 스택 포인터 만 저장하므로 page_fault ()에 전달 된 struct intr_frame에서 esp를 읽으면 사용자 스택 포인터가 아닌 정의되지 않은 값이 반환됩니다. 사용자가 커널 모드로 처음 전환할 때 esp를 struct thread에 저장하는 등의 다른 방법을 사용해야 합니다.
 대부분의 OS와 마찬가지로 스택 크기에 절대 제한을 두어야합니다. 일부 OS는 사용자가 조정할 수있는 한도를 만듭니다 (예 : 많은 유닉스 시스템에서는 ulimit 명령을 사용합니다.) 많은 GNU / Linux 시스템에서 기본 한계는 8MB입니다.
 첫 번째 스택 페이지를 지연 할당할 필요는 없습니다. 로드 타임에 명령 줄 인수를 할당하고 초기화 할 수 있으며 오류가 발생할 때까지 기다릴 필요가 없습니다.
 모든 스택 페이지는 축출을 위한 후보가 되어야 합니다.(All stack pages should be candidates for eviction) 축출된 스택 페이지는 스왑에 쓰여져야 합니다.

#### 4. 메모리 매핑 파일
다음 시스템 호출을 포함하여 메모리 매핑 파일을 구현합니다.
* 
파일을 fd로 프로세스의 가상 주소 공간에 매핑합니다. 전체 파일은 addr에서 시작하는 연속 가상 페이지로 매핑됩니다. VM 시스템은 mmap 영역의 페이지를 지연로드하고 맵핑을 위해 mmaped 파일 자체를 백업 저장소로 사용해야합니다. 즉, mmap에 의해 매핑 된 페이지를 제거하면 매핑 된 파일로 다시 기록됩니다. 파일의 길이가 PGSIZE의 배수가 아니면 마지막으로 매핑된 페이지의 일부 바이트가 파일의 끝 부분을 "튀어 나오게"됩니다. 페이지가 파일 시스템에서 폴트인 경우이 바이트를 0으로 설정하고 페이지가 디스크에 다시 기록 될 때 파기합니다.
성공하면이 함수는 프로세스 내에서 매핑을 고유하게 식별하는 "매핑 ID"를 반환합니다. 실패하면 –1을 반환해야 하며 그렇지 않으면 유효한 매핑 ID가 아니어야 하며 프로세스의 매핑은 변경되지 않아야 합니다.
 fd로 여는 파일의 길이가 0 바이트이면 mmap 호출에 실패할 수 있습니다. addr이 페이지 정렬되지 않았거나 매핑 된 페이지 범위가 실행 가능한로드 시간에 매핑 된 스택 또는 페이지를 포함하여 매핑 된 페이지의 기존 세트와 겹치면 실패해야 합니다. 일부 Pintos 코드는 가상 페이지 0이 매핑되지 않았다고 가정하기 때문에 addr이 0이면 실패해야 합니다. 마지막으로, 콘솔 입력 및 출력을 나타내는 파일 설명자 0 및 1은 매핑 할 수 없습니다.

* 
매핑에 의해 지정된 매핑을 해제합니다. 이전 매핑이 아직 매핑되지 않은 동일한 프로세스에 의해 mmap에 대한 호출에 의해 반환된 매핑 ID 여야 합니다.
모든 매핑은 종료나 다른 방법을 통해 프로세스가 종료 될 때 암시적으로 매핑 해제됩니다. 암시적으로 또는 명시적으로 매핑이 매핑되지 않은 경우 프로세스에서 작성한 모든 페이지가 파일에 다시 쓰여지고 작성되지 않은 페이지는 파일에 다시 쓰여서는 안됩니다. 페이지는 프로세스의 가상 페이지 목록에서 제거됩니다.
 파일을 닫거나 제거해도 맵핑이 맵핑되지 않습니다.(Closing or removing a file does not unmap any of its mappings.) 일단 생성되면 munmap이 호출되거나 프로세스가 종료 될 때까지 유닉스 규칙에 따라 매핑이 유효합니다. 자세한 내용은 35 페이지의 [열린 파일 제거]를 참조하십시오. file_reopen 함수를 사용하여 각각의 매핑에 대해 파일에 대한 별도의 독립적인 참조를 얻어야 합니다.
 두 개 이상의 프로세스가 동일한 파일을 매핑하는 경우 일관된 데이터를 볼 필요가 없습니다. 유닉스는 두 개의 매핑이 동일한 물리적 페이지를 공유하도록 함으로써 이것을 처리하지만, mmap 시스템 호출은 또한 클라이언트가 페이지가 공유인지 또는 비공개인지 (예 : copy-on-write)를 지정할 수 있는 인수를 갖습니다.

#### 5. 사용자 메모리 액세스
시스템 호출을 처리하는 동안 사용자 메모리에 액세스하기 위해 코드를 조정해야합니다 (섹션 3.1.5 [사용자 메모리 액세스], 페이지 27 참조). 사용자 프로세스가 페이지에 액세스 할 수있는 것처럼
그 내용은 현재 파일이나 스왑 공간에 있으므로 비거주 페이지를 참조하는 주소를 시스템 호출에 전달할 수 있습니다. 또한, 커널이 이를 방지하기 위한 조치를 취하지 않으면, 커널 코드에 의해 액세스되는 동안에도 그 프레임에서 페이지가 제거될 수 있습니다. 커널 코드가 비거주 사용자 페이지에 액세스하면 페이지 오류가 발생합니다.
사용자 메모리에 액세스하는 동안 커널은 이러한 페이지 오류를 처리 할 준비가되어 있거나 발생하지 못하게해야합니다. 커널은 이러한 페이지 오류를 방지해야합니다.
이 결함을 처리하기 위해 확보해야 할 자원을 보유하고 있습니다. Pintos에서 이러한 리소스에는 파일 시스템 및 스왑 공간이 포함 된 장치를 제어하는 ​​장치 드라이버가 획득 한 잠금이 포함됩니다.
예를 들어, 장치 드라이버가 file_read에 전달 된 사용자 버퍼에 액세스하는 동안 페이지 폴트가 발생하는 것을 허용해서는 안됩니다. 이러한 오류를 처리하는 동안 드라이버를 호출 할 수 없기 때문입니다.
이러한 페이지 폴트를 방지하려면 액세스가 발생하는 코드와 페이지 Eviction 코드가 서로 협력해야 합니다.(Preventing such page faults requires cooperation between the code within which the access occurs and your page eviction code.)  
 예를 들어 프레임에 포함된 페이지를 축출하지 않아도 되도록 프레임 테이블을 확장할 수 있습니다. (이를 프레임의 "고정 (pinning)"또는 "잠금 (locking)"이라고도 합니다.) 고정은 페이지를 제거할 때 페이지 교체 알고리즘의 선택을 제한하므로 필요 이상으로 페이지를 고정하지 말고 필요할 때 페이지 고정을 피하십시오.
 
### 4. FAQ
Q. 얼마나 많은 코드를 작성해야합니까?
다음은 diffstat 프로그램에 의해 작성된 참조 솔루션의 요약입니다.
마지막 행은, 삽입되고 삭제된 전체 행을 제공합니다. 변경된 행은 삽입 및 삭제로 계산됩니다. 이 요약은 Pintos 기본 코드와 관련이 있지만 프로젝트 3에 대한 참조 솔루션은 참조 솔루션에서 프로젝트 2로 시작합니다. 프로젝트 2의 요약은 섹션 3.4 [프로젝트 2 FAQ], 33 페이지를 참조하십시오.
참조 솔루션은 가능한 솔루션을 나타냅니다. 다른 많은 솔루션도 가능하며 그 중 많은 솔루션이 레퍼런스 솔루션과 크게 다릅니다. 일부 우수한 솔루션은 참조 솔루션에 의해 수정된 모든 파일을 수정할 수 없으며 일부는 참조 솔루션에 의해 수정되지 않은 파일을 수정할 수 있습니다.



Q. Project 3을 구현하기 위해 실제 Project 2가 필요합니까?
예.
Q. 어떤 추가 크레딧(학점)을 사용할 수 있습니까?
페이지 공유를 구현하는 경우 추가 크레딧을 사용할 수 있습니다 (일부 학급은 추가 학점을 부여하고 일부는 불하지 않음), 추가 정보가 있는지 클래스 별 정보를 확인하십시오 크레딧을 이용할 수 있습니다). 페이지 공유는 여러 프로세스가 동일한 실행 파일을 사용하는 경우 코드 페이지와 같은 읽기 전용 페이지를 각 프로세스에 별도의 복사본을 만드는 대신 프로세스간에 공유 할 수 있음을 의미합니다. 신중하게 데이터 구조를 설계한 경우 읽기 전용 페이지를 공유하면 이 부분이 훨씬 더 어려워서는 안됩니다.

Q. 페이지 폴트를 처리한 후에 어떻게 프로세스를 재개합니까?
page_fault ()에서 돌아와 현재 사용자 프로세스를 다시 시작합니다 (A.4.2 [내부 인터럽트 처리], 73 페이지 참조). 그런 다음 명령 포인터가 가리키는 명령을 다시 시도합니다.

Q. 사용자 프로세스가 때때로 스택 포인터 위에서 오류가 발생하는 이유는 무엇입니까?
 스택 확장 테스트에서 PUSH 및 PUSHA 명령어로 인해 현재 스택 포인터 아래에 4 및 32 바이트의 오류가 발생하더라도 사용자 프로그램의 현재 스택 포인터 위에있는 주소에서 사용자 프로그램 오류가 발생할 수 있습니다. 이것은 드문 일이 아닙니다. PUSH 및 PUSHA 명령은 사용자 스택 증가를 유발할 수있는 유일한 지침은 아닙니다.
 예를 들어 사용자 프로그램은 SUB $ n, % esp 명령어를 사용하여 스택 포인터를 감소시킨 다음 MOV ..., m (% esp) 명령어를 사용하여 할당 된 공간 내의 스택 위치에 쓰는 방법으로 스택 공간을 할당 할 수 있습니다 즉, 현재 스택 포인터 위의 m 바이트입니다. 그러한 액세스는 완벽하게 유효하며, 커널은 사용자 프로그램의 스택을 확장시켜 액세스가 성공하도록 해야 합니다.
Q. 가상 메모리 시스템이 데이터 세그먼트 증가를 지원해야합니까?
데이터 세그먼트의 크기는 링커에 의해 결정됩니다. 우리는 여전히 Pintos에는 동적 할당이 없습니다 (메모리 매핑 파일을 사용하여 사용자 수준에서 "가짜"로 만들 수도 있음). 데이터 세그먼트 증가를 지원하면 잘 설계된 시스템에 약간의 추가 복잡성을 추가해야 합니다.

Q. 왜 페이지 프레임 할당을 위해 PAL_USER를 사용해야 합니까?
PAL_USER를 palloc_get_page()에 전달하면 주 커널 풀 대신 사용자 풀에서 메모리가 할당됩니다. 사용자 풀의 페이지가 없어지면 사용자 프로그램이 페이지 되지만 커널 풀의 페이지가 부족하면 많은 커널 기능이 메모리를 확보해야 하므로 많은 오류가 발생합니다.
원하는 경우 palloc_get_page () 위에 다른 할당자를 겹칠 수 있지만 기본 메커니즘 이어야합니다.
또한 '-ul'커널 명령 행 옵션을 사용하여 사용자 풀의 크기를 제한할 수 있으므로 다양한 사용자 메모리 크기로 VM 구현을 쉽게 테스트 할 수 있습니다.


------
