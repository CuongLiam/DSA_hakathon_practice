#include <stdio.h>
#include <stdlib.h>

#define MAX 100

typedef struct Student {
    int id;
    char name[MAX];
    char sdt[MAX];
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

typedef struct Queue {
    Node* front;
    Node* rear;

    int size;
    int capacity;
} Queue;

Node* createItem(int id) {
    Node* newItem = malloc(sizeof(Node));
    newItem->data.id = id;

    printf("nhap ten: ");
    fgets(newItem->data.name, MAX, stdin);

    printf("sdt: ");
    fgets(newItem->data.sdt, MAX, stdin);

    newItem->next = NULL;

    return newItem;
}

Queue* createQueue(int maxSize) {
    Queue* newQueue = malloc(sizeof(Queue));

    newQueue->front = NULL;
    newQueue->rear = NULL;

    newQueue->size = 0;
    newQueue->capacity = maxSize;

    return newQueue;
}

int isEmpty(Queue* q) {
    if (q->size == 0) {
        return 1;
    }
    return 0;
}

int isFull(Queue* q) {
    return q->size == q->capacity;
}

void addToQueue(Queue* q) {
    if (isFull(q)) {
        printf("full");
        return ;
    }

    int newId = q->size + 1;
    Node* newItem = createItem(newId);
    if (isEmpty(q)) {
        q->front = newItem;
        q->rear = newItem;

    } else {
        q->rear->next = newItem;
        q->rear = newItem;
    }
    q->size++;
}

void printQueue(Queue* q) {
    Node* curr = q->front;

    while (curr!=NULL) {
        printf("%d", curr->data.id);

        curr = curr->next;
    }
}

void displayMenu() {
    printf("===E-CONTACT BOOK===");
    printf("\n1. add a student");
    printf("\n2. display studentList");
    printf("\n3. del a student");
    printf("\n4. update student infor");
    printf("\n5. note for student");
    printf("\n6. sort with avg score");
    printf("\n7. find student using name");
    printf("\n0. exit");
}

int main(void) {
    Queue* queue1 = createQueue(5);

    addToQueue(queue1);

    printQueue(queue1);

    return 0;
}