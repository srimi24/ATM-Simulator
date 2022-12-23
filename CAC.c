#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "CustomerAccountCreation.h"


void main()	{
	
	system("cls");

	CustAcctDetRecStruct cadr;
	CustLedgerDetRecStruct cldr;

	printf("\nEnter New Customer (must be 10 numbers in length)");
	printf("\n------------------------------------------------");

	fflush(stdin);
	printf("\nEnter Acct No: ");
	scanf("%lld", &cadr.AcctNo);

	char accNoStr[21] = "";
	sprintf(accNoStr,"%lld", cadr.AcctNo);
	if(strlen(accNoStr) != 10)	{
		printf("Acct. No must be 10 numbers in length\n");
		exit(0);
	}

	if ( !IsUniqueAcctNoCardNo(cadr.AcctNo) )	{
		printf("Account number or Card number already exists\n");
		exit(0);
	}

	fflush(stdin);
	printf("\nEnter Acct Name: ");
	//scanf("%s", cadr.AcctName);
	gets(cadr.AcctName);

	fflush(stdin);
	printf("\nEnter Card No (must be 16 numbers in length): ");
	scanf("%lld", &cadr.CardNo);

	char cardNoStr[21] = "";
	sprintf(cardNoStr,"%lld", cadr.CardNo);
	if(strlen(cardNoStr) != 16)	{
		printf("Card No must be 16 numbers in length\n");
		exit(0);
	}

	if ( !IsUniqueAcctNoCardNo(cadr.CardNo) )	{
		printf("Account number or Card number already exists\n");
		exit(0);
	}

	fflush(stdin);
	printf("\nEnter User Name: ");
	scanf("%s", cadr.UserName);
	if(strlen(cadr.UserName) != 8)	{
		printf("User Name must be 8 characters in length\n");
		exit(0);
	}

	cadr.Pin = getRandomNumber();

	fflush(stdin);
	printf("\nEnter Opening Balance: ");
	scanf("%lf", &cldr.Amount);

	cadr.AadharNo = 0;

	cldr.AcctNo = cadr.AcctNo;
	cldr.creditDebit = Credit;
	cldr.next = NULL;
	
	writeCustAcctDetRecord(&cadr);
	writeCustLedgerDetRecord(&cldr);

	printCustAcctDetRecord();
	printCustLedgerDetRecord();
}
