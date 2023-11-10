#include <stdio.h>
#include <stdlib.h>

typedef struct node {
    int value;
    struct node *next;
} LinkedList;

LinkedList *LinkedListCreate() {
    LinkedList *q = (LinkedList *) malloc(sizeof(LinkedList));
    q->next = NULL;
    return q;
}

int LinkedListIsEmpty(LinkedList *q) {
    return q->next == NULL;
}

LinkedList *LinkedListGetEnd(LinkedList *q) {
    LinkedList *a = q;
    while (a->next != NULL) {
        a = a->next;
    }
    return a;
}

void LinkedListNodeAdd(int value, LinkedList *q) {
    LinkedList *end = LinkedListGetEnd(q);
    LinkedList *node = (LinkedList *) malloc(sizeof(LinkedList));
    node->value = value, node->next = NULL;
    end->next = node;
}

void LinkedListPrint(LinkedList *q) {
    LinkedList *a = q->next;
    while (a->next != NULL) {
        printf("%d ", a->value);
        a = a->next;
    }
    printf("%d\n", a->value);
}

void LinkedListUpDown(LinkedList *q) {
    LinkedList *a = q->next;
    LinkedList *last = NULL;
    while (a->next != NULL) {
        LinkedList *next = a->next;
        a->next = last;
        last = a;
        a = next;
    }
    a->next = last;
    q->next = a;
}

int LinkedListSearch(int value, int index, LinkedList *q) {
    LinkedList *a = q->next;
    int cnt = -1, count = 0;
    while (count < index && a->next != NULL) {
        cnt++;
        if (a->value == value)count++;
        a = a->next;
    }
    if (a->value == value && a->next==NULL)count++;
    if (count == index)return cnt;
    return -1;
}

//链表头不放任何值，只用来访问链表
int main() {
    LinkedList *Q = LinkedListCreate();
    LinkedListNodeAdd(1, Q);
    LinkedListNodeAdd(2, Q);
    LinkedListNodeAdd(3, Q);
    LinkedListNodeAdd(5, Q);
    LinkedListNodeAdd(5, Q);
    LinkedListPrint(Q);
    LinkedListUpDown(Q);
    LinkedListPrint(Q);
    printf("%d\n", LinkedListSearch(5, 1, Q));
    printf("%d\n", LinkedListSearch(5, 2, Q));
}
