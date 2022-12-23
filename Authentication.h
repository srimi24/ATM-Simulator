
// define constants

#define True 1
#define False 0
#define INSERTCARD "InsertCard.txt"

// function declarations

int Login(CustAcctDetRecStruct* cadr);
int Authentication(char* userName, int pin, long long cardNo, CustAcctDetRecStruct* cadr);
int checkInsertCard(long long* cardNoP);
void getPassword(char* pass);
