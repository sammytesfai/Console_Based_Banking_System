This program simulates a banking system in C programming language.

void New_Member():
This function allows the user to input new clients
and autogenerates them an account number. It then prompts the user   
to deposit money in either their checking or savings account.
 
void Display_Client():
This funcitons allows the user to display all the clients currently      
in the banking systems linked list. Starting from the first client 
entered in.

void Display_Client_Reverese():
This function allows the user to display all the clients currently                  
in the banking systems linked list. Starting at the end and displaying 
them in reverse order from when entered in.

void Account_Mod():
This function allows the user to modify a client/members checking or 
savings account with the option to Deposit or Withdraw funds.

void Delete_Member():
This functions allows the user to delete any member in the list and 
identified the member by searching for the members account number that 
the user enters.

int Account_Num_Gen():
This heler functions generates a 9 digit random account number for every new member 
that is added.
 
void Name_Input():
This helper function prompts the user to enter the new members first and last 
name and inputs them in their corresponding account.

void Depos_Withd();
This helper function prompts the user to enter in what dollar amount they would like   
to withdraw/deposit from their account and modifies the corresponding value in their   
account.

struct Members *Look_up():
This helper functions identifies the client/member that is trying to be searched for 
and returns the structure address that correlates to the account.  
