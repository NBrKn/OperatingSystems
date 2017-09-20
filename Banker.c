#include <stdio.h>
#include <stdlib.h>

/*
	Bankers Algorithm implementation in c
	Variable number of processes and resources
	Author: Nimish Sule
*/

int max[20][10];
int alloc[20][10];
int need[20][10];
int avail[10];
int safestring[20];	
int marked[20];
int marked_r;


int safetyTest(int n, int r){
	int current[r];
	int i;
	for(i=0; i<r; i++){
		current[i]=avail[i];
	}
	//setting all marked to 0
	for(i=0; i<r; i++){
		marked[i]=0;
	}
	for(i=0; i<n; i++){
		safestring[i]=-1;
	}
	int safe_iter = 0;
	int found = 0;
	int iter_flag = 0;
	//counter for procs mark_counter
	int mark_counter=n;
	//keep loop till iter_flag is not zero
	int j;
	while(1){
		iter_flag=0;
		//over all processes
		for(i=0; i<n; i++){
			if(marked[i]==1){
				continue;
			}
			//counter for found
			found=r;
			//for each resource check found, decrement counter
			for(j=0; j<r; j++){
				if(need[i][j]<=current[j]){
					found--;
				}
			}
			//if counter is not 0 then continue
			if(found!=0){
				continue;
			}
			//for each resource
			for(j=0; j<r; j++){
				current[j]+=alloc[i][j];
			}
			marked[i]=1;
			mark_counter--;
			//add to safestring
			safestring[safe_iter]=i;
			safe_iter++;
			iter_flag=1;
			break;
		}
		if(iter_flag==0){
			break;
		}
	}
	if(mark_counter==0){
		return 1;
	}
	return 0;
}
void printAll(int n, int r){
	printf("\nDEBUG:\n");
	int i, j;
	for(i=0; i<n; i++){
		for(j=0; j<r; j++){
			printf("%d\t", max[i][j]);
		}
		for(j=0; j<r; j++){
			printf("%d\t", alloc[i][j]);
		}
		for(j=0; j<r; j++){
			printf("%d\t", need[i][j]);
		}
		printf("\n");
	}
	printf("\nAvailable\n");
	for(j=0; j<r; j++){
		printf("%d\t", avail[j]);
	}
}
int request(int n, int r){
	printf("Enter the process:\n");
	int proc;
	scanf("%d", &proc);
	int i;
	int res[r];
	printf("Enter the resources:\n");
	for(i=0; i<r; i++){
		scanf("%d", &res[i]);
		if(res[i]>need[proc][i] || res[i]>avail[i]){
			printf("Error");
			return 1;
		}
	}
	for(i=0; i<r; i++){
		avail[i]-=res[i];
		alloc[proc][i]+=res[i];
		need[proc][i]-=res[i];
	}
	if(safetyTest(n, r)){
		printf("Safety test failed");
		for(i=0; i<r; i++){
			avail[i]+=res[i];
			alloc[proc][i]-=res[i];
			need[proc][i]+=res[i];
		}
		printAll(n, r);
		return 2;
	}
	int markf = 0;
	for(i=0; i<r; i++){
		if(need[proc][i]!=0){
			markf=1;
		}
	}
	if(!markf){
		for(i=0; i<r; i++){
			avail[i]+=alloc[proc][i];
		}
		marked_r++;
	}
	printf("Allocated!");
	printAll(n, r);
}

int main(){
	//input parameters for array init
	printf("Enter the number of processes:\n");
	int n;
	scanf("%d", &n);
	printf("Enter the number of resources:\n");
	int r;
	scanf("%d", &r);
	int i;
	marked_r =0 ;
	///set all of marked_r to 0
	//for(i=0; i<n; i++){
	//	marked_r[i]=0;
	//}

	//init max, alloc, need
	printf("Enter the maximum number of resources:\n");
	int j;
	for(i = 0; i<n; i++){
		for(j =0; j<r; j++){
			scanf("%d", &max[i][j]);
		}
	}
	printf("Enter the allocated number of resources:\n");
	for(i = 0; i<n; i++){
		for(j =0; j<r; j++){
			scanf("%d", &alloc[i][j]);
			//calculating need matrix
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	printf("Enter the available resources:\n");
	for(i = 0; i < r; i++){
		scanf("%d", &avail[i]);
	}

	if(safetyTest(n, r)){
		printf("Currently Safe\n");
		for(i=0; i<n; i++){
			printf("%d\t", safestring[i]);
		}
	} else {
		printf("Unsafe");
	}

	while(marked_r<n){
		request(n, r);
	}
	printf("\n");


}





