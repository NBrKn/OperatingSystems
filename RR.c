#include <stdio.h>
#include <stdlib.h>

/*
 RR program with Arrival time, preemptive
 Includes: Gantt chart, WT&TAT table, Averages
 Author: Nimish Sule
*/


int pq[20];
int top = 0;

typedef struct process_table {
    int id;
    int at;
    int bt;
    int rt;
    int wt;
    int tat;
} proc;

typedef struct execution_table {
    int id;
    int et;
} exec;

int compareAT (const void* a, const void* b){
    proc *procA = (proc *)a;
    proc *procB = (proc *)b;
    if(procA->at==procB->at){
        return (procA->id-procB->id);
    }
    return (procA->at - procB->at);
}

int compareID (const void* a, const void* b){
    proc *procA = (proc *)a;
    proc *procB = (proc *)b;
    return (procA->id - procB->id);
}

int compareRT (const void* a, const void* b){
    proc *procA = (proc *)a;
    proc *procB = (proc *)b;
    if(procA->rt==procB->rt){
        return (procA->at - procB->at);
    }
    return (procA->rt - procB->rt);
}

// void printArr(proc p[], int n){
//     int i;
//     for(i=0; i<n; i++){
//         printf("PID:%d\tAT:%d\tBT:%d\tRT:%d\n", p[i].id, p[i].at, p[i].bt, p[i].rt);
//     }
// }

// void printArr2(exec p[], int n){
//     int i;
//     for(i=0; i<n; i++){
//         printf("PID:%d\tET:%d\n", p[i].id, p[i].et);
//     }
// }
void initArr(proc p[], int n){
    int i;
    fflush(stdin);
    for(i=0; i<n; i++){
        p[i].id = i+1;
        scanf("%d %d", &p[i].at, &p[i].bt);
        p[i].rt = p[i].bt;
        p[i].wt = 0;
        p[i].tat = 0;
    }
    for(i=0; i<20; i++){
    	pq[i]=-;
    }
}

// void calcWT(proc p[], exec t[], int n, int min_at){
//     qsort(p, n, sizeof(*p), compareID);
//     int i=0;
//     int counter=min_at;
//     while(t[i].id!=-2){
//         p[t[i].id-1].wt+=(counter-p[t[i].id-1].at);
//         counter+=t[i].et;
//         i++;
//     }
// }

// void calcTAT(proc p[], int n){
//     int i;
//     for( i=0; i<n; i++){
//         p[i].tat=p[i].wt+p[i].bt;
//     }
// }

void print_table(proc p[], int n){
    qsort(p, n, sizeof(*p), compareID);
    int i;
    for(i=0; i<n; i++){
        printf("PID:%d\tAT:%d\tBT:%d\tWT:%d\tTAT:%d\n", p[i].id, p[i].at, p[i].bt, p[i].wt, p[i].tat);
    }
}


void rr(proc p[], int n, int tq){
    //arranging by arrival time first
    qsort(p, n, sizeof(*p), compareAT);
    int i, j;
    exec t[3*n];
    // for(i=0;i<3*nn;i++){
    //     t[i].id=-3;
    // }
    //setting minimum arrival time
    
    //queueing
    int min_at = p[0].at;
    int k = 0;
    t[k].id = -1;
    t[k].et = min_at;
    int exec_rem = n;
    int exec_time = min_at;
    int exec_flag = 0;
    int exec_period;
    while(exec_rem){
        // printf("exec_time:%d", exec_time);
        // printf("exec_rem:%d", exec_rem);

        for(i=0; i<n; i++){
            // printf("\n%d", i);
            // printArr(p, n);
            if(p[i].at<=exec_time && p[i].rt>0){
                exec_period = p[i].rt<tq ? p[i].rt : tq; 
                if(k>0 && p[i].id == t[k].id){
                    t[k].et+=exec_period;
                } else {
                    k++;
                    t[k].id = p[i].id;
                    t[k].et = exec_period;
                }
                p[i].rt-=exec_period;
                exec_flag = 1;
                if(p[i].rt==0){
                    p[i].tat=exec_time-p[i].at+exec_period;
                    p[i].wt=p[i].tat-p[i].bt;
                    exec_rem--;
                }
                exec_time+=exec_period;
                
            }
        }
        if(!exec_flag){
            if(t[k].id==-1){
                t[k].et++;
            } else {
                k++;
                t[k].id = -1;
                t[k].et = 1;
            }
            exec_time++;    
        }
        exec_flag = 0;
    }
    
    
    int min_at = p[0].at;
    int k = 0;
    t[k].id = -1;
    t[k].et = min_at;
    int exec_rem = n;
    int exec_time = min_at;
    int exec_flag = 0;
    int exec_period;
    while(exec_rem){
        // printf("exec_time:%d", exec_time);
        // printf("exec_rem:%d", exec_rem);
        for(i=0; i<n; i++){
            // printf("\n%d", i);
            // printArr(p, n);
            if(p[i].at<=exec_time && p[i].rt>0){
                exec_period = p[i].rt<tq ? p[i].rt : tq; 
                if(k>0 && p[i].id == t[k].id){
                    t[k].et+=exec_period;
                } else {
                    k++;
                    t[k].id = p[i].id;
                    t[k].et = exec_period;
                }
                p[i].rt-=exec_period;
                exec_flag = 1;
                if(p[i].rt==0){
                    p[i].tat=exec_time-p[i].at+exec_period;
                    p[i].wt=p[i].tat-p[i].bt;
                    exec_rem--;
                }
                exec_time+=exec_period;
                
            }
        }
        if(!exec_flag){
            if(t[k].id==-1){
                t[k].et++;
            } else {
                k++;
                t[k].id = -1;
                t[k].et = 1;
            }
            exec_time++;    
        }
        exec_flag = 0;
    }
    k++;
    t[k].id=-2;
    i=0;
    int counter=0;
    while(t[i].id!=-2){
        counter+=t[i].et;
        printf("P%d|%d:",t[i].id, counter);
        i++;
    }
    printf("\n");
    // calcWT(p, t, n, min_at);
    // calcTAT(p, n);
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
    printf("Enter the time quantum:\n");
    int tq;
    scanf("%d", &tq);
    proc p[n];
    printf("Enter the arrival and burst times:\n");
    initArr(p, n);
    // printArr(p, n);
    printf("Gantt Chart:\n"); 
    rr(p, n, tq);
    printf("Table:\n");
    print_table(p, n);
    avgtime(p, n);
}
