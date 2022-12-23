#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "CustomerAccountCreation.h"
#include "ATMTransactions.h"
#include "LedgerTransactionsList.h"


CustLedgerDetRecStruct* root = NULL;

int fetchCustBalanceStmt(long long AcctNo)	{
	FILE* fp = fopen( CUST_LEDGER_FILE, "r" );
	if (fp == NULL)	{ 
		printf("There is an issue with opening file.. %s", CUST_LEDGER_FILE);
		exit(0);
	}

	CustLedgerDetRecStruct cldr;
	int totalTransactions = 0;

	int nbytes = fread( &cldr, sizeof(CustLedgerDetRecStruct), 1, fp );

	while( nbytes )	{
		if(AcctNo == cldr.AcctNo)	{
			addCustLedgerDetRecToList( &cldr );
			totalTransactions += 1;
		}
		nbytes = fread( &cldr, sizeof(CustLedgerDetRecStruct), 1, fp );
	}

	fclose(fp);

	return totalTransactions;
}

void addCustLedgerDetRecToList( CustLedgerDetRecStruct* cldr )	{

	CustLedgerDetRecStruct* cldrRec = (CustLedgerDetRecStruct*) malloc(sizeof(CustLedgerDetRecStruct));

	cldrRec->AcctNo = cldr->AcctNo;
	strcpy(cldrRec->Date, cldr->Date);
	
	cldrRec->creditDebit = cldr->creditDebit;
	cldrRec->Amount = cldr->Amount;
	cldrRec->next = NULL;
	
	if( root == NULL)
		root = cldrRec;
	else	{
		CustLedgerDetRecStruct* cldrTemp = root;

		while( cldrTemp->next != NULL )
			cldrTemp = cldrTemp->next;
		
		cldrTemp->next = cldrRec;		
	}
}

void deleteCustLedgerDetRecList()	{
	
	if( root == NULL)
		printf("Customer Ledger Records list is empty\n");
	else	{
		while( root != NULL )	{
			CustLedgerDetRecStruct* cldrDelete = root;
			root = root->next;
			free(cldrDelete);
		}		
	}
}

double getCustBalance()	{
	if( root == NULL )
		printf("No Customer Ledger Transactions found\n");
	else	{
		double Amount = 0;

		CustLedgerDetRecStruct* cldrList = root;
		while( cldrList != NULL )	{
			
			if(cldrList->creditDebit == Credit)
				Amount = Amount + cldrList->Amount;
			else
				Amount = Amount - cldrList->Amount;


			cldrList = cldrList->next;
		}
		return Amount;
	}
}

void printCustBalanceStmt(long long AcctNo)	{

	int totalTransactions = fetchCustBalanceStmt(AcctNo);

	if( root == NULL )
		printf("No Customer Ledger Transactions found\n");
	else	{
		printf("The Balance Amount: %lf\n\n",getCustBalance());

		printf("Last 5 transactions are.. \n\n");

		CustLedgerDetRecStruct* cldrList = root;

		while(totalTransactions > 5)	{
			cldrList = cldrList->next;
			totalTransactions = totalTransactions - 1;
		}

		while( cldrList != NULL )	{
			char strTemp[100];
			sprintf(strTemp, "%s ", cldrList->Date);
			if(cldrList->creditDebit == Credit)
				strcat(strTemp, "Credit  ");
			else
				strcat(strTemp, "Debit   ");

			char strAmount[21];
			sprintf(strAmount, "%lf", cldrList->Amount);
			strcat(strTemp, strAmount);

			printf("%s\n", strTemp);

			cldrList = cldrList->next;
		}
	}

	deleteCustLedgerDetRecList();
}