//
// Created by ycm on 2023/10/24.
//

#include "calculator.h"

signed char priority(char c){
    switch (c){
        case '+':
        case '-':
            return 1;
        case '*':
        case '/':
        case '%':
            return 2;
        case '^':
            return 3;
        case '(':
        case ')':
            return 0;
        default:
            return -1;
    }
}

char* my_concat_str(char* str1, char* str2, unsigned len2){
    for(unsigned j=0;j<len2;j++)str1[j] = str2[j];
    return str1;
}

char* Dijkstra(const char* raw_str) {
    char* result = malloc(sizeof(char) * strlen(raw_str)*2), tmp[100] = {};
    result[0] = 0;
    unsigned presult = 0, ptmp = 0;
    Stack * st = initStack(100);
    char c=raw_str[0];
    char pop_num;
    for(unsigned i=0;c!=0;c=raw_str[++i]){
        if(priority(c)==-1){
            tmp[ptmp++] = c;
        }else{
            if(i!=0&&ptmp) {
                my_concat_str(result+presult,tmp,ptmp);//不要使用 strcat ,程序不对 tmp 以 0 结尾做保证
                presult += ptmp;
                ptmp = 0;
                result[presult++] = 0x20;
            }
            if(c=='('){ pushStack(st,c);
                continue;}
            if(c==')'){
                while((pop_num= (char)popStack(st))!='(')result[presult++] = pop_num;
                continue;
            }
            if(c=='^') {
                while (!isEmptyStack(st) && priority((char) *(st->pointer - 1)) > priority(c) &&
                       *(st->pointer - 1) != '(')
                    result[presult++] = (char) popStack(st);
            }
            else {
                while (!isEmptyStack(st) && priority((char) *(st->pointer - 1)) >= priority(c) &&
                       *(st->pointer - 1) != '(')
                    result[presult++] = (char) popStack(st);
            }

            pushStack(st, c);

        }
    }

    if(ptmp!=0) {
        my_concat_str(result+presult,tmp,ptmp);
        presult += ptmp;
    }
    result[presult++]=0x20;
    while(!isEmptyStack(st))result[presult++]= (char)popStack(st);
    result[presult++]=0;
    return result;
}

int calculator(const char* raw_str) {
    Stack* st = initStack(100);
    int tmp = 0;
    char c=raw_str[0];
    for(unsigned i=0;c!=0;c=raw_str[++i]){
        if('0'<=c&&c<='9') { tmp = tmp * 10 + c - '0'; }
        else if(c==0x20) { if(raw_str[i-1]>='0'&&raw_str[i-1]<='9') {
                pushStack(st, tmp);
                tmp = 0;
            }else continue;
        }
        else {
            int num2 = popStack(st), num1 = popStack(st);
            if(c=='+'){ pushStack(st, num1+num2);}
            if(c=='-'){ pushStack(st, num1-num2);}
            if(c=='*'){ pushStack(st, num1*num2);}
            if(c=='/'){ pushStack(st, num1/num2);}
            if(c=='%'){ pushStack(st, num1%num2);}
            if(c=='^'){ pushStack(st, (int)pow(num1,num2));}
    }}
    return popStack(st);
}
