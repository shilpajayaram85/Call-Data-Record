/*******************************************************************************************************************************************************
 * * FILE NAME : myFunction.c
 *
 * *DESCRIPTION : This file contains all the functions for CDR
 *
 * *REVISION HISTORY :
 *
 * *DATE                                          NAME                                    REFERENCE                                  REASONS
 -------------------------------------------------------------------------------------------------------------------------------------------------------
 * *23 MAY 2023                                 SHILPA J                                   New File                                  Initial            
 *******************************************************************************************************************************************************
 * * STANDARD HEADER FILE
 * *****************************************************************************************************************************************************/
   #include<myHeader.h>
/********************************************************************************************************************************************************
 * 
 * *FUNCTION NAME : mainMenu
 * 
 * *DESCRIPTION : This function shows home page of the application
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/
void mainMenu()
{
	int choice;
	while(1)
	{
		system("clear");
		printf("\n\n\n\t\t Welcome to Call Data Record Application!!!\n\n");
		printf("\n\n==============================================================================\n\n");
		printf("1. Signup\n");
		printf("2.Login\n");
		printf("3.Exit\n");
		printf("Choice: ");
		scanf("%d", &choice);
		switch(choice)
		{
			case 1: signUp();
				break;
			case 2: logIn();
				break;
			case 3: 
				printf("\n\n\tThankyou for using our application!!!\n");
				printf("\n\t\t********\n");
				exit(0);
				break;
			default:
				printf("\n\n\tWrong Choice!\n\n");
		}
	}
}

/*******************************************************************************************************************************************************
 *
 * *FUNCTION NAME : signUp
 *
 * *DESCRIPTION : This function sign up for the new user
 *
 * *RETURN : Nothing
 * *****************************************************************************************************************************************************/

void signUp()
{

	char user_name[MAX_LENGTH];
	char password[MAX_LENGTH];
	char re_password[MAX_LENGTH];
	FILE *fp = NULL;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/user_details.dat", "a+");
	if(fp == NULL)
	{
		printf("\n\nPlease try later!!\n\n");
		exit(EXIT_FAILURE);
	}
	printf("\n\n*****SIGNUP*****\n");
	printf("\nEnter user ID : ");
	scanf("%s", user_name);
	printf("\nEnter the password : ");
        scanf("%s", password);
	
	printf("\nRe enter the password : ");
	scanf("%s", re_password);
	if(strcmp(password,re_password) == 0)
	{
		if(userAllowed(user_name, password))
		{
			fprintf(fp, "%s %s\n", user_name, password);
			printf("\nRegistration successful\n\n");
			printf("\nLogin with username and password\n");
			sleep(2);
		}
		else
		{
			printf("\nUser already exist!!\n");
			sleep(2);
		}
	}
	else
	{
		printf("Password mismatch\n");
		sleep(3);
	}
	fclose(fp);
	mainMenu();

}

/*******************************************************************************************************************************************************
 *
 * *FUNCTION NAME : userAllowed
 *
 * *DESCRIPTION : This function checks if user is existing or not
 * *
 * *RETURN : Flag
 * *****************************************************************************************************************************************************/

