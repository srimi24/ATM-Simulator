
// type specifications


typedef struct AccountRecord CustAcctDetRecStruct;
typedef struct LedgerRecord CustLedgerDetRecStruct;

// function declarations

void ATMTransactions(CustAcctDetRecStruct* cadr);
void DisplayBalanceStatement();
void WithdrawMoney(CustAcctDetRecStruct* cadr);
void DepositMoney(CustAcctDetRecStruct* cadr);
void ChangePin(CustAcctDetRecStruct* cadr);
void KYC(CustAcctDetRecStruct* cadr);




