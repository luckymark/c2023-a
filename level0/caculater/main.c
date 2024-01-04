//
// Created by ycm on 2023/10/24.
//
#include "calculator.h"
#include "stdio.h"

int main(){
    char str1[] = "4 1 2 + + 3 * 2 -";
    char str2[] = "1+(1+2*2-1)*3";
    printf("%d\n", calculator(str1));
    printf("%s\n", Dijkstra(str2));
    printf("%d", calculator(Dijkstra(str2)));

    return 0;
}