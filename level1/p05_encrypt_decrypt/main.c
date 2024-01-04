#include <stdio.h>
int i=0;
void enc(char a[]){
    i=0;
    while(a[i]!='\0'){
        a[i]++;
        i++;
    }
}
void dec(char a[]){
    i=0;
    while(a[i]!='\0'){
        a[i]--;
        i++;
    }
}
int main() {
    char arr[100];
    gets(arr);
    enc(arr);
    printf("%s\n",arr);
    dec(arr);
    printf("%s",arr);
    return 0;
}