int userAllowed(char user_name[], char password[])
{
	char exist_username[MAX_LENGTH];
	char exist_password[MAX_LENGTH];
	int flag = 1;
	FILE *fp;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/user_details.dat","r");
	if(fp == NULL)
	{
		printf("\n\n Please try later\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
		while(fscanf(fp,"%s %s\n", exist_username,exist_password)== 2)
		{
			if(strcmp(user_name,exist_username) == 0)
			{
				flag = 0;
				break;
			}
		}
	fclose(fp);
	return flag;
	}
}


/*******************************************************************************************************************************************************
 *
 * *FUNCTION NAME : logIn
 *
 * *DESCRIPTION : This function provides the login for existing user
 *
 * *RETURN : Nothing
 * *****************************************************************************************************************************************************/

void logIn()
{
	char user_name[MAX_LENGTH];
	char password[MAX_LENGTH];
	char exist_username[MAX_LENGTH];
	char exist_password[MAX_LENGTH];
	int flag = 0;

	FILE *fp = NULL;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/user_details.dat", "r");

	if(fp == NULL)
	{
		printf("\n\nPlease try later!!\n\n");
		exit(EXIT_FAILURE);
	}

	printf("\n\n******LOGIN******\n\n");
	printf("\nEnter user ID : ");
	scanf("%s", user_name);
	printf("\nEnter the password : ");
        scanf("%s", password);
	
	while(fscanf(fp,"%s %s\n", exist_username,exist_password)== 2)
	{
		if(strcmp(user_name,exist_username) == 0)
		{
		  if(strcmp(password,exist_password) == 0)	
		  { 
			printf("\n\nLogin Successful\n\n");
			flag = 1;
			billingMenu();
			printf("\n\nLogout Successful\n\n");
			sleep(2);
			break;
		  } 
		
		}
	}
		if(flag == 0)
		{
			printf("\n\n Authentication Failed\n\n");
			sleep(2);
			
		}

	
	fclose(fp);
}


/*******************************************************************************************************************************************************
 *
 * *FUNCTION NAME : billingMenu
 *
 * *DESCRIPTION : This function provides billing menu for users
 *
 * *RETURN : Nothing
 * *****************************************************************************************************************************************************/

int billingMenu()
{
	int ch;
	USER *usr = NULL;
	while(1)
	{
	printf("\n\n1. Process CDR File");
	printf("\n\n2. Billing");
	printf("\n\n3. Logout");
	printf("\n\nChoice: ");
	scanf("%d", &ch);

	switch(ch)
	{
		case 1: 
			if(usr == NULL)
			{
				USER* temp = process_cdr();
				usr =temp;
				if(usr==NULL)
				{	
					printf("\n\nProcess Failed\n");
				}
				else
				{
					printf("\n\nProcessed the file\n");
					
				}
			}
			else
			{
				printf("\n\nFile Already Processed");
			}
			break;
		case 2:
			billing(usr);
			break;
		case 3:
			free(usr);
			return EXIT_SUCCESS;
		default:
			printf("\n\nWrong Choice");
	}
  }
  return EXIT_SUCCESS;
}

/*******************************************************************************************************************************************************
 *
 * *FUNCTION NAME : process_cdr
 *
 * *DESCRIPTION : This function will process the cdr file
 *
 * *RETURN : Array of Structure
 * *****************************************************************************************************************************************************/

int n = 0;
USER *process_cdr()
{
	FILE *fp;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/data.cdr", "r");
	USER *usr = NULL;
	char record[9][MAX_LENGTH];
	char line[MAX_LENGTH]={0};
	int i = 0;
	
	if(fp == NULL)
	{
		printf("\n\nPlease try Later");
		return NULL;
	}
	else
	{
		
		while(fgets(line,MAX_LENGTH,fp)!=NULL)
		{
			char *token = strtok(line,"|");
			while(token != NULL)
			{
				if(i ==7 && strcmp(record[3],"GPRS")==0)
				{	
					strcpy(record[i]," ");
					i++;
					continue;
				}
				strcpy(record[i],token);
				token = strtok(NULL, "|");
				i++;
			}
			
			i = 0;
			n++;
			usr = realloc(usr, n*sizeof(USER));
			
			strcpy(usr[n-1].msisdn, record[0]);
			strcpy(usr[n-1].opbrand, record[1]);
			strcpy(usr[n-1].opmmc, record[2]);
			strcpy(usr[n-1].calltype, record[3]);
			strcpy(usr[n-1].dur, record[4]);
			strcpy(usr[n-1].download, record[5]);
			strcpy(usr[n-1].upload, record[6]);
			strcpy(usr[n-1].thirdpartymsisdn, record[7]);
			strcpy(usr[n-1].thirdpartyopbrand, record[8]);
			
		}
	}
	fclose(fp);
	return usr;
}

/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : billing()
 *
 * *DESCRIPTION : This function shows the menu for billing
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/
void billing(USER *usr)
{
	int ch;
	printf("\n\n 1.Customer Billing \n\n 2.Interoperator Billing\n\n");
	printf("\n\nChoice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 1: 
			customerBillingFile(usr);
			break;
		case 2: 
			interOperatorBillingFile(usr);
			break;
	}
}

/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : customerBilling
 *
 * *DESCRIPTION : This function calculates the customer bill
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/

void customerDetails(USER *usr)
{
	char msisdn[20];
	printf("\n\nEnter msisdn number\n");
	scanf("%s", msisdn);
	int i;
	int flag = 0;
	for(i = 0; i < n; i++)
	{
		if(strcmp(usr[i].msisdn, msisdn) == 0)
		{
			printf("\n\n==========USER DETAILS===============\n\n");
			printf("\nMSISDN: %s", usr[i].msisdn);
			printf("\nBRAND NAME: %s", usr[i].opbrand);
			printf("\nOP MMC/MNC: %s", usr[i].opmmc);
			printf("\nCALL TYPE: %s", usr[i].calltype);
			printf("\nDURATION: %s", usr[i].dur);
			printf("\nDOWNLOAD: %s", usr[i].download);
			printf("\nUPLOAD: %s", usr[i].upload);
			printf("\nTHIRD PARTY MSISDN: %s", usr[i].thirdpartymsisdn);
			printf("\nTHIRD PARTY BRAND NAME: %s", usr[i].thirdpartyopbrand);
			flag = 1;
			break;
		}
	}
	if(flag == 0)
	{
	printf("\n\nCustomer not found\n\n");
	}
}	



/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : interOperatorBilling
 *
 * *DESCRIPTION : This function calculates the interoperator bill
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/

void interOperatorBilling(USER *usr)
{
	int i;
	int flag = 0;
	
	long int incomingcall = 0, outgoingcall = 0, incomingsms = 0, outgoingsms = 0, downloaded = 0, uploaded = 0;
	char op_number[20];
	char opname[MAX_LENGTH] = {0};
	printf("\n\nEnter the operator number\n");
	scanf("%s", op_number);
	for(i = 0;i < n; i++)
	{
		if(strcmp(op_number,usr[i].opmmc) == 0)
		{
			flag = 1;
			if(strcmp(usr[i].calltype,"MOC") == 0)
			{
				outgoingcall += atol(usr[i].dur);
			}
			else if(strcmp(usr[i].calltype,"MTC") == 0)
                        {
                                incomingcall += atol(usr[i].dur);
                        }
			else if(strcmp(usr[i].calltype,"SMS-MO") == 0)
                        {
                                outgoingsms += 1;
                        }
			else if(strcmp(usr[i].calltype,"SMS-MT") == 0)
                        {
                                incomingsms += 1;
                        }
			else if(strcmp(usr[i].calltype,"GPRS") == 0)
                        {
                                downloaded += atol(usr[i].download);
				uploaded += atol(usr[i].upload);
                        }
			strcpy(opname, usr[i].opbrand);
		}
	}
	if(flag == 0)
	{

        	printf("\n\nOperator not Found\n\n");
	}
	else
	{	
				
		printf("\n======Interoperator Billing===========\n");
		printf("\nOperator Brand : %s ( %s )", opname,op_number);
		printf("\nIncoming Voice Call Durations: %ld", incomingcall);
		printf("\nOutgoing Voice Call Durations: %ld", outgoingcall);
		printf("\nIncoming SMS Messages: %ld", incomingsms);
		printf("\nOutgoing SMS Messages: %ld", outgoingsms);
		printf("\nMB Downloaded: %ld | MB Uploaded: %ld", downloaded,uploaded);

	}
	
   
}


/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : customerBilling
 *
 * *DESCRIPTION : This function calculates the customer bill
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/

void customerBilling(USER *usr)
{
 	char msisdn[20];
        printf("\n\nEnter msisdn number\n");
        scanf("%s", msisdn);
        int i;
        int flag = 0;
        for(i = 0; i < n; i++)
        {
		if(strcmp(usr[i].msisdn, msisdn) == 0)
                {
                     printf("\nCustomer ID: %s ( %s )", usr[i].msisdn, usr[i].opbrand);

			if( atoi(usr[i].opmmc) == atoi(usr[i].thirdpartyopbrand) )
			{
				printf("\n\t* Services within the mobile operator *");
				if(strcmp(usr[i].calltype,"MTC") == 0 || strcmp(usr[i].calltype, "MOC") == 0)
				{
					if(strcmp(usr[i].calltype,"MTC") == 0 )
					{
						printf("\n\tIncoming voice call durations: %s", usr[i].dur);
						printf("\n\tOutgoing voice call durations: 0");
						printf("\n\tIncoming SMS messages: 0");
						printf("\n\tOutgoing SMS messages: 0 ");
					}
					if(strcmp(usr[i].calltype,"MOC") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: %s",usr[i].dur);
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 0 ");
                                        }
				}
				 if(strcmp(usr[i].calltype,"SMS-MT") == 0 || strcmp(usr[i].calltype, "SMS-MO") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"SMS-MT") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 1");
                                                printf("\n\tOutgoing SMS messages: 0 ");
					}
                                        if(strcmp(usr[i].calltype,"SMS-MO") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 1 ");
					}
                                }

				 printf("\n\n* Services outside the mobile operator *");
				 printf("\n\tIncoming voice call durations: 0");
                                 printf("\n\tOutgoing voice call durations: 0");
                                 printf("\n\tIncoming SMS messages: 0");
                                 printf("\n\tOutgoing SMS messages: 0");
			}				
			else

			{
				 printf("\n\n * Services within the mobile operator *");
                                 printf("\n\tIncoming voice call durations: 0");
                                 printf("\n\tOutgoing voice call durations: 0");
                                 printf("\n\tIncoming SMS messages: 0");
                                 printf("\n\tOutgoing SMS messages: 0 ");
					
				 printf("\n\n * Services outsisde the mobile operator *");

                                if(strcmp(usr[i].calltype,"MTC") == 0 || strcmp(usr[i].calltype, "MOC") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"MTC") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: %s", usr[i].dur);
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 0 ");
                                        }
                                        if(strcmp(usr[i].calltype,"MOC") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: %s",usr[i].dur);
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 0 ");
                                        }
                                }
                                 if(strcmp(usr[i].calltype,"SMS-MT") == 0 || strcmp(usr[i].calltype, "SMS-MO") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"SMS-MT") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 1");
                                                printf("\n\tOutgoing SMS messages: 0 ");
                                         }
                                        if(strcmp(usr[i].calltype,"SMS-MO") == 0 )
                                        {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 1 ");
                                        }
				}
			}
			if(strcmp(usr[i].calltype, "GPRS")==0)
                                {
                                                printf("\n\tIncoming voice call durations: 0");
                                                printf("\n\tOutgoing voice call durations: 0");
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 0 ");

                                }

                        printf("\n\t* Internet use *");
                        printf("\n\tMB downloaded: %s | MB uploaded: %s",usr[i].download,usr[i].upload);
			flag = 1;
                        break;
                }
        }
        if(flag == 0)
        {
        printf("\n\nCustomer not found\n\n");
        }
}



