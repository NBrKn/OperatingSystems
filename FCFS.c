#include <stdio.h>
#include <stdlib.h>

/*
 FCFS program with Arrival time
 Includes: Gantt chart, WT&TAT table, Averages
 Author: Nimish Sule
*/

typedef struct process {
    int id;
    int at;
    int bt;
    int wt;
    int tat;
} proc;

int compareAT (const void* a, const void* b){
    proc *procA = (proc *)a;
    proc *procB = (proc *)b;
    return (procA->at - procB->at);
}

int compareID (const void* a, const void* b){
    proc *procA = (proc *)a;
    proc *procB = (proc *)b;
    return (procA->id - procB->id);
}

void printArr(proc p[], int n){
    int i;
    for(i=0; i<n; i++){
        printf("PID:%d\tAT:%d\tBT:%d\n", p[i].id, p[i].at, p[i].bt);
    }
}

void initArr(proc p[], int n){
    int i;
    fflush(stdin);
    for(i=0; i<n; i++){
        p[i].id = i+1;
        scanf("%d %d", &p[i].at, &p[i].bt);
    }
}

void calcWT(proc p[], int n){
    int counter = p[0].at;
    int i;
    for( i=0; i<n; i++){
        p[i].wt=counter-p[i].at;
        counter+=p[i].bt;
    }
}

void calcTAT(proc p[], int n){
    int i;
    for( i=0; i<n; i++){
        p[i].tat=p[i].wt+p[i].bt;
    }
}

void print_table(proc p[], int n){
    qsort(p, n, sizeof(*p), compareID);
    int i;
    for(i=0; i<n; i++){
        printf("PID:%d\tAT:%d\tBT:%d\tWT:%d\tTAT:%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}

void gantt(proc p[], int n){
    int counter = p[0].at;
    printf("|%d:", counter);
    int i;
    for(i=0; i<n; i++){
        counter+=p[i].bt;
        printf("P%d|%d:",p[i].id, counter);
    }
    printf("\n");
}

void fcfs(proc p[], int n){
    qsort(p, n, sizeof(*p), compareAT);
    calcWT(p,n);
    calcTAT(p, n);
}

void avgtime(proc p[], int n){
    float awt = 0, atat = 0;
    int i;
    for(i=0; i<n; i++){
        awt+=p[i].wt;
        atat+=p[i].tat;
    }
    awt/=n;
    atat/=n;
    printf("Average Waiting Time: %f\nAverage Turnaround Time: %f\n", awt, atat);
}

void main(){
    printf("Enter the number of processes:\n");
    int n;
    scanf("%d", &n);
    proc p[n];
    printf("Enter the arrival and burst times:\n");
    initArr(p, n);
    fcfs(p, n);
    printf("Gantt Chart:\n");
    gantt(p, n);  
    printf("Table:\n");
    print_table(p, n);
    avgtime(p, n);
}