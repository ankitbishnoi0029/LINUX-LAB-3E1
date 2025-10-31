#include <stdio.h>
#include <stdlib.h>
#include <limits.h>

typedef struct {
    int pid;
    int bt;
    int at;
    int priority;
} Process;

void print_stats(int n, int wt[], int tat[], int bt[]) {
    double total_wt=0, total_tat=0;
    printf("PID\tBT\tWT\tTAT\n");
    for(int i=0;i<n;i++){
        printf("%d\t%d\t%d\t%d\n", i+1, bt[i], wt[i], tat[i]);
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Average WT = %.2f\nAverage TAT = %.2f\n", total_wt/n, total_tat/n);
}

void fcfs(Process p[], int n) {
    for(int i=0;i<n;i++)
        for(int j=i+1;j<n;j++)
            if(p[i].at > p[j].at) { Process t=p[i]; p[i]=p[j]; p[j]=t; }
    int time=0, wt[n], tat[n], bt[n];
    for(int i=0;i<n;i++) bt[i]=p[i].bt;
    for(int i=0;i<n;i++){
        if(time < p[i].at) time = p[i].at;
        wt[i] = time - p[i].at;
        time += p[i].bt;
        tat[i] = wt[i] + p[i].bt;
    }
    printf("\nFCFS Results:\n");
    print_stats(n, wt, tat, bt);
}

void sjf(Process p[], int n) {
    int done=0, time=0;
    int wt[n], tat[n], bt[n], completed[n];
    for(int i=0;i<n;i++){ completed[i]=0; bt[i]=p[i].bt; }
    while(done < n){
        int idx=-1, minb=INT_MAX;
        for(int i=0;i<n;i++){
            if(!completed[i] && p[i].at <= time){
                if(p[i].bt < minb){ minb=p[i].bt; idx=i; }
            }
        }
        if(idx==-1){ time++; continue; }
        wt[idx] = time - p[idx].at;
        time += p[idx].bt;
        tat[idx] = wt[idx] + p[idx].bt;
        completed[idx]=1; done++;
    }
    printf("\nSJF (non-preemptive) Results (ordered by PID index):\n");
    print_stats(n, wt, tat, bt);
}

void rr(Process p[], int n, int tq) {
    int time=0, done=0;
    int rem[n], wt[n], tat[n], bt[n];
    for(int i=0;i<n;i++){ rem[i]=p[i].bt; bt[i]=p[i].bt; wt[i]=0; tat[i]=0; }
    int q[1000], front=0, rear=0;
    int arrived[n]; for(int i=0;i<n;i++) arrived[i]=0;
    while(done < n){
        for(int i=0;i<n;i++) if(!arrived[i] && p[i].at <= time){ q[rear++] = i; arrived[i]=1; }
        if(front==rear){ time++; continue; }
        int idx = q[front++ % 1000];
        int exec = (rem[idx] < tq) ? rem[idx] : tq;
        rem[idx] -= exec;
        time += exec;
        for(int i=0;i<n;i++) if(!arrived[i] && p[i].at <= time){ q[rear++] = i; arrived[i]=1; }
        if(rem[idx]==0){
            done++;
            tat[idx] = time - p[idx].at;
            wt[idx] = tat[idx] - bt[idx];
        } else {
            q[rear++ % 1000] = idx;
        }
    }
    printf("\nRound Robin (TQ=%d) Results:\n", tq);
    print_stats(n, wt, tat, bt);
}

void priority_np(Process p[], int n) {
    int done=0, time=0;
    int wt[n], tat[n], bt[n], completed[n];
    for(int i=0;i<n;i++){ completed[i]=0; bt[i]=p[i].bt; }
    while(done < n){
        int idx=-1, best=INT_MAX;
        for(int i=0;i<n;i++){
            if(!completed[i] && p[i].at <= time){
                if(p[i].priority < best){ best = p[i].priority; idx=i; }
            }
        }
        if(idx==-1){ time++; continue; }
        wt[idx] = time - p[idx].at;
        time += p[idx].bt;
        tat[idx] = wt[idx] + p[idx].bt;
        completed[idx]=1; done++;
    }
    printf("\nPriority (non-preemptive) Results:\n");
    print_stats(n, wt, tat, bt);
}

int main(){
    int n; printf("Enter number of processes: "); scanf("%d",&n);
    Process p[n];
    for(int i=0;i<n;i++){
        p[i].pid = i+1;
        printf("Process %d - Arrival time, Burst time, Priority: ", i+1);
        scanf("%d%d%d", &p[i].at, &p[i].bt, &p[i].priority);
    }
    Process p1[n]; for(int i=0;i<n;i++) p1[i]=p[i];
    Process p2[n]; for(int i=0;i<n;i++) p2[i]=p[i];
    Process p3[n]; for(int i=0;i<n;i++) p3[i]=p[i];
    Process p4[n]; for(int i=0;i<n;i++) p4[i]=p[i];

    fcfs(p1, n);
    sjf(p2, n);
    int tq; printf("\nEnter Time Quantum for Round Robin: "); scanf("%d",&tq);
    rr(p3, n, tq);
    priority_np(p4, n);
    return 0;
}
