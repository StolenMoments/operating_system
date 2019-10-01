# CPU 스케줄링

### 선점 vs 비선점 (preemptive vs Non-preemptive)

- Ready Queue 를 병원 대기실이라 하고 CPU를 의사라 하자.
- 의사가 환자의 진료를 끝날 때 까지 대기자는 진료를 받을 수 없다. 이를 '비선점'.
- 응급환자가 발생해서 진료 중이던 환자가 물러나고 응급환자를 치료한다. 이를 '선점'.

### 스케줄링 척도 (Scheduling Criteria)
- CPU Utilization (CPU 사용률)
- Throughput (시간 당 작업량. 처리율)
- Turnaround Time (반환 시간. 작업 시작부터 끝내고 나오기 까지의 시간. 병원 들어가서 접수하고 대기하고 진료받고 병원에서 나오기 까지의 시간.)
- Waiting Time (대기 시간)
- Response Time (응답 시간. 인터랙티브 시스템에서 중요)

### 스케줄링 알고리즘

- FCFS
  - 간단하고 공정함. 선착순. Non-preemptive.
  - Convoy Effect (호송 효과)
    - 시간을 많이 잡아먹는 프로세스가 먼저 와서 시간을 적게 먹는 프로세스를 기다리게 해 평균 대기 시간을 증가시키는 효과...
  - AWT (Average Waiting Time)
    - P1 Burst Time : 24
    - P2 Burst Time : 3
    - P3 Burst Time : 3
    
    - 순서가 P1->P2->P3 이라면 AWT = (0 + 24 + 27) / 3 = 17
    - 순서가 P2->P3->P1 이라면 AWT = (0 + 3 + 6) / 3 = 3
    - 척도를 대기 시간으로 본다면 빠른 것 부터 처리하면 좋다는 결론을 낼 수 있음.
    - 먼저 온 녀석을 처리하는 것이 마냥 좋은 것이 아니다.

- SJF (1)
  - 시간이 적게 드는 프로세스 부터 실행
  - AWT (Average Waiting Time)
    - P1 Burst Time : 6
    - P2 Burst Time : 8
    - P3 Burst Time : 7
    - P4 Burst Time : 3
    
    - P4 -> P1 -> P3 -> P2 AWT = 7ms (FCFS : 10.25ms)
  
  - 단점은 비현실적이라는 것...Burst Time을 미리 알 수가 없다...
  
- SJF (2)
  - 최소 잔여시간 우선 (SRTF)
  - 현재 시점에서 잔여시간이 가장 적은 것(Burst Time - Arrival Time) 부터 실행
  - 선점형은 돌던 프로세스를 바꿀 수 있음.
  
- Priorty Scheduling (1)
  - 프로세스에 우선 순위를 부여해 1순위, 2순위, 3순위...순서로 실행
  - 우선 순위는 어떻게 정하는가?
    - 내부적 : Time Limit, Memory Requirement, I/O to CPU Burst...
    - 외부적 : 돈 많이 낸 순서, 정치적인 요소, 업무 우선 순위 등...
    
  - 문제점 : 기아(Starvation)
    - 외부에서 새로운 작업이 계속 들어오는데, 그 작업이 우선 순위가 높으면 기다리던 것은 또 기다림.
    - **계속 기다릴 수 있음...!**
    - 해결책으로 aging. Ready Queue에서 오래 기다릴 수록 우선 순위를 점진적으로 올려줌.
