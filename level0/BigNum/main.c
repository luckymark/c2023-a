//
// Created by ycm on 2023/11/19.
//
#include "stdio.h"
#include "stdlib.h"
#define MAX_SIZE 100

typedef char* BigNum;

BigNum mul(BigNum a, BigNum b);
BigNum quickPow(BigNum base, int exp);
void printBigNum(BigNum n);
unsigned lenBigNum(BigNum n);
BigNum cpyBigNum(BigNum n1, BigNum n2);

int main(){
    char a[100] = {2};
    BigNum result;
    result = quickPow(a, 128);
    printBigNum(result);
    return 0;
}

BigNum mul(BigNum a, BigNum b){
    BigNum c = calloc(100, sizeof(signed char));
    unsigned lena=lenBigNum(a), lenb=lenBigNum((char*)b);
    char x;
    for(unsigned i=0;i<lena;i++){
        x=0;
        for(unsigned j=0;j<lenb;j++){
            c[i+j] = (char)(a[i]*b[j]+x+c[i+j]);
            x = (char)(c[i+j]/10);
            c[i+j] %= 10;
        }
        c[i+lenb] += x;
    }
    return c;
}

BigNum quickPow(BigNum basecpy, int exp){
    BigNum result = calloc(MAX_SIZE, sizeof(char));
    BigNum temp = calloc(MAX_SIZE, sizeof(char));
    BigNum base = calloc(MAX_SIZE, sizeof(char));
    cpyBigNum(base, basecpy);
    result[0] = 1;
    while(exp){
        if(exp&1) {
            cpyBigNum(temp, result);
            free(result);
            result = mul(temp, base);
        }
        cpyBigNum(temp, base);
        free(base);
        base = mul(temp, temp);
        exp >>= 1;
    }
    return result;
}

void printBigNum(BigNum n){
    unsigned len = lenBigNum(n);
    for(;len>0;len--)printf("%d", n[len-1]);
}

unsigned lenBigNum(BigNum n){
    unsigned len=0;
    for(unsigned i=0;i<MAX_SIZE;i++)if(n[i]!=0)len=i+1;
    return len;
}

BigNum cpyBigNum(BigNum n1, BigNum n2){
    for(unsigned i=0;i<MAX_SIZE;i++){
        n1[i]=n2[i];
    }
    return n1;
}
