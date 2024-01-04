// 简单的异或加密
#include "stdio.h"
#include "string.h"
#define MAX_SIZE 10000
void xor(char[], char[], char []);

int main() {
    char input[MAX_SIZE] = {};
    char key[MAX_SIZE] = {};
    printf("please press the raw string:");
    scanf("%s", input);
    printf("your raw string is '%s',please press the key:", input);
    scanf("%s", key);
    printf("your key string is '%s'", key);
    char out[MAX_SIZE] = {};
    xor(input, key, out);
//    for (int i=0; out[i]!=0;i++) putchar(out[i]);
    printf("string:%s", out);
    return 0;
}

void xor(char s[], char k[], char out[]){
//    char result[MAX_SIZE] = {0};
    unsigned long long len_k = strlen(k);
    for(int i=0; i<strlen(s);i++){
        out[i] = s[i]^k[i%len_k];
    }

}