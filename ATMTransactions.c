// include header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#include "CustomerAccountCreation.h"
#include "ATMTransactions.h"
#include "LedgerTransactionsList.h"
#include "ATMCash.h"
#include "Authentication.h"


void ATMTransactions(CustAcctDetRecStruct* cadr)	{

	system("cls");

	printf("Authenticatin successful\n\n");
	printf("Welcome %s!\n", cadr->AcctName);
	printf("\n\n");
	printf("-------------------------------\n");
	printf("Press 1 : Balance Statement\n");
	printf("Press 2 : Withdraw Money\n");
	printf("Press 3 : Deposit Money\n");
	printf("Press 4 : Change Pin\n");
	printf("Press 5 : KYC\n");
	printf("Press 6 : To exit\n");
	printf("-------------------------------\n");

	fflush(stdin);
	int userOption = 9;
	scanf("%d", &userOption);
	
	switch(userOption)	{
		case 1:
			DisplayBalanceStatement(cadr->AcctNo);
			break;
		case 2:
			WithdrawMoney(cadr);
			break;
		case 3:
			DepositMoney(cadr);
			break;
		case 4:
			ChangePin(cadr);
			break;
		case 5:
			KYC(cadr);
			break;
		case 6:
			exit(0);
		default:
			printf("Invalid option entered\n");
			exit(0);
	}
}

void DisplayBalanceStatement(long long AcctNo)	{
	printCustBalanceStmt(AcctNo);
}
			
void WithdrawMoney(CustAcctDetRecStruct* cadr)	{
	system("cls");

	double Amount;
	fflush(stdin);
	printf("Enter Total Amount:\n");
	scanf("%lf", &Amount);

	if (Amount > DisplayATMCashBalance())	{
		printf("No Cash in the ATM\n");
		exit(0);
	}

	CustLedgerDetRecStruct cldr;
	cldr.AcctNo = cadr->AcctNo;
	cldr.creditDebit = Debit;
	cldr.Amount = Amount;

	writeCustLedgerDetRecord(&cldr);

	ATMCashRecStruct ac;
	ac.AcctNo = cadr->AcctNo;
	ac.ATMLoadDebit == ATMDebit;
	ac.Amount = Amount;
	
	postATMTransaction(&ac);
}

void DepositMoney(CustAcctDetRecStruct* cadr)	{
	system("cls");

	double depositAmount;
	fflush(stdin);
	printf("Enter Total Amount:\n");
	scanf("%lf", &depositAmount);

	CustLedgerDetRecStruct cldr;
	cldr.AcctNo = cadr->AcctNo;
	cldr.creditDebit = Credit;
	cldr.Amount = depositAmount;

	writeCustLedgerDetRecord(&cldr);
}

void ChangePin(CustAcctDetRecStruct* cadr)	{
	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}

	CustAcctDetRecStruct cadrTemp;
	
	int nRecs = fread( &cadrTemp, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nRecs )	{
		if(cadr->Pin == cadrTemp.Pin && cadr->AcctNo == cadrTemp.AcctNo)
			break;

		nRecs += fread( &cadrTemp, sizeof(CustAcctDetRecStruct), 1, fp );
	}
	
	fclose(fp);

	int Pin1;
	int Pin2;
	char pinStr1[9];
	char pinStr2[9];
	printf("\nEnter PIN to be changed:");
	getPassword(pinStr1);
	//scanf("%d", &Pin1);
	printf("\nRe-enter PIN:");
	getPassword(pinStr2);
	//scanf("%d", &Pin2);

	Pin1 = atoi(pinStr1);
	Pin2 = atoi(pinStr2);

	if(Pin1 != Pin2)	{
		printf("\nPIN mismatch\n");
		exit(0);
	}
	cadr->Pin = Pin1;

	fp = fopen( CUST_ACCT_DETAILS_FILE, "r+" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}

	fseek(fp, sizeof(CustAcctDetRecStruct) * (nRecs-1), SEEK_SET);
	fwrite( cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	fclose(fp);

	printf("\nThe PIN Successfully changed\n");
}

void KYC(CustAcctDetRecStruct* cadr)	{
	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}

	CustAcctDetRecStruct cadrTemp;
	
	int nRecs = fread( &cadrTemp, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nRecs )	{
		if(cadr->AcctNo == cadrTemp.AcctNo)
			break;

		nRecs += fread( &cadrTemp, sizeof(CustAcctDetRecStruct), 1, fp );
	}
	
	fclose(fp);

	if(cadr->AadharNo == 0)	{
		system("cls");
		printf("\nKYC Update\n");
		printf("-------------\n\n");
		printf("Enter Aadhar No (must be 12 numbers): ");
		scanf("%lld", &(cadr->AadharNo));
		
		//printf("%lld\n", cadr->AadharNo);

		char tempAadharNo[21] = "";
		sprintf(tempAadharNo, "%lld", cadr->AadharNo);

		//printf("%d",strlen(tempAadharNo));

		if(strlen(tempAadharNo) != 12)	{
			printf("Aadhar number must be 12 numbers\n");
		}
		else	{
			fp = fopen( CUST_ACCT_DETAILS_FILE, "r+" );
			if (fp == NULL)	{ 
				printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
				exit(0);
			}

			fseek(fp, sizeof(CustAcctDetRecStruct) * (nRecs-1), SEEK_SET);
			fwrite( cadr, sizeof(CustAcctDetRecStruct), 1, fp );

			fclose(fp);

			printf("\nThe KYC details successfully updated\n");
		}
	}
	else	{
		system("cls");
		printf("\n\nYour KYC details are already updated, the Aadhar No is : %lld", cadr->AadharNo);
	}
}
