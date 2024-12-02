#include <stdio.h>
int main()
{
    int vc[10]={163,347,45,346,775,512,856,411,195,685}; //An array for example.

    int count = -1;
    while(count != 0){
        count = 0;
        for(int i = 0;i<9;i++){
            if(vc[i]>vc[i+1]){
                int temp;

                temp = vc[i+1];
                vc[i+1] = vc[i];
                vc[i] = temp;

                count++;
            }
        }
    }

    //Show the result.
    for(int i=0;i<10;i++){
        printf("vc[%d]=%d ",i,vc[i]);
    }

    return 0;
}