/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : interOperatorBillingFile
 *
 * *DESCRIPTION : This function calculates the interoperator bill and writes to file
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/

void interOperatorBillingFile(USER *usr)
{
	int i, k;
	//int flag = 0;

	//long int incomingcall = 0, outgoingcall = 0, incomingsms = 0, outgoingsms = 0, downloaded = 0, uploaded = 0;
	//char op_number[20];
	//char opname[MAX_LENGTH] = {0};
	
	IOP op[5];
	char msg[2048]={0};
	char temp[MAX_LENGTH];
	FILE *fp;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/IOSB.txt", "w");
	if(fp == NULL)
	{
		printf("\n\n Please Try Later\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
	//printf("\n\nEnter the operator number\n");
	//scanf("%s", op_number);
	
	for(k = 0; k < 5; k++)
	{
		bzero(op[k].opname,20);
		op[k].incomingcall = 0;
		op[k].outgoingcall = 0;
		op[k].incomingsms = 0;
		op[k].outgoingsms = 0;
		op[k].downloaded = 0;
		op[k].uploaded = 0;
	}
	strcpy(op[0].opmmc ,"42500");
	strcpy(op[1].opmmc ,"42501");
	strcpy(op[2].opmmc ,"42502");
	strcpy(op[3].opmmc ,"42503");
	strcpy(op[4].opmmc ,"42504");


	for(i = 0;i < n; i++)
	{
		
		 for(k = 0; k < 5; k++)
        {

		if(strcmp(op[k].opmmc,usr[i].opmmc) == 0)
		{
			
			if(strcmp(usr[i].calltype,"MOC") == 0)
			{
				op[k].outgoingcall += atol(usr[i].dur);
			}
			else if(strcmp(usr[i].calltype,"MTC") == 0)
                        {
                                op[k].incomingcall += atol(usr[i].dur);
                        }
			else if(strcmp(usr[i].calltype,"SMS-MO") == 0)
                        {
                                op[k].outgoingsms += 1;
                        }
			else if(strcmp(usr[i].calltype,"SMS-MT") == 0)
                        {
                                op[k].incomingsms += 1;
                        }
			else if(strcmp(usr[i].calltype,"GPRS") == 0)
                        {
                                op[k].downloaded += atol(usr[i].download);
				op[k].uploaded += atol(usr[i].upload);
                        }
			strcpy(op[k].opname, usr[i].opbrand);
		}
	   }
	}
		
		strcpy(msg,"\n# Operator Data Base: \n");
		memset(temp,0,MAX_LENGTH);
		 for(k = 0; k < 5; k++)
        	{

		sprintf(temp,"\nOperator Brand : %s ( %s )", op[k].opname,op[k].opmmc);
		strcat(msg, temp);
		memset(temp,0,MAX_LENGTH);
		sprintf(temp,"\nIncoming Voice Call Durations: %ld", op[k].incomingcall);
		strcat(msg, temp);
                memset(temp,0,MAX_LENGTH);
		sprintf(temp,"\nOutgoing Voice Call Durations: %ld", op[k].outgoingcall);
		strcat(msg, temp);
                memset(temp,0,MAX_LENGTH);
		sprintf(temp,"\nIncoming SMS Messages: %ld", op[k].incomingsms);
		strcat(msg, temp);
                memset(temp,0,MAX_LENGTH);
		sprintf(temp,"\nOutgoing SMS Messages: %ld", op[k].outgoingsms);
		strcat(msg, temp);
                memset(temp,0,MAX_LENGTH);
		sprintf(temp,"\nMB Downloaded: %ld | MB Uploaded: %ld", op[k].downloaded,op[k].uploaded);
		strcat(msg, temp);
		strcat(msg, "\n\n");
                memset(temp,0,MAX_LENGTH);
		fprintf(fp, "%s\n\n", msg);
		printf("\n\n%s\n\n", msg);

	}
	fclose(fp);
   }
}




/********************************************************************************************************************************************************
 *
 * *FUNCTION NAME : customerBillingFile
 *
 * *DESCRIPTION : This function calculates the customer bill and writes to file
 *
 * *RETURN : Nothing
 *******************************************************************************************************************************************************/

void customerBillingFile(USER *usr)
{
 	char msisdn[20];
	FILE *fp;
	fp = fopen("/home1/trainer02/Call-Data-Record/cdr/data/CB.dat","a+");
	if(fp == NULL)
	{
		printf("\n\n Please try later\n\n");
		exit(EXIT_FAILURE);
	}
	else
	{
        printf("\n\nEnter msisdn number\n");
        scanf("%s", msisdn);
        int i;
        int flag = 0;
	char msg[MAX_LENGTH];
	char temp[MAX_LENGTH];
	for(i = 0; i < n; i++)
        {
		if(strcmp(usr[i].msisdn, msisdn) == 0)
                {
                     	memset(temp, 0, MAX_LENGTH);
			sprintf(temp,"\nCustomer ID: %s ( %s )", usr[i].msisdn, usr[i].opbrand);
			strcpy(msg,temp);
			if( atoi(usr[i].opmmc) == atoi(usr[i].thirdpartyopbrand) )
			{
			
				memset(temp, 0, MAX_LENGTH);
				sprintf(temp,"\n\t* Services within the mobile operator *");
				strcat(msg, temp);
				if(strcmp(usr[i].calltype,"MTC") == 0 || strcmp(usr[i].calltype, "MOC") == 0)
				{
					if(strcmp(usr[i].calltype,"MTC") == 0 )

					{	
						
						memset(temp, 0, MAX_LENGTH);
						sprintf(temp,"\n\tIncoming voice call durations: %s", usr[i].dur);
						strcat(msg, temp);
						strcat(msg,"\n\tOutgoing voice call durations: 0");
						strcat(msg,"\n\tIncoming SMS messages: 0");
						strcat(msg,"\n\tOutgoing SMS messages: 0 ");
					}
					if(strcmp(usr[i].calltype,"MOC") == 0 )
                                        {
                                                strcat(msg, "\n\tIncoming voice call durations: 0");
						memset(temp, 0, MAX_LENGTH);
                                                sprintf(temp,"\n\tOutgoing voice call durations: %s",usr[i].dur);
						strcat(msg,temp);
                                                strcat(msg,"\n\tIncoming SMS messages: 0");
                                                strcat(msg,"\n\tOutgoing SMS messages: 0 ");
                                        }
				}
				 if(strcmp(usr[i].calltype,"SMS-MT") == 0 || strcmp(usr[i].calltype, "SMS-MO") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"SMS-MT") == 0 )
                                        {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                                strcat(msg,"\n\tIncoming SMS messages: 1");
                                                strcat(msg,"\n\tOutgoing SMS messages: 0 ");
					}
                                        if(strcmp(usr[i].calltype,"SMS-MO") == 0 )
                                        {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                               	strcat(msg,"\n\tIncoming SMS messages: 0");
                                                strcat(msg,"\n\tOutgoing SMS messages: 1 ");
					}
                                }

				 strcat(msg,"\n\n* Services outside the mobile operator *");
				 strcat(msg,"\n\tIncoming voice call durations: 0");
                                 strcat(msg,"\n\tOutgoing voice call durations: 0");
                                 strcat(msg,"\n\tIncoming SMS messages: 0");
                                 strcat(msg,"\n\tOutgoing SMS messages: 0");
			}
			else

			{
				 strcat(msg,"\n\n * Services within the mobile operator *");
                                 strcat(msg,"\n\tIncoming voice call durations: 0");
                                 strcat(msg,"\n\tOutgoing voice call durations: 0");
                                 strcat(msg,"\n\tIncoming SMS messages: 0");
                                 strcat(msg,"\n\tOutgoing SMS messages: 0 ");

				 strcat(msg,"\n\n * Services outsisde the mobile operator *");

                                if(strcmp(usr[i].calltype,"MTC") == 0 || strcmp(usr[i].calltype, "MOC") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"MTC") == 0 )
                                        {
                                                memset(temp,0,MAX_LENGTH);
						sprintf(temp,"\n\tIncoming voice call durations: %s", usr[i].dur);
						strcat(msg,temp);
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                                strcat(msg,"\n\tIncoming SMS messages: 0");
                                                strcat(msg,"\n\tOutgoing SMS messages: 0 ");
                                        }
                                        if(strcmp(usr[i].calltype,"MOC") == 0 )
                                        {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
						memset(temp,0,MAX_LENGTH);
                                                sprintf(temp,"\n\tOutgoing voice call durations: %s",usr[i].dur);
						strcat(msg,temp);
                                                printf("\n\tIncoming SMS messages: 0");
                                                printf("\n\tOutgoing SMS messages: 0 ");
                                        }
                                }
                                 if(strcmp(usr[i].calltype,"SMS-MT") == 0 || strcmp(usr[i].calltype, "SMS-MO") == 0)
                                {
                                        if(strcmp(usr[i].calltype,"SMS-MT") == 0 )
                                        {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                                strcat(msg,"\n\tIncoming SMS messages: 1");
                                                strcat(msg,"\n\tOutgoing SMS messages: 0 ");
                                         }
                                        if(strcmp(usr[i].calltype,"SMS-MO") == 0 )
                                        {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                                strcat(msg,"\n\tIncoming SMS messages: 0");
                                                strcat(msg,"\n\tOutgoing SMS messages: 1 ");
                                        }
				}
			}
			if(strcmp(usr[i].calltype, "GPRS")==0)
                                {
                                                strcat(msg,"\n\tIncoming voice call durations: 0");
                                                strcat(msg,"\n\tOutgoing voice call durations: 0");
                                                strcat(msg,"\n\tIncoming SMS messages: 0");
                                                strcat(msg,"\n\tOutgoing SMS messages: 0 ");

                                }

                        strcat(msg,"\n\t* Internet use *");
			memset(temp,0,MAX_LENGTH);
                        sprintf(temp,"\n\tMB downloaded: %s | MB uploaded: %s",usr[i].download,usr[i].upload);
			strcat(msg,temp);
			 fprintf(fp, "%s\n\n", msg);
                	printf("\n\n%s\n\n", msg);
	
			flag = 1;
                        break;
                }
        }
        if(flag == 0)
        {
        printf("\n\nCustomer not found\n\n");
        }
}
}
