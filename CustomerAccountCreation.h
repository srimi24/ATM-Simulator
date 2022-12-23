// define constants

#define CUST_ACCT_DETAILS_FILE "cad.dat"
#define CUST_LEDGER_FILE "cl.dat"


// type specifications

typedef enum {Credit, Debit} CustTransactionTypeEnum;


typedef struct AccountRecord	{
	char UserName[9];
	int Pin;
	long long AcctNo;
	char AcctName[31];
	long long CardNo;
	long long AadharNo;
} CustAcctDetRecStruct;

typedef struct LedgerRecord CustLedgerDetRecStruct;

typedef struct LedgerRecord	{
	long long AcctNo;
	char Date[11];
	CustTransactionTypeEnum creditDebit;
	double Amount;
	
	struct LedgerRecord* next;
} CustLedgerDetRecStruct;


// function declarations

int IsUniqueAcctNoCardNo(long long AcctNo);
int getRandomNumber();
void writeCustAcctDetRecord( CustAcctDetRecStruct* cadr );
void writeCustLedgerDetRecord( CustLedgerDetRecStruct* cldr );
void printCustAcctDetRecord();
void printCustLedgerDetRecord();
