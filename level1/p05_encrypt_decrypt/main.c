#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* encrypt(char *_clear);
char* decrypt(char *_cypher);
char* getstring();

//这个程序有内存问题，暂时还不会解决。
//没有实现任意长度输入。
int main() {
    printf("Enter the clear text which you want to encrypt:");
    char *clear = getstring();
    printf("The text you entered is:%s\n", clear);
    char *cypher = encrypt(clear);
    printf("The cypher is:%s\n", cypher);

    printf("Enter the clear text which you want to decrypt:");
    char *cypher1 = getstring();
    printf("The text you entered is:%s\n", cypher1);
    char *clear2 = decrypt(cypher1);
    printf("The clear text is:%s\n",clear2);

    return 0;
}

//wrong and unfinished.
char* encrypt(char *_clear){
    int len = (int)(strlen(_clear) + 1);
    char *cypher = (char*)malloc(len);
    strcpy(cypher,_clear);
    for (int i = 0;i < len - 1;i++){
        cypher[i] += i + 1;
    }
    return cypher;
}

char* decrypt(char *_cypher){
    int len = (int)(strlen(_cypher) + 1);
    char *clear = (char*)malloc(len);
    strcpy(clear,_cypher);
    for (int i = 0;i < len - 1;i++){
        clear[i] -= i + 1;
    }
    return clear;
}

char* getstring(){
    char *str = NULL;
    char *str_temp = NULL;
    int i = 1;
    str = (char*)malloc((i+1)*sizeof(char));
    while ( '\n' != (str[i-1] = getwchar()) ){
        i++;
        str_temp = (char*)malloc(strlen(str) + 1);
        strcpy(str_temp,str);
        free(str);
        str = (char*)malloc((i+1)*sizeof(char));
        if(str == NULL){
            free(str_temp);
            printf("Lack of memory.\n");
            return NULL;
        }
        strcpy(str,str_temp);
        free(str_temp);
    }
    str[i-1] = '\0';
    return str;
}