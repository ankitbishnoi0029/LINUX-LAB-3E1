#include <stdio.h>
#include <stdlib.h>

struct Node {
    int data;
    struct Node *next;
};

struct Node *head = NULL;

void insertAtEnd(int value) {
    struct Node *newNode = (struct Node *)malloc(sizeof(struct Node));
    newNode->data = value;
    newNode->next = NULL;
    if (head == NULL) {
        head = newNode;
        return;
    }
    struct Node *temp = head;
    while (temp->next != NULL)
        temp = temp->next;
    temp->next = newNode;
}

void deleteAtBeginning() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head;
    head = head->next;
    free(temp);
    printf("Node deleted from beginning\n");
}

void deleteAtEnd() {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head, *prev = NULL;
    if (head->next == NULL) {
        free(head);
        head = NULL;
    } else {
        while (temp->next != NULL) {
            prev = temp;
            temp = temp->next;
        }
        prev->next = NULL;
        free(temp);
    }
    printf("Node deleted from end\n");
}

void deleteAtPosition(int pos) {
    if (head == NULL) {
        printf("List is empty\n");
        return;
    }
    struct Node *temp = head, *prev = NULL;
    if (pos == 1) {
        head = head->next;
        free(temp);
        printf("Node deleted from position %d\n", pos);
        return;
    }
    for (int i = 1; i < pos && temp != NULL; i++) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Invalid position\n");
        return;
    }
    prev->next = temp->next;
    free(temp);
    printf("Node deleted from position %d\n", pos);
}

void displayList() {
    struct Node *temp = head;
    if (temp == NULL) {
        printf("List is empty\n");
        return;
    }
    printf("Linked List: ");
    while (temp != NULL) {
        printf("%d ", temp->data);
        temp = temp->next;
    }
    printf("\n");
}

int main() {
    int choice, value, pos;
    while (1) {
        printf("\n1. Insert at End\n2. Delete at Beginning\n3. Delete at End\n4. Delete at Position\n5. Display\n6. Exit\nEnter choice: ");
        scanf("%d", &choice);
        switch (choice) {
            case 1:
                printf("Enter value: ");
                scanf("%d", &value);
                insertAtEnd(value);
                break;
            case 2:
                deleteAtBeginning();
                break;
            case 3:
                deleteAtEnd();
                break;
            case 4:
                printf("Enter position: ");
                scanf("%d", &pos);
                deleteAtPosition(pos);
                break;
            case 5:
                displayList();
                break;
            case 6:
                return 0;
            default:
                printf("Invalid choice\n");
        }
    }
}
