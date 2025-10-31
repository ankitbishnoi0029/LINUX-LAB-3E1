#include <stdio.h>
#include <stdlib.h>

void mft() {
    int ms, bs, nob, ef, n, mp[10], tnp = 0, p = 0;
    printf("\n--- MFT (Multiprogramming with Fixed Tasks) ---\n");
    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &ms);
    printf("Enter the block size (in Bytes): ");
    scanf("%d", &bs);
    nob = ms / bs;
    ef = ms - nob * bs;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (int i = 0; i < n; i++) {
        printf("Enter memory required for process %d (in Bytes): ", i + 1);
        scanf("%d", &mp[i]);
    }
    printf("\nNo. of Blocks available in memory: %d\n", nob);
    for (int i = 0; i < n && p < nob; i++) {
        if (mp[i] > bs)
            printf("Process %d cannot be allocated (Memory exceeds block size)\n", i + 1);
        else {
            printf("Process %d is allocated in Block %d\n", i + 1, p + 1);
            tnp += mp[i];
            p++;
        }
    }
    printf("\nTotal Memory Allocated = %d\n", tnp);
    printf("Internal Fragmentation = %d\n", (p * bs) - tnp);
    printf("External Fragmentation = %d\n", ef);
}

void mvt() {
    int ms, temp, n, mp[10], allocation[10];
    int i = 0, j = 0, sum = 0;
    printf("\n--- MVT (Multiprogramming with Variable Tasks) ---\n");
    printf("Enter the total memory available (in Bytes): ");
    scanf("%d", &ms);
    temp = ms;
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    for (i = 0; i < n; i++) {
        printf("Enter memory required for process %d (in Bytes): ", i + 1);
        scanf("%d", &mp[i]);
    }
    for (i = 0; i < n; i++) {
        if (mp[i] <= temp) {
            allocation[i] = 1;
            temp -= mp[i];
            sum += mp[i];
            printf("Process %d is allocated\n", i + 1);
        } else {
            allocation[i] = 0;
            printf("Process %d cannot be allocated (Not enough memory)\n", i + 1);
        }
    }
    printf("\nTotal Memory Allocated = %d\n", sum);
    printf("Total Free Memory (External Fragmentation) = %d\n", temp);
}

int main() {
    int ch;
    while (1) {
        printf("\nMemory Management Schemes\n1. MFT\n2. MVT\n3. Exit\nEnter your choice: ");
        scanf("%d", &ch);
        switch (ch) {
            case 1: mft(); break;
            case 2: mvt(); break;
            case 3: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
