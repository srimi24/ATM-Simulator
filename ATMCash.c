#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>


#include "ATMCash.h"


void ATMLoadTransactions(ATMCashRecStruct* ac)	{

	system("cls");

	printf("Authentication successful\n\n");
	printf("\n\n");
	printf("-------------------------------\n");
	printf("Press 1 : ATM Cash position\n");
	printf("Press 2 : ATM Cash load\n");
	printf("Press 3 : To exit\n");
	printf("-------------------------------\n");
	
	int adminOption = 9;
	scanf("%d", &adminOption);
	
	switch(adminOption)	{
		case 1:
			DisplayATMCashPosition();
			break;
		case 2:
			ATMLoadCash(ac);
			break;
		case 3:
			exit(0);
		default:
			printf("Invalid option entered\n");
			exit(0);
	}
}

void DisplayATMCashPosition()	{

	printf("The ATM Cash Balance: %lf\n", DisplayATMCashBalance());

	FILE* fp = fopen( ATM_CASH_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", ATM_CASH_FILE);
		exit(0);
	}

	ATMCashRecStruct ac;
	
	int nbytes = fread( &ac, sizeof(ATMCashRecStruct), 1, fp );

	if (nbytes==0)
		printf("ATM is empty\n");

	printf("\nThe ATM Cash Details are:\n\n");
	printf("Date     , Account No, ATM Transaction Type, Amount\n");
	printf("-----------------------------------------------------\n");

	while( nbytes )	{
		char tempStr[100];
		sprintf(tempStr, "%s, %lld,", ac.Date, ac.AcctNo);
		if(ac.ATMLoadDebit == ATMLoad)
			strcat(tempStr, " ATM Load            ,");
		else
			strcat(tempStr, " Cust Debit          ,");
		
		char tempBal[21];
		strcat(tempStr, itoa(ac.Amount, tempBal, 10));
		printf("%s\n", tempStr);

		nbytes = fread( &ac, sizeof(ATMCashRecStruct), 1, fp );
	}

	fclose(fp);
}

double DisplayATMCashBalance()	{

	FILE* fp = fopen( ATM_CASH_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", ATM_CASH_FILE);
		exit(0);
	}

	ATMCashRecStruct ac;
	
	int nbytes = fread( &ac, sizeof(ATMCashRecStruct), 1, fp );

	if (nbytes==0)
		printf("ATM is empty\n");

	double ATMBalance=0;

	while( nbytes )	{
		if(ac.ATMLoadDebit == ATMLoad)
			ATMBalance += ac.Amount;
		else
			ATMBalance -= ac.Amount;
		
		nbytes = fread( &ac, sizeof(ATMCashRecStruct), 1, fp );
	}

	fclose(fp);

	return ATMBalance;
}

void ATMLoadCash(ATMCashRecStruct* ac)	{
	double Amt;
	printf("Enter Cash to be loaded in ATM:");
	scanf("%lf", &Amt);

	ac->Amount = Amt;

	postATMTransaction(ac);
}

void postATMTransaction(ATMCashRecStruct* ac)	{
	FILE* fp = fopen( ATM_CASH_FILE, "a" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", ATM_CASH_FILE);
		exit(0);
	}

	time_t now = time(0);
	struct tm* ltm = localtime(&now);
	sprintf(ac->Date, "%d-%d-%d", ltm->tm_mday, ltm->tm_mon+1, 1900+ltm->tm_year);


	fwrite( ac, sizeof(ATMCashRecStruct), 1, fp );

	fclose(fp);
}
