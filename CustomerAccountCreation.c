// include header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CustomerAccountCreation.h"

int IsUniqueAcctNoCardNo(long long AcctNo)	{
	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{ 
		return 1;
	}

	CustAcctDetRecStruct cadr;
	
	int nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nbytes )	{
 
		if ( cadr.AcctNo == AcctNo || cadr.CardNo == AcctNo)	{
			return 0;
		}

		nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );
	}

	fclose(fp);
	
	return 1;
}

int getRandomNumber()	{
	int lower = 1000, upper = 9999;
	srand(time(0));

	int num = (rand() % (upper - lower + 1)) + lower;

	return num;
}

void writeCustAcctDetRecord( CustAcctDetRecStruct* cadr )	{

	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "a" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}

	fwrite( cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	fclose(fp);
}

void writeCustLedgerDetRecord( CustLedgerDetRecStruct* cldr )	{

	FILE* fp = fopen( CUST_LEDGER_FILE, "a" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_LEDGER_FILE);
		exit(0);
	}


	time_t now = time(0);
	struct tm* ltm = localtime(&now);
	sprintf(cldr->Date, "%d-%d-%d", ltm->tm_mday, ltm->tm_mon+1, 1900+ltm->tm_year);

	fwrite( cldr, sizeof(CustLedgerDetRecStruct), 1, fp );

	fclose(fp);
}

void printCustAcctDetRecord()	{
	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}

	printf("\nThe Customer Account Details are:\n\n");
	printf("User Name\t, Pin , Account No, Account Name, Card Number\n");
	printf("--------------------------------------------------------------\n");

	CustAcctDetRecStruct cadr;
	
	int nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nbytes )	{

		printf("%s\t, %d, %lld, %s, %lld\n", cadr.UserName, cadr.Pin, cadr.AcctNo, cadr.AcctName, cadr.CardNo);

		nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );
	}

	fclose(fp);
}


void printCustLedgerDetRecord()	{
	FILE* fp = fopen( CUST_LEDGER_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_LEDGER_FILE);
		exit(0);
	}

	printf("\nThe Customer Ledger Transactions are:\n\n");
	printf("Account No, Date     , Type  , Amount\n");
	printf("--------------------------------------\n");

	CustLedgerDetRecStruct cldr;

	int nbytes = fread( &cldr, sizeof(CustLedgerDetRecStruct), 1, fp );

	while( nbytes )	{

		char tempStr[100];
		sprintf(tempStr, "%lld, %s ,", cldr.AcctNo, cldr.Date);

		if( cldr.creditDebit == Credit )
			strcat(tempStr, "Credit,");
		else
			strcat(tempStr, "Debit,");

		strcat(tempStr, " ");

		char tempBal[21];
		strcat(tempStr, itoa(cldr.Amount, tempBal, 10));

		printf("%s\n", tempStr);

		nbytes = fread( &cldr, sizeof(CustLedgerDetRecStruct), 1, fp );
	}

	fclose(fp);
}
