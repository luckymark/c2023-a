#include<stdio.h>
#include<windows.h>
#include<string.h>
char word[800];
char secret[800];
char letter[800];
void encryption(){
     int len=strlen(word);
     len--;
     for(int i=0;i<len;i++){
         if(word[i]>='a' && word[i]<='z'){
             secret[i]=word[i]+1;
         }else if(word[i]>='0' && word[i]<='9'){
             secret[i]=word[i]+1;
         }else if(word[i]>='A' && word[i]<='Z'){
             secret[i]=word[i]+1;
         }else secret[i]=word[i];
     }
     printf("密文为:%s\n",secret);
}
void decryption(){
    int len=strlen(secret);
    for(int i=0;i<len;i++){
        if(secret[i]>='a' && secret[i]<='z'){
            letter[i]=secret[i]-1;
        }else if(secret[i]>='0' && secret[i]<='9'){
            letter[i]=word[i]-1;
        }else if(secret[i]>='A' && secret[i]<='Z'){
            letter[i]=secret[i]-1;
        }else letter[i]=secret[i];
    }
    printf("明文为:%s\n",letter);
}
int main(){
    for(int i=0;;i++){
        word[i]=getchar();
        if(word[i]=='\n')break;
    }
    encryption();
    decryption();
    system("pause");
}
