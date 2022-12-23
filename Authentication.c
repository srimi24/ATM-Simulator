// include header files

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <conio.h>

#include "CustomerAccountCreation.h"
#include "ATMTransactions.h"
#include "Authentication.h"


int Login(CustAcctDetRecStruct* cadr)	{

	system("cls");

	long long cardNo;
	int checkIC = checkInsertCard(&cardNo);
	if(!checkIC)	{
		printf("An issue with inserted card, Please contact the nearest branch\n");
		exit(0);
	}
	if (checkIC == 2)	{
		printf("Hello ATM Admin !!\n");
	}


	// UserName and Pin validations

	char userName[9] = "";
	int pin;

	printf("\nUser Login: ");
	printf("\n------------\n");

	fflush(stdin);
	printf("\nEnter User Name: ");
	scanf("%s", userName);
	if(strlen(userName) > 8)	{
		printf("User Name cannot exceed 8 characters in length\n");
		exit(0);
	}

	fflush(stdin);
	printf("\nEnter Pin: ");
	//scanf("%d", &pin);
	char pinStr[9]="";
	getPassword(pinStr);
	//itoa(pin, pinStr, 10);
	pin = atoi(pinStr);
	//printf("\nThe password is: %s", pinStr);

	if(strlen(pinStr) > 4)	{
		printf("\nPin cannot exceed 4 characters in length\n");
		exit(0);
	}
	
	// User & Pin authentication
	if (checkIC == 2)	{
		if(strcmp(userName,"$AAdmin$")==0 && (pin == 9999))
			return 9999;
		else
			printf("\nATM Admin Login unsuccessful\n");
			exit(0);
	}
	else
		return Authentication(userName, pin, cardNo, cadr);
}

void getPassword(char* pass)	{
	char ch;
	int i=0;
	while( (ch = _getch()) != 13 )	{
		*(pass+i) = ch;
		i++;
		printf("*");
	}
	*(pass+i) = '\0';
}

int checkInsertCard(long long* cardNoP)	{
	FILE* fp = fopen( INSERTCARD, "r" );
	if (fp == NULL)	{
		printf("There is an issue with opening file.. %s", INSERTCARD);
		exit(0);
	}
	
	long long cardNo;
	fscanf( fp, "%lld", &cardNo );

	fclose(fp);

	if (cardNo == 9999999999999999)
		return 2;

	fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}
	
	CustAcctDetRecStruct cadr;
	int nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nbytes )	{
		
		if( cadr.CardNo == cardNo )	{
			printf("Hello %s!\n", cadr.AcctName);
			*cardNoP = cardNo;
			return True;
		}

		nbytes = fread( &cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	}

	fclose(fp);

	return False;

}

int Authentication(char* userName, int pin, long long cardNo, CustAcctDetRecStruct* cadr)	{

	FILE* fp = fopen( CUST_ACCT_DETAILS_FILE, "r" );
	if (fp == NULL)	{
		printf("There is an issue with opening file.. %s", CUST_ACCT_DETAILS_FILE);
		exit(0);
	}
	
	int nbytes = fread( cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	while( nbytes )	{
		
		if( strcmp(userName, cadr->UserName) == 0 && (pin == cadr->Pin) && (cardNo == cadr->CardNo) )	{
			return True;
		}

		nbytes = fread( cadr, sizeof(CustAcctDetRecStruct), 1, fp );

	}

	fclose(fp);

	return False;
}
