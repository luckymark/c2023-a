#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "limits.h"
#include "LinkList.h"

void print_list(LinkList* list){
    if(!(list->size)) { printf("(null)"); return; }
    LinkNode* p = list->head;
    for(unsigned i=0;i<list->size-1;i++){printf("'%s' -> ", (char*)p->value);p=p->next;}
    printf("'%s'", (char*)p->value);
}

int main(){
    const unsigned MAX_LENGTH = 100;
    LinkList *list = createLinkList();
    unsigned i = 0;
    char values[MAX_LENGTH];
    values[0] = '\0';
    printf(">>>");
    scanf("%s", values);
    while(values[0]!='#'){
        char* tmp = malloc(strlen(values)* sizeof(char));
        strcpy(tmp, values);
        appendLinkList(list, list->size, tmp);
        printf(">>>");
        scanf("%s", values);
        i++;
    }
    printf("create link list: ");
    print_list(list);
    reversedLinkList(list);
    printf("\nreversed link list: ");
    print_list(list);
    printf("\npress in the index of value to delete: ");
    scanf("%d", &i);
    bool res = removeLinkList(list, i);
    printf("\n%s\n", res?"delete success":"delete failed");
    print_list(list);

    printf("\npress in the index of value to search: ");
    scanf("%d", &i);
    char* ans = (char*)searchLinkList(list, i);
    printf("\n%s\n", ans);

    char** tolist = (char**) toList(list);
    for(i=0;i<list->size;i++)printf("%s, ", tolist[i]);
    destroyLinkList(list);
}
