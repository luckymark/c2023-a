#include <stdio.h>
#include "linked_list.h"

int main() {
    List list1={NULL,NULL};
    int length = 0;
    int value = 0;

    printf("The length:");
    scanf("%d",&length);
    printf("Enter the value in order:\n");
    for(int i = 0;i<length;i++){
        scanf("%d",&value);
        listAdd(&list1,value);
        printf("Added %d to the list.\n",value);
    }
    printf("The whole list:\n");
    listPrint(&list1);

    listReverse(&list1);
    printf("The reversed list:\n");
    listPrint(&list1);

    listReverse(&list1);
    listShow(&list1,5);
    printf("The serial of the 1st \"5\":%d\n", listFind(&list1,5,1));
    printf("The serial of the 2nd \"5\":%d\n", listFind(&list1,5,2));

    return 0;
}