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
		printf("\n\n\n\t Welcome to Call Data Record Application!!!\n\n");
		printf("\t\t================================================\n\n");
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
	fp = fopen("/home1/trainer02/shilpa/cdr/data/user_details.dat", "a+");
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
			sleep(3);
		}
		else
		{
			printf("\nUser already exist!!\n");
			sleep(3);
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
	fp = fopen("/home1/trainer02/shilpa/cdr/data/user_details.dat","r");
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
	fp = fopen("/home1/trainer02/shilpa/cdr/data/user_details.dat", "r");

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
			sleep(3);
			break;
		  } 
		
		}
	}
		if(flag == 0)
		{
			printf("\n\n Authentication Failed\n\n");
			sleep(3);
			
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
	printf("\n\n1. Process CDR File");
	printf("\n\n2. Billing");
	printf("\n\n3. Logout");
	printf("\nChoice: ");
	scanf("%d", &ch);
	switch(ch)
	{
		case 1: 
			process_cdr();
			break;
		case 2:
			billing();
			break;
		case 3:
			return EXIT_SUCCESS;
		default:
			printf("\n\nWrong Choice");
	}
  return EXIT_SUCCESS;
}
