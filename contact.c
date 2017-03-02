#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int main(void){
	
	struct contact {
		unsigned long phone_number;
		long first_name_posn;
		long last_name_posn;
		long company_name_posn;
		long email_posn;
		long next;
	};
	typedef struct contact info;
	
	char menuChoice[5];
	FILE *data;
	info entry;
	char fname[100];
	char lname[100];
	char company[100];
	char email[100];
	char num[100];
	int i = 0;
	
	if(fopen("myContactList.db", "r+") == NULL){
		data = fopen("myContactList.db", "w+");
		fclose(data);
	}
	
	start:printf("Do you wish to enter a new contact (Yes or No)?: ");
	fgets(menuChoice, 5, stdin);
	
	if(strncmp(menuChoice, "Yes", 3) == 0 && menuChoice[3] == '\n'){
		printf("Yes was chosen\n");
		/*
		 * YES
		*/
		
		data = fopen("myContactList.db", "a+");
		
		fseek(data, (-1 * sizeof(info)), SEEK_END);
		fread(&entry, sizeof(info), 1, data);
		
	
		printf("First Name: ");
		fgets(fname, 100, stdin);
		fname[strlen(fname)] = '\0';
		printf("%lu\n", sizeof(info));
		entry.first_name_posn = sizeof(info);
		printf("%lu\n", entry.first_name_posn); 
		
		printf("Last Name: ");
		fgets(lname, 100, stdin);
		lname[strlen(lname)] = '\0';
		entry.last_name_posn = sizeof(info) + strlen(fname) + 1;
		
		printf("Company Name: ");
		fgets(company, 100, stdin);
		company[strlen(company)] = '\0';
		entry.company_name_posn = entry.first_name_posn + strlen(lname) + 1;
		
		retry:printf("Phone Number (enter only numbers): ");
		
		fgets(num, 100, stdin);
		num[strlen(num)] = '\0';
		for(i = 0; i < strlen(num - 1); ++i){
			if(isdigit(num[i]) == 0){
				num[0] = '\0';
				printf("Not a number try again!\n");
				goto retry;
			}
		}
		entry.phone_number = strtoul(num, NULL, 0);		
		printf("%lu\n", entry.phone_number); 
		
		printf("Email: ");
		fgets(email, 100, stdin);
		email[strlen(email)] = '\0';
		entry.email_posn = entry.last_name_posn + strlen(company) + 1;
		
		entry.next = entry.email_posn + strlen(email) + 1;
		
		fseek(data, 0, SEEK_END);
		fwrite(&entry, sizeof(info), 1, data);
		fwrite(fname, (sizeof(char) * strlen(fname)), 1, data);  
		fwrite(lname, (sizeof(char) * strlen(lname)), 1, data);  
		fwrite(company, (sizeof(char) * strlen(company)), 1, data);
		fwrite(email, (sizeof(char) * strlen(email)), 1, data);   
		
		menuChoice[0] = '\0';
		fname[0] = '\0';
		lname[0] = '\0';
		company[0] = '\0';
		email[0] = '\0';
		num[0] = '\0';
		
		fclose(data);
		
		goto start;
		
		
	}
	
	else if(strncmp(menuChoice, "No", 2) == 0 && menuChoice[2] == '\n'){
		printf("No was chosen\n");
		menuChoice[0] = '\0';
		
		
		printf("Do you wish to retrieve contact (Yes or No)?: ");
		fgets(menuChoice, 5, stdin);
		
		if(strncmp(menuChoice, "Yes", 3) == 0 && menuChoice[3] == '\n'){
			
			num[0] = '\0';
			info retrieve[100];
			i = 0;
			
			data = fopen("myContactList.db", "r");
			
			printf("Phone Number: ");
			fgets(num, 100, stdin);
			
			fseek(data, 0, SEEK_SET);
			
			while(!feof(data)){
				
				fread(&retrieve[i], sizeof(info), 1, data);
				fseek(data, 0, retrieve[i].next);
				printf("%lu\n", retrieve[i].phone_number);
				++i;
			}
			
			
			
		}
		
		else if(strncmp(menuChoice, "No", 2) == 0 && menuChoice[2] == '\n'){
			return 0;
		}
		
	}
	
	else{
		printf("Invalid Entry\n");
		return (-1);
	}
	
	
	return 0;
}
