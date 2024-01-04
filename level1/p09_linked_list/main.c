//输入结束请输入-1哦
#include <stdio.h>
#include <malloc.h>
#include <assert.h>
#include <stdbool.h>
typedef struct node{
    int x;
    struct node *next;
}node,*Pnode;
typedef struct List{
    Pnode start;
    Pnode last;
    size_t size;
}List;
int cnt1=1,cnt2=0,flag=0;
void Init(List *list){
    list->start=NULL;
    /*list->start=*/list->last=(node*)malloc(sizeof(node));
    assert(list->last!=NULL);
    /*list->start->next=*/list->last->next=NULL;
    list->size=0;
    return;
}
void Push_back(int a,List *list){
    node *s=(node*)malloc(sizeof(node));
    assert(s!=NULL);
    s->next=NULL;
    s->x=a;
    list->last->next=s;
    list->last=s;
    list->size++;
    if(list->start==NULL) list->start=s;
    return;
}
void reverse(node *p,List *list){
    if(p==NULL) list->last=list->start;
    if(list->start==NULL) return;
    if(list->start->next==NULL){
        list->start->next=p;
        list->last->next=NULL;
        return;
    }
    /*node *s=(node*)malloc(sizeof(node));
    assert(s!=NULL);
    node *n=(node*)malloc(sizeof(node));
    assert(n!=NULL);*/
    node *s,*n;
    s=list->start->next;
    n=list->start;
    list->start->next=p;
    list->start=s;
    reverse(n,list);
    return;
}
void print(List *list){
    node *s=list->start;
    while(s!=NULL){
        printf("%d ",s->x);
        s=s->next;
    }
    //printf("%d %d",list->start->x,list->start->next->x);
    return;
}
void search(List *list,int n){
    node *s=list->start;
    while(s->next!=NULL){
        if(s->x==n && cnt2!=0){
            cnt1++;
            flag=2;
            return;
        }
        if(s->x==n && cnt2==0){
            cnt2=cnt1;
            flag=1;
        }
        cnt1++;
        s=s->next;
    }
    if(cnt2==0) flag=0;
    return;
}
int main() {
    int tmp;
    List list;
    Init(&list);
    while(scanf("%d",&tmp)) {
        if(tmp==-1) break;
        Push_back(tmp, &list);
    }
    print(&list);
    reverse(NULL,&list);
    printf("\n");
    print(&list);
    printf("\n");
    search(&list,5);
    if(!flag) printf("-1\n-1");
    else{
        if(flag==1) printf("%d\n-1",cnt2);
        else printf("%d\n%d",cnt2,cnt1-cnt2);
    }
    return 0;
}