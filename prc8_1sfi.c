// firs fi algo
#include <stdio.h>

void firstFit(int blockSize[], int m, int processSize[], int n) {
    int allocation[n];
    
    // Initially no block is assigned to any process
    for (int i = 0; i < n; i++) {
        allocation[i] = -1;
    }

    // Pick each process and find suitable blocks
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            if (blockSize[j] >= processSize[i]) {
                // Allocate block j to process i
                allocation[i] = j;
                
                // Reduce available memory in this block
                blockSize[j] -= processSize[i];
                break;
            }
        }
    }

    // Display allocation
    printf("\nProcess No.\tProcess Size\tBlock No.\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t", i + 1, processSize[i]);
        if (allocation[i] != -1)
            printf("%d\n", allocation[i] + 1);
        else
            printf("Not Allocated\n");
    }
}

int main() {
    int m, n;

    // Input number of blocks
    printf("Enter the number of blocks: ");
    scanf("%d", &m);
    int blockSize[m];

    // Input size of each block
    printf("Enter the size of each block: \n");
    for (int i = 0; i < m; i++) {
        printf("Block %d: ", i + 1);
        scanf("%d", &blockSize[i]);
    }

    // Input number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    int processSize[n];

    // Input size of each process
    printf("Enter the size of each process: \n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", i + 1);
        scanf("%d", &processSize[i]);
    }

    // Call first fit allocation function
    firstFit(blockSize, m, processSize, n);

    return 0;
}
