#include <stdio.h>
#include <stdlib.h>
#define LEN sizeof (struct Student)
struct Student
{
    int num;
    float score;
    struct Student * next;
};
struct Student * create();
void print(struct Student *head);
struct Student *inverse(struct Student *head);
struct Student *search(struct Student *head);
int main()
{
    struct Student *pt=create();
    print(pt);
    pt = inverse(pt);
    printf("After inversion,");
    print(pt);
    printf("The serial numbers of the nodes whose value is 5 are listed as:\n");
    while (search(pt)->next!=NULL)
    {
        printf("%d\n", search(pt)->num);
        pt = search(pt)->next;
    }
    if(search(pt)->score==5)
    {
        printf("%d\n", search(pt)->num);
    }
    printf("That's all.\n");
    printf("-1\n");
    return 0;
}
struct Student *create()
{
    printf("Enter the values.\n");
    struct Student *head;
    struct Student *p1,*p2,*p3;
    p1=p2=(struct Student*)malloc(LEN);
    scanf("%f",&p1->score);
    head=NULL;
    int n=0;
    while (p1->score!=0)
    {
        n++;
        if(n==1) head=p1;
        else p2->next=p1;
        p2=p1;
        p1=(struct Student *) malloc(LEN);
        scanf("%f",&p1->score);
    }
    p2->next=NULL;
    p3=head;
    p3->num=1;
    while(p3->next!=NULL)
    {
        (p3->next)->num=(p3->num+1);
        p3=p3->next;
    }
    return(head);
}
void print(struct Student *head)
{
    printf("Here are the records.\n");
    struct Student *p =head;
    if(head!=NULL)
    {
        do
        {
            printf("%5d  %5.1f\n",p->num,p->score);
            p=p->next;
        } while (p!=NULL);
    }
}
struct Student *inverse(struct Student *head)
{
    struct Student *p1,*p2,*p3;
    struct Student *p=head;
    p1=p->next;
    p->next=NULL;
    p2=p1->next;
    p1->next=p;
    while(p2->next!=NULL)
    {
        p3=p2->next;
        p2->next=p1;
        p1=p2;
        p2=p3;
    }
    p2->next=p1;
    p3->num=1;
    while(p3->next!=NULL)
    {
        (p3->next)->num=(p3->num+1);
        p3=p3->next;
    }
    return(p2);
}
struct Student *search(struct Student *head)
{
    struct Student *p=head;
    while (p->score!=5 && p->next!=NULL)
    {
        p=p->next;
    }
    if(p->score==5)
    {
        return(p);
    }
    return(p);
}
