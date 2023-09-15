#include <stdio.h>
using namespace std;
int main() {
    int n;
    bool flag=true;
    scanf("%d",&n);
    for (int i=2;i*i<=n;i++){
        if(n%i==0){
            flag=false;
            break;
        }
    }
    if(flag==true) printf("Is Prime");
    else printf("Not Prime");
    return 0;// 
}
