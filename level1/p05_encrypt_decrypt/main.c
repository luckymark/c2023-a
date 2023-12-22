#include <stdio.h>
#include <string.h>

void Enc(char* str, int shift)
{   int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = (str[i] - 'a' + shift) % 26 + 'a';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = (str[i] - 'A' + shift) % 26 + 'A';
        }
    }
    char copy[100];
    for(int i = 0;i<len;i++)
    {
        copy[i]=str[i];
    }
    for(int i = 0;i<len;i++)
    {
        str[i]=copy[len - 1 - i];
    }
}
void Dec(char *str, int shift)
{
    int len = strlen(str);
    for (int i = 0; i < len; i++)
    {
        if (str[i] >= 'a' && str[i] <= 'z')
        {
            str[i] = (str[i] - 'a' - shift + 26) % 26 + 'a';
        }
        else if (str[i] >= 'A' && str[i] <= 'Z')
        {
            str[i] = (str[i] - 'A' - shift + 26) % 26 + 'A';
        }
    }
    char copy[100];
    for(int i = 0;i<len;i++)
    {
        copy[i]=str[i];
    }
    for(int i = 0;i<len;i++)
    {
        str[i]=copy[len - 1 - i];
    }
}

int main()
{   setbuf(stdout,NULL);
    int shift = 0;
    flag:
    printf("Enter a shift(shift>0):");
    scanf("%d", &shift);
    if(shift<=0)
    {
        printf("ERROR\n");
        goto flag;
    }
    while(1)
    {
        int input = 0;
        arrow:
        printf("Please choose:\n1.Encrypt\n2.Decrypt\n3.Exit\n");
        scanf("%d", &input);
        char str1[1000], str2[1000];
        if (input == 1)
        {
            printf("Enter a string to Enc:");
            scanf("%s", str1);
            Enc(str1, shift % 26);
            printf("Encrypted string: %s\n", str1);
        }
        else if (input == 2)
        {
            printf("Enter a string to Dec:");
            scanf("%s", str2);
            Dec(str2, shift % 26);
            printf("Decrypted string: %s\n", str2);
        }
        else if (input == 3)
            break;
        else
        {
            printf("ERROR\n");
            goto arrow;
        }
    }
    return 0;
}
