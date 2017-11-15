/*
 *
 * Purpose: To print start address,end address and fragmentation of firstfit and best fit
 *
 * Parameter: Memory requests and memory partitions
 *
 * Input: Five memory requests and five partitions
 *
 * Output: Fragmentation,start address and end address of each memory request
 *
 */

#include<stdio.h>

int main() {
	static int partition_arr[10], memoryreq_arr[10], allocation[10];
	int fragments[10], startAdrs[10], endAdrs[10]; //Integer array for fragmentation,start address and end address
	int partition[10], tempPartition[10], memoryreq[10]; //Partition and memory request array
	int number_of_partition = 5, number_of_memoryreq = 5; //Number of partition and number of memory request
	int i, j, temp; //i,j used for loop and temmp used to find first fit

	//Input five memory partitions
	printf("Enter the Size of the Partition:\n");
	for (i = 0; i < number_of_partition; i++) {
		scanf("%d", &partition[i]);
	}
	//Input five memory request
	printf("Enter the Size of the Memory Request:\n");
	for (i = 0; i < number_of_memoryreq; i++) {
		scanf("%d", &memoryreq[i]);
	}
	//Initialize -1 for all
	for (i = 0; i < number_of_memoryreq; i++)
		allocation[i] = -1;
	//copy partition data to temp array
	for (i = 0; i < number_of_partition; i++)
		tempPartition[i] = partition[i];

	printf("************************First Fit*************************");
	//Calculating first fit
	for (i = 0; i < number_of_memoryreq; i++) {
		int adrs = 0;
		for (j = 0; j < number_of_partition; j++) {
			adrs += partition[j];
			if (partition_arr[j] != 1) {
				temp = partition[j] - memoryreq[i];
				if (temp >= 0) {
					memoryreq_arr[i] = j;
					startAdrs[i] = adrs - partition[j];  //Start address
					endAdrs[i] = startAdrs[i] + memoryreq[i] - 1; //End address
					break;
				}
			}
		}
		fragments[i] = temp; //calculating fragmentation
		partition_arr[memoryreq_arr[i]] = 1;
	}
	//Printing the results for Firstfit
	for (i = 0; i < number_of_memoryreq; i++) {
		printf("\nJob %d with size %d", i + 1, memoryreq[i]);
		if (fragments[i] > -1)
			printf(" loaded at %d goes to %d and fragmentation is %d",
					startAdrs[i], endAdrs[i], fragments[i]);
		else
			printf(" not allocated");
	}

	printf("\n************************Best Fit*************************");
	for (i = 0; i < number_of_memoryreq; i++) {
		// Find the best fit partition for current process
		int bestFit = -1;

		for (j = 0; j < number_of_partition; j++) {

			if (partition[j] >= memoryreq[i]) {
				if (bestFit == -1)
					bestFit = j;
				else if (partition[bestFit] > partition[j])
					bestFit = j;
			}

		}

		// Finding the best fit
		if (bestFit != -1) {
			allocation[i] = bestFit;
			// Reduce available memory in this block.
			partition[bestFit] -= memoryreq[i];
			fragments[i] = partition[bestFit]; //calculating fragmentation
		}
	}
//Finding start and end address of bestfit
	for (i = 0; i < number_of_memoryreq; i++) {
		int adrs = 0;
		if (allocation[i] != -1) {
			for (j = 0; j < allocation[i]; j++)
				adrs += tempPartition[j];
		}

		startAdrs[i] = adrs;  //Start address
		endAdrs[i] = startAdrs[i] + memoryreq[i] - 1; //End address
	}

//Displaying the bestfit results
	for (int i = 0; i < number_of_memoryreq; i++) {
		printf("\nJob %d with size %d", i + 1, memoryreq[i]);
		if (allocation[i] != -1)
			printf(" loaded at %d goes to %d and fragmentation is %d",
					startAdrs[i], endAdrs[i], fragments[i]);
		else
			printf(" not allocated");
	}
	printf("\n");
	return 0;
}
