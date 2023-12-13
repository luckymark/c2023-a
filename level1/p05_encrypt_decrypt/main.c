#include <stdio.h>
void encrypt(char* input, int key) {
    for (int i = 0;input[i] != '\0'; ++i) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            input[i] = input[i] + key;
            if (input[i] > 'z') {
                input[i] = input[i] - 'z' + 'a' - 1;
            }
        } else if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] + key;
            if(input[i] > 'Z') {
                input[i] = input[i] - 'Z' + 'A' - 1;
            }
        }

    }
}
void decrypt(char* input,int key) {
    for (int i = 0;input[i] != '\0'; ++i) {
        if (input[i] >= 'a' && input[i] <= 'z') {
            input[i] = input[i] - key;
            if (input[i] > 'z') {
                input[i] = input[i] + 'z' - 'a' + 1;
            }
        } else if (input[i] >= 'A' && input[i] <= 'Z') {
            input[i] = input[i] - key;
            if(input[i] > 'Z') {
                input[i] = input[i] + 'Z' - 'A' + 1;
            }
        }

    }
}
int main() {
    char input[999];
    int key;
    printf("Enter key:");
    scanf("%d",&key);
    printf("Enter a message:");
    scanf("%s",input);
    encrypt(input, key);
    printf("Encrypted message: %s \n",input);
    char input2[999];
    int key2;
    printf("Enter key:");
    scanf("%d",&key2);
    printf("Enter a message:");
    scanf("%s",input2);
    decrypt(input2,key2);
    printf("Decrypted message: %s \n",input2);
}