#include <stdio.h>
#include <windows.h>
#define len 80
#define sleep 50
#define sep '-'

void move(char a){
    int left=0,right=len-1;
    boolean s_right=1;
    for(;;){
        for(int i=0;i<left;i++)putchar(sep);
        putchar(a);
        for(int i=0;i<right;i++)putchar(sep);
        if (s_right){
            left++;right--;
        }else{
            left--;right++;
        }
        if (right==-1)s_right=0;
        else if (left==-1)s_right=1;
        Sleep(sleep);
    }
}

int main() {
    move(getchar());
    return 0;
}