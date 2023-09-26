#include <stdio.h>
#include <stdlib.h>
typedef struct node{
    int data;
    struct node *next;
}Linklist;
int befound[80];
Linklist * listmake (int n){
      Linklist *head,*node,*end;
      head=(Linklist*)malloc(sizeof(Linklist*));
      end=head;
      scanf("%d",&head->data);
      for(int i=1;i<=n-1;i++){
          node=(Linklist*)malloc(sizeof(Linklist*));
          scanf("%d",&node->data);
          end->next=node;
          end=node;
      }
      end->next=NULL;
      return head;
}
Linklist * listhead;
void updown(){
     Linklist *s=listhead;
     Linklist *last=listhead;
     while(s->next){
         Linklist *next=s->next;
         s->next=last;
         last=s;
         s=next;
     }
     s->next=last;
     listhead->next=NULL,listhead=s;
}
int listfind(int x){
    Linklist *s=listhead;
    int cnt=0;
    while(s->next){
        cnt++;
        if(s->data==x && !befound[cnt]){
            befound[cnt]=1;
            return cnt;
        }
    }
}
int main(){
    int n;
    scanf("%d",&n);
    listhead=listmake(n);
    Linklist *s=listhead;
    while(s->next){
        printf("%d\n",s->data);
        s=s->next;
    }
    printf("%d\n",s->data);
    updown();
    s=listhead;
    while(s->next){
        printf("%d\n",s->data);
        s=s->next;
    }
    printf("%d\n",s->data);
    int first=listfind(5);
    int second=listfind(5);
    while(1){}
}
