#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"mini5phone.h"

int menu() {
	printf("Phonebook Menu: (1)Add, (2)Delete/Clear, (3)Find, (4)List, (5)Quit> ");
	char array[100];
	fgets(array, 99, stdin);
	return atoi(array);
}

int main() {
	int x, y, m, file_does_not_exist;
	struct PHONE_NODE *current = head;
	char garbage;
	char name[51], birthdate[13], phone[16], name_to_find[51];
	file_does_not_exist = loadCSV("phonebook.csv");     //equals 1 if it doesn't exist

	while (1) {
		x = menu();
		switch(x) { 
			case 1: printf("Name: ");
				fgets(name, 50, stdin);
				printf("Birth: ");
				fgets(birthdate, 12, stdin);
				printf("Phone: ");
				fgets(phone, 15, stdin);
				
				name[strlen(name)-1] = '\0';  //getting rid of carriage return
				birthdate[strlen(birthdate)-1] = '\0';
				phone[strlen(phone)-1] = '\0';

				addRecord(name, birthdate, phone);	
				file_does_not_exist = 0; // file must exist now
				break;

			case 2: if (file_does_not_exist) {
                                        puts("phonebook.csv does not exist");                 
                                        break;
                                }
				printf("(D)elete or (C)lear: ");
				char option[6];
				fgets(option, 5, stdin);
				option[strlen(option)-1] = '\0';
					if (strcmp(option, "D")==0){
						printf("Please provide the name of the user you want to delete: ");
						char username[51];
						fgets(username, 50, stdin);
						int m = delete(username);
						if (m == 1) puts("Sorry not found");
						break;
					}
					else if (strcmp(option, "C")==0){
						printf("Are you sure Y/N>");
						char garbage, to_clear = getc(stdin);
						garbage = getc(stdin); // get rid of carriage return
						if (to_clear == 'N') break; 
						clear();
						break;
					}
					else{
						puts("Invalid input! Enter D or C");
						break;
					}
			case 3: if (file_does_not_exist) {
					puts("phonebook.csv does not exist"); 		      
					break;
				}
				char garbage;
				printf("Find name: ");
				fgets(name_to_find, 50, stdin);
				name_to_find[strlen(name_to_find)-1] = '\0';
				y = findRecord(name_to_find);
				if (y == -1) puts("No such person can be found");
				else {
					puts("----NAME--------- ------BIRTH------ -----PHONE-------"); //copied from listRecords()
							struct PHONE_NODE *current = head;
							//loop until we get to the record we want
							for (int i = 0; i < y; i++){
								current = current->next;
							}
							//print name with proper spacing
							int len = strlen(current->name);
			                printf("%s", current->name);
			                for (;len < 18; len++) printf(" ");

							//print birthdate with proper spacing
			                len = strlen(current->birthdate);
			                printf("%s", current->birthdate);
			                for (;len < 18; len++) printf(" ");

			                if (strlen(current->phone) == 12) printf("  %s\n", current->phone);//spacing details
			                else printf("%s\n", current->phone);
						
							
				}
				break;

			case 4: if (file_does_not_exist) {
					puts("Phonebook.csv does not exist");
					break;
				}
				listRecords();
				break;
			
			case 5: saveCSV("phonebook.csv");
				puts("End of phonebook program");
			        exit(0);	
				
			default: puts("Invalid input! Enter a number between 1-5");

		}
	}	
}
				
