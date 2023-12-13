#include <stdio.h>
#include <stdlib.h>

struct node {
    int value;
    struct node* next;
};

struct node** createlist(int nodeAmount) {
    struct node** list = malloc(nodeAmount * sizeof(struct node*));
    for (int i = 0; i < nodeAmount; ++i) {
        int num;
        printf("Enter the value of node %d: ",i+1);
        scanf("%d",&num);
        list[i] = malloc(sizeof(struct node));
        list[i] -> value = num;
        if(i > 0) {
            list[i-1] -> next = list[i];
        }
    }
    return list;
}
void printlist(struct node** list, int nodeAmount) {
    for (int i = 0; i < nodeAmount; ++i) {
        printf("%d",list[i] -> value);
    }
    printf("\n");
}
void reverselist(struct node** list,int nodeAmount) {
    int temp;
    for (int i = 0; i < nodeAmount / 2 + nodeAmount % 2; ++i) {
        temp = list[i] -> value;
        list[i] -> value = list[nodeAmount - i - 1] -> value;
        list[nodeAmount -i - 1] -> value = temp;
    }
}
void find(struct node** list , int nodeAmount , int value) {
    for (int i = 0; i < nodeAmount; ++i) {
        if (list[i] -> value == value) {
            printf("Find %d at node %d\n",value,nodeAmount + 1);
        }
    }
}
int main() {
    int nodeAmount;
    printf("Enter the amount of the nodes: ");
    scanf("%d",&nodeAmount);
    struct node** list = createlist(nodeAmount);
    printlist(list,nodeAmount);
    reverselist(list,nodeAmount);
    printlist(list,nodeAmount);
    reverselist(list,nodeAmount);
    printf("Enter the value you want to search for: ");
    int value;
    scanf("%d",value);
    find(list,nodeAmount,value);
    return 0;
}
