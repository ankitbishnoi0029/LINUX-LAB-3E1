#include <stdio.h>

typedef struct {
    int pid;
    int bt;
    int at;
    int priority;
} Process;

void fcfs(Process p[], int n) {
    int wt[n], tat[n];
    int time = 0;
    for(int i=0;i<n;i++) {
        if(time < p[i].at) time = p[i].at;
        wt[i] = time - p[i].at;
        time += p[i].bt;
        tat[i] = wt[i] + p[i].bt;
    }
    printf("\nQueue 1 (FCFS):\nPID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, wt[i], tat[i]);
}

void round_robin(Process p[], int n, int tq) {
    int rem[n], wt[n], tat[n], time=0, done=0;
    for(int i=0;i<n;i++){ rem[i]=p[i].bt; wt[i]=0; tat[i]=0; }
    while(done<n){
        for(int i=0;i<n;i++){
            if(rem[i]>0){
                if(rem[i]>tq){
                    time+=tq;
                    rem[i]-=tq;
                } else {
                    time+=rem[i];
                    wt[i]=time-p[i].bt;
                    tat[i]=time;
                    rem[i]=0;
                    done++;
                }
            }
        }
    }
    printf("\nQueue 2 (Round Robin, TQ=%d):\nPID\tBT\tWT\tTAT\n", tq);
    for(int i=0;i<n;i++)
        printf("%d\t%d\t%d\t%d\n", p[i].pid, p[i].bt, wt[i], tat[i]);
}

int main() {
    int n1, n2, tq;
    printf("Enter number of processes in Queue 1 (FCFS): ");
    scanf("%d",&n1);
    Process q1[n1];
    for(int i=0;i<n1;i++) {
        q1[i].pid = i+1;
        printf("Queue1 Process %d - Arrival, Burst: ", i+1);
        scanf("%d%d",&q1[i].at,&q1[i].bt);
    }

    printf("Enter number of processes in Queue 2 (Round Robin): ");
    scanf("%d",&n2);
    Process q2[n2];
    for(int i=0;i<n2;i++) {
        q2[i].pid = i+1;
        printf("Queue2 Process %d - Arrival, Burst: ", i+1);
        scanf("%d%d",&q2[i].at,&q2[i].bt);
    }

    printf("Enter Time Quantum for Round Robin: ");
    scanf("%d",&tq);

    fcfs(q1, n1);
    round_robin(q2, n2, tq);

    printf("\nMultilevel Queue Scheduling Completed.\n");
    return 0;
}
