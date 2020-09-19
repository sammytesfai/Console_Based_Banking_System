#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "Bank_Func_Proto.h"
#define MAX 10

int Account_Num_Gen()
{
	int random = 0;
	srand(time(0));
	random = 1 + rand()%1000000000;
	return random;
}

void Depos_Withd(struct Members  **current, int oper)
{
    double money = 0;
    if(oper == 0)
    {
        printf("Enter the amount you wish to Deposit into savings: ");
        scanf("%lf", &(*current)->savings);
        printf("Enter the amount you wish to Deposit into checking: ");
        scanf("%lf", &(*current)->checking);
    }
    else if(oper == 1)
    {
        printf("Enter the amount you wish to Deposit into savings: ");
        scanf("%lf", &money);
        (*current)->savings += money;
        printf("Enter the amount you wish to Deposit into checking: ");
        scanf("%lf", &money);
        (*current)->checking += money;
    }
    else
    {
        printf("Enter the amount you wish to Withdraw into savings: ");
        scanf("%lf", &money);
        (*current)->savings -= money;
        printf("Enter the amount you wish to Withdraw into checking: ");
        scanf("%lf", &money);
        (*current)->checking -= money;
    }
}

struct Members *Look_up(struct Members *current_f, struct Members *current_b)
{
    int account_num = 0;
    printf("Enter the account number of member: ");
    scanf("%d", &account_num);
    while(current_f != NULL && current_b != NULL)
    {
        if(current_f->acc_num == account_num)
        {
            return current_f;
        }
        else if(current_b->acc_num == account_num)
        {
            return current_b;
        }
        current_f = current_f->next;
        current_b = current_b->prev;
    }
    printf("\n\nInvalid account number: %d\n\n", account_num);
    return NULL;
}

void Name_Input(struct Members **current)
{
    char f_name[MAX];
    size_t name_len = 0;
    printf("Enter the new members First name: ");
    scanf("%s", f_name);
    name_len = strlen(f_name);
    (*current)->f_name = (char*)malloc(sizeof(char) * name_len);
    strncpy((*current)->f_name, f_name, name_len);
    char l_name[MAX];
    printf("Enter the new members Last name: ");
    scanf("%s", l_name);
    name_len = strlen(l_name);
    (*current)->l_name = (char*)malloc(sizeof(char) * name_len);
    strncpy((*current)->l_name, l_name, name_len);
}

void New_Member(struct Members **front, struct Members **back)
{
	struct Members *current_b = *back;
	struct Members *current_f = *front;
	if (current_f == NULL)
	{
		current_f = (struct Members*)malloc(sizeof(struct Members));
		if (current_f == NULL)
		{
			printf("Failed to allocated memory for new member.\n");
			exit(EXIT_FAILURE);
		}
        Name_Input(&current_f);
		current_f->acc_num = Account_Num_Gen();
		Depos_Withd(&current_f, 0);

        current_f->next = NULL;
        current_f->prev = NULL;
        *front = current_f;
        *back = current_f;
	}
	else
    {
        struct Members *new_mem = NULL;
        new_mem = (struct Members*)malloc(sizeof(struct Members));
        current_b->next = new_mem;
        new_mem->prev = current_b;
        current_b = new_mem;
        current_b->next = NULL;

        Name_Input(&current_b);
        current_b->acc_num = Account_Num_Gen();
        Depos_Withd(&current_b, 0);
        *back = current_b;
    }
}

void Display_Client(struct Members *current)
{
    struct Members *print = current;
    if(print == NULL)
    {
        printf("There are no members on file.\n");
    }
    else
    {
        while(print != NULL)
        {
            printf("\nMember: %s %s\n",print->f_name, print->l_name);
            printf("Account#: %d\n", print->acc_num);
            printf("Savings: $%.2f\n", print->savings);
            printf("Checking: $%.2f\n\n", print->checking);
            print = print->next;
        }
    }
}

void Display_Client_Reverse(struct Members *current)
{
    struct Members *print = current;
    if(print == NULL)
    {
        printf("\nThere are no members on file.\n\n");
    }
    else
    {
        while(print != NULL)
        {
            printf("\nMember: %s %s\n",print->f_name, print->l_name);
            printf("Account#: %d\n", print->acc_num);
            printf("Savings: $%.2f\n", print->savings);
            printf("Checking: $%.2f\n\n", print->checking);
            print = print->prev;
        }
    }
}

void Account_Mod(struct Members **front, struct Members **back, int oper)
{
    struct Members *current_f = *front;
    struct Members *current_b = *back;
    struct Members *member = Look_up(current_f, current_b);
    if(member != NULL)
    {
        Depos_Withd(&member, oper);
    }
}

void Delete_Member(struct Members **front, struct Members **back)
{
    struct Members *current_f = *front;
    struct Members *current_b = *back;
    struct Members *members = Look_up(current_f, current_b);
    if(members != NULL)
    {
        if(members->next == NULL && members->prev != NULL)
        {
            members->prev->next = NULL;
            *back = members->prev;
            free(members);
        }
        else if(members->prev == NULL && members->next != NULL)
        {
            members->next->prev = NULL;
            *front = members->next;
            free(members);
        }
        else if(members->next == NULL && members->prev == NULL)
        {
            free(members);
            *front = NULL;
            *back = NULL;
        }
        else
        {
            members->prev->next = members->next;
            members->next->prev = members->prev;
            free(members);
        }
    }
}

void Budget(struct Members **front, struct Members **back)
{
    double monthly_income = 0;
    double monthly_costs = 0;
    struct Members *current_f = *front;
    struct Members *current_b = *back;
    struct Members *member = Look_up(current_f, current_b);
    printf("What is the members total monthly costs: ");
    scanf("%lf", &monthly_costs);
    printf("What is the members monthly income: ");
    scanf("%lf", &monthly_income);
    if(monthly_costs > monthly_income)
    {
        printf("\nMembers monthly income can not support monthly expenses.\n\n");
        return;
    }
    printf("\nThe recommended monthly budget for personal expenses would be: $%.2f\n", (monthly_income-monthly_costs)*.25);
    printf("12 month saving account projections would be: $%.2f\n\n", member->savings + (12*((monthly_income - monthly_costs)*.75)));
}

void Transfer(struct Members **front, struct Members **back)
{
    int oper = 2;
    double transfer_amount = 0;
    struct Members *current_f = *front;
    struct Members *current_b = *back;
    printf("\nTransferring Member:\n");
    struct Members *member = Look_up(current_f, current_b);
    if(member == NULL)
    {
        printf("\n\nCould not find member.\n\n");
        return;
    }
    printf("\n\nReceiving Member\n");
    struct Members *r_member = Look_up(current_f, current_b);
    if(r_member == NULL)
    {
        printf("\n\nCould not find member.\n\n");
        return;
    }
    printf("How much would you like to transfer: ");
    scanf("%lf", &transfer_amount);
    while(oper != 0 || oper != 1)
    {
        printf("Enter 0 to transfer from checking or 1 for savings: ");
        scanf("%d", &oper);
        if(oper == 0 && member->checking >= transfer_amount)
        {
            member->checking -= transfer_amount;
            r_member->checking += transfer_amount;
            printf("\n\n----Transfer Complete----\n\n");
            return;
        }
        else if(oper == 1 && member->savings >= transfer_amount)
        {
            member->savings -= transfer_amount;
            r_member->savings += transfer_amount;
            printf("\n\n----Transfer Complete----\n\n");
            return;
        }
        printf("\n\nIncorrect input operation\n\n");
    }
}
