#ifndef C2023_CHALLENGE_LINKED_H
#define C2023_CHALLENGE_LINKED_H
#include <stdio.h>
#include <stdlib.h>
typedef struct
{
    int data;
    int num;
    struct Node* next;
}Node;
void Creat_list(Node* pHead,int n);
Node* List(Node* pHead,int n);
void Print_list(Node* pHead,int n);
void Anti_list(Node* pHead,int n);
int Find_5(Node* pHead,int start,int n);
#endif //C2023_CHALLENGE_LINKED_H
