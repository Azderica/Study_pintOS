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

------
