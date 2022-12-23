typedef enum {ATMLoad, ATMDebit} ATM_Transaction_Type_Enum;

typedef struct ATMCashRecord	{
	char Date[11];
	long long AcctNo;
	ATM_Transaction_Type_Enum ATMLoadDebit;
	double Amount;
} ATMCashRecStruct;


void ATMLoadTransactions();
void DisplayATMCashPosition();
void ATMLoadCash();
void postATMTransaction(ATMCashRecStruct* ac);
double DisplayATMCashBalance();


#define ATM_CASH_FILE "ATMCash.dat"