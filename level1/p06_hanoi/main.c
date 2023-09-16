#include <stdio.h>

void hanoi(int layer,char a,char b,char c);

int main(){
    int layer = 0;
    char a = 'A',b = 'B',c ='C';
    printf("Set the number of layers of the hanoi to be solved:\n");
    scanf("%d",&layer);
    printf("Condition:A:%d B:0 C:0    Target:A:0 B:0 C:%d\n"
           "The steps are shown below:\n",layer,layer);
    hanoi(layer,a,b,c);
    return 0;
}

//a:base b:temporary c:target
void hanoi(int layer,char a,char b,char c){
    if (layer == 0) return;
    hanoi(layer - 1,a,c,b);//将base柱本层以上所有层，移到temporary柱暂存。
    printf("%c -> %c\n",a,c);//将base柱本层，移到target柱。
    hanoi(layer - 1,b,a,c);//将所有在temporary柱的暂存层，移到target柱。
}