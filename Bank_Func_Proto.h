#ifndef BANK_FUNC_PROTO_H_INCLUDED
#define BANK_FUNC_PROTO_H_INCLUDED

struct Members
{
	char* f_name;
	char* l_name;
	int acc_num;
	double checking;
	double savings;
	struct Members *next;
	struct Members *prev;
};

void New_Member(struct Members **front, struct Members **back);

int Account_Num_Gen();

void Name_Input(struct Members **current);

void Depos_Withd(struct Members  **current, int oper);

void Display_Client(struct Members *current);

void Display_Client_Reverse(struct Members *current);

void Account_Mod(struct Members **front, struct Members **back, int oper);

struct Members *Look_up(struct Members *current_f, struct Members *current_b);

void Delete_Member(struct Members **front, struct Members **back);

#endif // BANK_FUNC_PROTO_H_INCLUDED
