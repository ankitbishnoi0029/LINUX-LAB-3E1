#include <stdio.h>

int main() {
    int ms, ps, nop, np, rempages, i, j, x, y, pa, offset;
    int p[10];

    printf("Enter the memory size: ");
    scanf("%d", &ms);
    printf("Enter the page size: ");
    scanf("%d", &ps);

    nop = ms / ps;
    printf("The number of pages available in memory: %d\n", nop);

    printf("Enter number of processes: ");
    scanf("%d", &np);

    rempages = nop;
    for (i = 0; i < np; i++) {
        printf("Enter number of pages required for process %d: ", i + 1);
        scanf("%d", &p[i]);
        if (p[i] > rempages)
            printf("Memory is full. Process %d cannot be allocated.\n", i + 1);
        else {
            rempages -= p[i];
            printf("Enter page table for process %d (each page frame number):\n", i + 1);
            for (j = 0; j < p[i]; j++) scanf("%d", &p[j]);
        }
    }

    printf("Enter logical address (process number, page number, offset): ");
    scanf("%d %d %d", &x, &y, &offset);

    if (x > np || y >= p[x - 1]) {
        printf("Invalid process or page number.\n");
        return 0;
    }

    pa = (p[y] * ps) + offset;
    printf("Physical Address = %d\n", pa);

    return 0;
}
