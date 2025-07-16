//
// Created by Admin on 7/16/2025.
//
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Task {
    int id;
    char title[100];
    int priority;
    char deadline[50];
} Task;

typedef struct TaskNode {
    Task data;
    struct TaskNode* next;
} TaskNode;

typedef struct CompletedTaskNode {
    Task data;
    struct CompletedTaskNode* prev;
    struct CompletedTaskNode* next;
} CompletedTaskNode;

void addTask(TaskNode **head) {
    TaskNode *newNode = (TaskNode *)malloc(sizeof(TaskNode));
    printf("Nhap ID: ");
    scanf("%d", &newNode->data.id);
    printf("Nhap Tieu de: ");
    getchar();
    fgets(newNode->data.title, 100, stdin);
    newNode->data.title[strcspn(newNode->data.title, "\n")] = '\0';
    printf("Nhap Muc do uu tien: ");
    scanf("%d", &newNode->data.priority);
    printf("Nhap Deadline: ");
    getchar();
    fgets(newNode->data.deadline, 50, stdin);
    newNode->data.deadline[strcspn(newNode->data.deadline, "\n")] = '\0';

    newNode->next = NULL;

    if (*head == NULL) {
        *head = newNode;
    } else {
        TaskNode *temp = *head;
        while (temp->next != NULL) temp = temp->next;
        temp->next = newNode;
    }

    printf("Them thanh cong!\n");
}

void printTasks(TaskNode *head) {
    if (head == NULL) {
        printf("Danh sach rong.\n");
        return;
    }
    while (head != NULL) {
        printf("ID: %d\nTitle: %s\nPriority: %d\nDeadline: %s\n",
               head->data.id, head->data.title, head->data.priority, head->data.deadline);
        printf("--------------------------\n");
        head = head->next;
    }
}
void printCompletedTasks(CompletedTaskNode *head) {
    if (head == NULL) {
        printf("Khong co nhiem vu hoan thanh.\n");
        return;
    }
    printf("=== Danh sach da hoan thanh ===\n");
    while (head != NULL) {
        printf("ID: %d\nTitle: %s\nPriority: %d\nDeadline: %s\n",
               head->data.id, head->data.title, head->data.priority, head->data.deadline);
        printf("--------------------------\n");
        head = head->next;
    }
}

void deleteTask(TaskNode **head, int id) {
    TaskNode *temp = *head, *prev = NULL;
    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay nhiem vu co ID %d\n", id);
        return;
    }
    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }
    free(temp);
    printf("Xoa thanh cong!\n");
}

void updateTask(TaskNode **head, int id) {
    TaskNode *cur = *head;
    while (cur != NULL && cur->data.id != id) cur = cur->next;
    if (cur == NULL) {
        printf("Khong tim thay nhiem vu.\n");
        return;
    }
    printf("Cap nhat tieu de: ");
    getchar(); // Đọc ký tự '\n' còn lại
    fgets(cur->data.title, 100, stdin);
    cur->data.title[strcspn(cur->data.title, "\n")] = '\0';

    printf("Cap nhat deadline: ");
    fgets(cur->data.deadline, 50, stdin);
    cur->data.deadline[strcspn(cur->data.deadline, "\n")] = '\0';

    printf("Cap nhat muc uu tien: ");
    scanf("%d", &cur->data.priority);

    printf("Cap nhat thanh cong!\n");
}

void markCompleted(TaskNode **head, CompletedTaskNode **completedHead, int id) {
    TaskNode *temp = *head, *prev = NULL;
    while (temp != NULL && temp->data.id != id) {
        prev = temp;
        temp = temp->next;
    }
    if (temp == NULL) {
        printf("Khong tim thay nhiem vu.\n");
        return;
    }

    if (prev == NULL) {
        *head = temp->next;
    } else {
        prev->next = temp->next;
    }

    CompletedTaskNode *newNode = (CompletedTaskNode *)malloc(sizeof(CompletedTaskNode));
    newNode->data = temp->data;
    newNode->prev = NULL;
    newNode->next = *completedHead;
    if (*completedHead != NULL) (*completedHead)->prev = newNode;
    *completedHead = newNode;

    free(temp);
    printf("Da chuyen nhiem vu vao danh sach da hoan thanh.\n");
}

void sortTasksByPriority(TaskNode *head) {
    if (head == NULL || head->next == NULL) return;

    int swapped;
    TaskNode *ptr;
    Task temp;
    do {
        swapped = 0;
        ptr = head;
        while (ptr->next != NULL) {
            if (ptr->data.priority > ptr->next->data.priority) {
                temp = ptr->data;
                ptr->data = ptr->next->data;
                ptr->next->data = temp;
                swapped = 1;
            }
            ptr = ptr->next;
        }
    } while (swapped);

    printf("Da sap xep theo muc do uu tien.\n");
}

void searchTask(TaskNode *head, char *title) {
    int found = 0;
    while (head != NULL) {
        if (strstr(head->data.title, title)) {
            printf("Tim thay: ID: %d | Title: %s | Priority: %d | Deadline: %s\n",
                   head->data.id, head->data.title, head->data.priority, head->data.deadline);
            found = 1;
        }
        head = head->next;
    }
    if (!found)
        printf("Khong tim thay nhiem vu co tu khoa '%s'\n", title);
}

int main() {
    TaskNode *taskList = NULL;
    CompletedTaskNode *completedList = NULL;
    int choice, id;
    char title[100];

    do {
        printf("\n======= TASK MANAGER =======\n");
        printf("1. Them nhiem vu\n");
        printf("2. Hien thi danh sach\n");
        printf("3. Xoa nhiem vu\n");
        printf("4. Cap nhat nhiem vu\n");
        printf("5. Danh dau hoan thanh\n");
        printf("6. Sap xep theo uu tien\n");
        printf("7. Tim kiem theo tieu de\n");
        printf("8. Thoat\n");
        printf("Chon chuc nang: ");
        scanf("%d", &choice);

        switch (choice) {
            case 1:
                addTask(&taskList);
                break;
            case 2:
                printf("\n--- Danh sach nhiem vu dang thuc hien ---\n");
                printTasks(taskList);

                printf("\n--- Danh sach nhiem vu da hoan thanh ---\n");
                printCompletedTasks(completedList);
                break;

            case 3:
                printf("Nhap ID can xoa: ");
                scanf("%d", &id);
                deleteTask(&taskList, id);
                break;
            case 4:
                printf("Nhap ID can cap nhat: ");
                scanf("%d", &id);
                updateTask(&taskList, id);
                break;
            case 5:
                printf("Nhap ID can danh dau hoan thanh: ");
                scanf("%d", &id);
                markCompleted(&taskList, &completedList, id);
                break;
            case 6:
                sortTasksByPriority(taskList);
                break;
            case 7:
                printf("Nhap tu khoa tieu de can tim: ");
                getchar();
                fgets(title, 100, stdin);
                title[strcspn(title, "\n")] = '\0';
                searchTask(taskList, title);
                break;
            case 8:
                printf("Thoat chuong trinh.\n");
                break;

            default:
                printf("Lua chon khong hop le.\n");
        }
    } while (choice != 8);

    return 0;
}
