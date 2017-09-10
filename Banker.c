#include <stdio.h>
#include <stdlib.h>

/*
	Bankers Algorithm implementation in c 
	Variable number of processes and resources
	Author: Nimish Sule	
*/


int main(){
	printf("Enter the number of processes");
	int n;
	scanf("%d", &n);
	printf("Enter the number of resources");
	int r;
	scanf("%d", &r);
	int max[n][r];
	int alloc[n][r];
	int need[n][r];
	int avail[r];
	int safestring[n];
	int marked[n];
	int i;
	for(i=0; i<n; i++){
		marked[i]=0;
	}
	printf("Enter the maximum number of resources");
	int i, j;
	for(i = 0; i<n; i++){
		for(j =0; j<r; j++){
			scanf("%d", &max[i][j]);
		}
	}
	printf("Enter the allocated number of resources");
	int i, j;
	for(i = 0; i<n; i++){
		for(j =0; j<r; j++){
			scanf("%d", &alloc[i][j]);
			//calculating need matrix
			need[i][j] = max[i][j] - alloc[i][j];
		}
	}
	for(i=0; i<n; i++){
				
	}

}



