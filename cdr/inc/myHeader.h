/*******************************************************************************************************************************************************
 * * FILE NAME : myHeader.h
 *
 * *DESCRIPTION : This file contains all the header files for CDR Application
 *
 * *REVISION HISTORY :
 *
 * *DATE                                          NAME                                    REFERENCE                                  REASONS
 -------------------------------------------------------------------------------------------------------------------------------------------------------
 * *23 MAY 2023                                 SHILPA J                                   New File                                  Initial            
 *******************************************************************************************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>

#define MAX_LENGTH 1024
struct user
{
	char msisdn[20];
	char opbrand[64];
	char opmmc[20];
	char calltype[10];
	char dur[10];
	char download[10];
	char upload[10];
	char thirdpartymsisdn[20];
	char thirdpartyopbrand[20];
};

typedef struct user USER;


struct interoperator
{
	char opname[20];
	char opmmc[20];
	long int incomingcall;
	long int outgoingcall;
	long int incomingsms;
	long int outgoingsms;
	long int downloaded;
	long int uploaded;
};

typedef struct interoperator IOP;

void mainMenu();
void logIn();
void signUp();
int userAllowed(char[], char[]);

int billingMenu();

void billing(USER*);

void customerDetails(USER*);

USER* process_cdr();

void customerBilling(USER*);
void interOperatorBilling(USER*);
void interOperatorBillingFile(USER*);
void customerBillingFile(USER*);
