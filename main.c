#include <stdio.h>
#include <stdlib.h>
#include "Bank_Func_Proto.h"
#define EXIT 8

int main()
{
    FILE *fp = NULL;
    struct Members *front = NULL;
    struct Members *back = NULL;
    char ch;
    fp = fopen("Header.txt", "r");
    int option = 0;
    printf("Welcome to Sammy's Bank. Please follow the instructions below.\n");
    if (fp != NULL)
    {
        while ((ch = fgetc(fp)) != EOF)
        {
            printf("%c", ch);
        }
    }
    else
    {
        printf("File failed to open.\n");
        exit(EXIT_FAILURE);
    }

    printf("\nEnter the number associated with the operation you wish to do: ");
    scanf("%d", &option);

    int oper = 0;
    while (option != EXIT)
    {
        switch (option)
        {
            case 1:
                New_Member(&front, &back);
                Display_Client(front);
                break;
            case 2:
                Display_Client(front);
                 break;
            case 3:
                Display_Client_Reverse(back);
                break;
            case 4:
                printf("Enter 1 to Deposit or 2 to Withdraw: ");
                scanf("%d", &oper);
                if(oper ==  1 || oper == 2)
                {
                    Account_Mod(&front, &back, oper);
                }
                else
                {
                    printf("The value you entered was invalid\n");
                }
                break;
            case 5:
                Delete_Member(&front, &back);
                break;
            case 6:
                Budget(&front, &back);
                break;
            case 7:
                Transfer(&front, &back);
                break;
        }

        fseek(fp, 0, SEEK_SET);
        while ((ch = fgetc(fp)) != EOF)
        {
            printf("%c", ch);
        }

        printf("\nEnter the number associated with the operation you wish to do: ");
        scanf("%d", &option);
    }
    fclose(fp);
    printf("Thank you for using Sammy's Bank.\nGoodbye.\n");
    return 0;
}
