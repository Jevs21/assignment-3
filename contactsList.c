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
	long nextVal;
	long compareNum;
	
	if(fopen("myContactsList.db", "r+") == NULL){
		data = fopen("myContactsList.db", "w+");
		fclose(data);
	}
	
	data = fopen("myContactsList.db", "r");
	fseek(data, -48, SEEK_END);
	nextVal = ftell(data);
	fclose(data);	
	
	start:printf("Do you wish to enter a new contact (Yes or No)?: ");
	fgets(menuChoice, 5, stdin);
	
	if(strncmp(menuChoice, "Yes", 3) == 0 && menuChoice[3] == '\n'){
		/*
		 * YES
		*/
		
		data = fopen("myContactsList.db", "a+");
		
		printf("First Name: ");
		fgets(fname, 100, stdin);
		if(fname[0] == '\n'){
			fname[0] = '\0';
		}
		else{
			fname[strlen(fname) - 1] = '\0';
		}
		entry.first_name_posn = sizeof(info) + nextVal; 
		
		
		printf("Last Name: ");
		fgets(lname, 100, stdin);
		if(lname[0] == '\n'){
			lname[0] = '\0';
		}
		else{
			lname[strlen(lname) - 1] = '\0';
		}
		entry.last_name_posn = entry.first_name_posn + strlen(fname) + 1;
		
		
		printf("Company Name: ");
		fgets(company, 100, stdin);
		if(company[0] == '\n'){
			company[0] = '\0';
		}
		else{
			company[strlen(company) - 1] = '\0';
		}
		entry.company_name_posn = entry.last_name_posn + strlen(lname) + 1;
		
		
		number:printf("Phone Number (enter only numbers): ");
		fgets(num, 100, stdin);
		if(num[0] == '\n'){
			num[0] = '\0';
			printf("Must input a phone number.\n");
			goto number;
		}
		num[strlen(num)] = '\0';
		for(i = 0; i < strlen(num - 1); ++i){
			if(isdigit(num[i]) == 0){
				num[0] = '\0';
				printf("Not a number try again!\n");
				goto number;
			}
		}
		entry.phone_number = strtoul(num, NULL, 0);
		
		email:printf("Email: ");
		fgets(email, 100, stdin);
		if(email[0] == '\n'){
			email[0] = '\0';
			printf("Must input an email.\n");
			goto email;
		}
		else{
			email[strlen(email) - 1] = '\0';
		}
		entry.email_posn = entry.company_name_posn + strlen(company) + 1;
		
		entry.next = entry.email_posn + strlen(email) + 1;
		
		/*
		 *PRINTS
		
		
		printf("%s %s %s %s\n", fname, lname, company, email);
		
		printf("Struct Size: %lu\n", sizeof(info));
		printf("First Name Pos: %lu\n", entry.first_name_posn);
		printf("Last Name Pos: %lu\n", entry.last_name_posn); 
		printf("Company Pos: %lu\n", entry.company_name_posn); 
		printf("Email Pos: %lu\n", entry.email_posn);
		printf("Next Struct Pos: %lu\n", entry.next);
		printf("\n");
		printf("Phone Number (part of struct): %lu\n", entry.phone_number); 
		
		*/
		
		fwrite(&entry, sizeof(info), 1, data);
		fwrite(fname, (strlen(fname) + 1), 1, data);  
		fwrite(lname, (strlen(lname) + 1), 1, data);  
		fwrite(company, (strlen(company) + 1), 1, data);
		fwrite(email, (strlen(email) + 1), 1, data);   
		
		menuChoice[0] = '\0';
		fname[0] = '\0';
		lname[0] = '\0';
		company[0] = '\0';
		email[0] = '\0';
		num[0] = '\0';
		nextVal = entry.next;
		
		fclose(data);
		
		goto start;
		
		
	}
	
	else if(strncmp(menuChoice, "No", 2) == 0 && menuChoice[2] == '\n'){
		menuChoice[0] = '\0';
		
		
		printf("Do you wish to retrieve contact (Yes or No)?: ");
		fgets(menuChoice, 5, stdin);
		
		if(strncmp(menuChoice, "Yes", 3) == 0 && menuChoice[3] == '\n'){
			
			num[0] = '\0';
			fname[0] = '\0';
			lname[0] = '\0';
			company[0] = '\0';
			email[0] = '\0';
			info retrieve[100];
			i = 0;
			int loop = 0;
			
			data = fopen("myContactsList.db", "r");
			
			printf("Phone Number: ");
			fgets(num, 100, stdin);
			num[strlen(num) - 1] = '\0';
			
			compareNum = strtoul(num, NULL, 0);
			
			fseek(data, 0, SEEK_SET);
			
			
			while(loop == 0){
				retrieve[i].next = 0;
				fread(&retrieve[i], sizeof(info), 1, data);
				fseek(data, 0, SEEK_END);
				if(compareNum == retrieve[i].phone_number){
					
					fseek(data, retrieve[i].first_name_posn, SEEK_SET);
					fread(&fname, (retrieve[i].last_name_posn - retrieve[i].first_name_posn), 1, data);
					
					fseek(data, retrieve[i].last_name_posn, SEEK_SET);
					fread(&lname, (retrieve[i].company_name_posn - retrieve[i].last_name_posn), 1, data);
									
					fseek(data, retrieve[i].company_name_posn, SEEK_SET);
					fread(&company, (retrieve[i].email_posn - retrieve[i].company_name_posn), 1, data);
										
					fseek(data, retrieve[i].email_posn, SEEK_SET);
					fread(&email, (retrieve[i].next - retrieve[i].email_posn), 1, data);
										
					
					printf("First Name: %s\n", fname);
					printf("Last Name: %s\n", lname);
					printf("Company Name: %s\n", company);
					printf("Phone Number: %lu\n", entry.phone_number);
					printf("Email: %s\n", email);
					fclose(data);
					goto start;
				}
				if(ftell(data) == retrieve[i].next){
					printf("No match found.\n");
					menuChoice[0] = '\0';
					num[0] = '\0';
					fclose(data);
					goto start;
				}
				fseek(data, retrieve[i].next, SEEK_SET);
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
