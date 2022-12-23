#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CustomerAccountCreation.h"
#include "ATMTransactions.h"
#include "Authentication.h"
#include "ATMCash.h"


int main()	{

	// Insert card (card no in a file)
	// Login username and password
	// Balance statement (last 5 transactions)
	// Withdraw money
	// Allow the user to change the password i.e. pin
	// Deposit money
	// KYC
	// Keep track of the total amount present in the ATM in terms of denominations
	
	CustAcctDetRecStruct cadr;
	int login = Login(&cadr);

	if( !login )	{
		printf("\nInvalid User Name or Pin entered\n");
		exit(0);
	}
	
	if(login == 9999)	{
		ATMCashRecStruct ac;
		ac.AcctNo = 9999999999;
		ac.ATMLoadDebit = ATMLoad;

		ATMLoadTransactions(&ac);
	}
	else
		ATMTransactions(&cadr);
}