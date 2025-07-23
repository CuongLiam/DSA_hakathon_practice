#include <stdio.h>
#include <stdlib.h>

#define MAX 100

int count = 1;

typedef struct Student {
    int id;
    char name[MAX];
    int grade;
    char note[MAX];
} Student;

typedef struct Node {
    Student data;
    struct Node* next;
} Node;

Node* createItem() {
    Node* newItem = malloc(sizeof(Node));

    newItem->data.id = count++;
    printf("nhap ten: ");
    fgets(newItem->data.name, MAX, stdin);

    printf("grade: ");
    scanf("%d", &newItem->data.grade);
    fflush(stdin);

    printf("note: ");
    fgets(newItem->data.note, MAX, stdin);

    newItem->next = NULL;

    return newItem;
}

Node* pushNode(Node* head) {
    Node* newNode = createItem();

    if (head == NULL) {
        return newNode;
    }
    Node* curr = head;
    while (curr->next != NULL) {
        curr = curr->next;
    }
    curr->next = newNode;
    return head;
}

void printList(Node* head) {
    if (head == NULL) {
        printf("ds rong\n");
        return;
    }

    Node* curr = head;
    while (curr != NULL) {
        printf("\nid: %d", curr->data.id);
        printf("\nname: %s", curr->data.name);
        printf("grade: %d", curr->data.grade);
        printf("\nnote: %s\n", curr->data.note);

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

Node* deleteStudent(Node* head) {
    if (head == NULL) {
        printf("\nds rong, ko the xoa\n");
        return head;
    }

    int delID;
    printf("nhap ID muon xoa");
    scanf("%d", &delID);

    if (head->data.id == delID) {
        Node* temp = head;
        head = head->next;
        free(temp);
        return head;
    }

    Node* curr = head;
    while (curr != NULL) {
        if (curr->next->data.id == delID) {
            Node* temp = curr->next;

            if (curr->next->next == NULL) {
                temp = curr->next;
                curr->next = NULL;
                free(temp);
                return head;
            }
            curr->next = curr->next->next;
            free(temp);
            return head;
        }
        curr = curr->next;
    }
    printf("\nko ton tai ID de xoa\n");
    return head;
}

void updateValue(Node* node) {
    printf("nhap ten: ");
    fgets(node->data.name, MAX, stdin);
    fflush(stdin);

    printf("grade: ");
    scanf("%d", &node->data.grade);
    fflush(stdin);

    printf("note: ");
    fgets(node->data.note, MAX, stdin);
}

Node* updateStudent(Node* head) {
    if (head == NULL) {
        printf("ds rong\n");
        return NULL;
    }

    int idToUpdate;
    printf("\nnhap id muon cap nhat");
    scanf("%d", &idToUpdate);
    fflush(stdin);

    if (head->data.id == idToUpdate) {
        updateValue(head);
        return head;
    }

    Node* curr = head;
    while (curr != NULL) {
        if (idToUpdate == curr->data.id) {
            updateValue(curr);
            printf("cap nhat thanh cong");
            return head;
        }
        curr = curr->next;
    }
    printf("id ko ton tai\n");
    return head;
}

void freeList(Node* head) {
    while (head) {
        Node* tmp = head;
        head = head->next;
        free(tmp);
    }
}

Node* notingStudent(Node* head) {
    if (head == NULL) {
        printf("ds rong\n");
        return NULL;
    }

    int idToNote;
    printf("nhap id muon note");
    scanf("%d", &idToNote);
    fflush(stdin);


    if (idToNote == head->data.id) {
        printf("noi dung note: ");
        fgets(head->data.note, MAX, stdin);
        return head;
    }

    Node* curr = head;
    while (curr != NULL) {
        if (idToNote == curr->data.id) {
            printf("noi dung note: ");
            fgets(curr->data.note, MAX, stdin);
            return head;
        }

        curr = curr->next;
    }
    return head;
}

Node* sortByGrade(Node* head) {
    if (head == NULL || head->next == NULL) {
        printf("ds trong hoac co 1 ptu\n");
        return head;
    }

    int swapped;
    do {
        swapped = 0;
        Node* curr = head;
        while (curr->next != NULL) {
            if (curr->data.grade > curr->next->data.grade) {
                Student temp = curr->data;
                curr->data = curr->next->data;
                curr->next->data = temp;
                swapped = 1;
            }
            curr = curr->next;
        }
    } while (swapped);

    printf("sort thanh cong");
    return head;
}

int main(void) {
    Node* stuHead = NULL;

    int choice;
    do {
        displayMenu();
        printf("\nur choice...");
        scanf("%d", &choice);
        fflush(stdin);
        switch (choice) {
            case 1: {
                stuHead = pushNode(stuHead);
                break;
            }
            case 2: {
                printList(stuHead);
                break;
            }
            case 3: {
                stuHead = deleteStudent(stuHead);
                printf("da xoa\n");
                break;
            }
            case 4: {
                stuHead = updateStudent(stuHead);
                break;
            }
            case 5: {
                stuHead = notingStudent(stuHead);
                break;
            }
            case 6: {
                stuHead = sortByGrade(stuHead);
                printList(stuHead);
            }
            default:
                break;
        }

    } while (choice != 0);

    freeList(stuHead);
    return 0;
}