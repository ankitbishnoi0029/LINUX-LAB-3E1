#include <stdio.h>
#include <stdlib.h>

void sequential() {
    int files[50], start, len, i, j;
    for(i=0;i<50;i++) files[i]=0;
    printf("\nSequential File Allocation\nEnter starting block and length of file: ");
    scanf("%d%d",&start,&len);
    for(j=start;j<(start+len);j++) {
        if(files[j]==0)
            files[j]=1;
        else {
            printf("Block already allocated.\n");
            break;
        }
    }
    if(j==(start+len))
        printf("File allocated successfully.\nBlocks: ");
    for(j=start;j<(start+len);j++)
        printf("%d ",j);
    printf("\n");
}

void indexed() {
    int index[50], files[50], n, i, j;
    for(i=0;i<50;i++) files[i]=0;
    printf("\nIndexed File Allocation\nEnter index block: ");
    scanf("%d",&n);
    if(files[n]!=0) {
        printf("Index block already allocated.\n");
        return;
    }
    files[n]=1;
    int no;
    printf("Enter number of blocks needed: ");
    scanf("%d",&no);
    printf("Enter %d block numbers: ",no);
    for(i=0;i<no;i++) scanf("%d",&index[i]);
    for(i=0;i<no;i++) {
        if(files[index[i]]==0)
            files[index[i]]=1;
        else {
            printf("Block %d already allocated.\n",index[i]);
            return;
        }
    }
    printf("File allocated successfully.\nIndex Block: %d\nBlocks: ",n);
    for(i=0;i<no;i++) printf("%d ",index[i]);
    printf("\n");
}

void linked() {
    int n, i;
    printf("\nLinked File Allocation\nEnter number of blocks: ");
    scanf("%d",&n);
    int link[n];
    printf("Enter the link of each block (-1 for end):\n");
    for(i=0;i<n;i++) {
        printf("Block %d -> ",i);
        scanf("%d",&link[i]);
    }
    int start;
    printf("Enter starting block: ");
    scanf("%d",&start);
    printf("File chain: ");
    while(start!=-1) {
        printf("%d -> ",start);
        start = link[start];
    }
    printf("END\n");
}

int main() {
    int ch;
    while(1) {
        printf("\nFile Allocation Methods\n1. Sequential\n2. Indexed\n3. Linked\n4. Exit\nEnter your choice: ");
        scanf("%d",&ch);
        switch(ch) {
            case 1: sequential(); break;
            case 2: indexed(); break;
            case 3: linked(); break;
            case 4: exit(0);
            default: printf("Invalid choice.\n");
        }
    }
    return 0;
}
