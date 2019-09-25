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
- Resposne Time (응답 시간. 인터랙티브 시스템에서 중요)

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
