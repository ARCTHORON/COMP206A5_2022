#include"mini5phone.h"
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

struct PHONE_NODE *head;
int loadCSV(char *CSV_file_name) {
	FILE *CSV_file = fopen(CSV_file_name, "rt");
	int j,k;

	char line_from_CSV[1000];
	if (CSV_file == NULL || fgets(line_from_CSV, 999, CSV_file) == NULL) return(1); //fgets returns null if file empty

	head = (struct PHONE_NODE *) malloc(sizeof(struct PHONE_NODE));	
	head->next = NULL;

	for (j=0; line_from_CSV[j] != ',' ; j++) head->name[j] = line_from_CSV[j];   
        head->name[j] = '\0';
        j++;
        for (k=0; line_from_CSV[j] != ','; j++,k++) head->birthdate[k] = line_from_CSV[j];
        head->birthdate[k] = '\0';
        j++;
        for (k=0; line_from_CSV[j] != '\n' && line_from_CSV[j] != '\r'; j++,k++) head->phone[k] = line_from_CSV[j];         
        head->phone[k] = '\0';
	fgets(line_from_CSV, 999, CSV_file);

	while((!feof(CSV_file))) {    // checking file still contains contents 
		struct PHONE_NODE new;
		
		for (j=0; line_from_CSV[j] != ',' ; j++) new.name[j] = line_from_CSV[j]; 
		new.name[j] = '\0';
		j++;
		for (k=0; line_from_CSV[j] != ','; j++,k++) new.birthdate[k] = line_from_CSV[j];
		new.birthdate[k] = '\0';
		j++;char* username="";
		for (k=0; line_from_CSV[j] != '\n' && line_from_CSV[j] != '\r'; j++,k++) {
			new.phone[k] = line_from_CSV[j];
		}
		new.phone[k] = '\0';
		addRecord(new.name, new.birthdate, new.phone);
		fgets(line_from_CSV, 999, CSV_file);
	}

	fclose(CSV_file);
	return 0;
}
int saveCSV(char *CSV_file_name) {
	FILE *CSV_file = fopen(CSV_file_name, "wt");
	if (CSV_file == NULL) return 1;
	struct PHONE_NODE *node = head;
	
	while (node != NULL) {
		fprintf(CSV_file, "%s,%s,%s\n", node->name, node->birthdate, node->phone);
		node = node->next;
	}

	fclose(CSV_file);
	return 0;
}


int addRecord(char name[], char birthdate[], char phone[]) {
	struct PHONE_NODE *last=head;
	if (head == NULL) {
		head = (struct PHONE_NODE *) malloc(sizeof(struct PHONE_NODE));
		head->next = NULL;
		last = head;
	}
	else {
		while(last->next != NULL) last = last->next;
		last->next = (struct PHONE_NODE *) malloc(sizeof(struct PHONE_NODE));	//making new node
		last = last->next; //last now points to new node
		last->next = NULL;
	}

	strcpy(last->name, name);
	strcpy(last->birthdate, birthdate);
	strcpy(last->phone, phone);
	return 0;
}

int findRecord(char *name) {
	struct PHONE_NODE *current = head;
	int recordPosition=0;

	while (current != NULL) {
		if (strcmp(current->name, name) == 0) return recordPosition;
		current = current->next;
		recordPosition++;
	}

	return -1;   //not found
}

int listRecords() {
	struct PHONE_NODE *current = head;
	int len;

	puts("----NAME--------- ------BIRTH------ -----PHONE-------");

    //loop through the list
	while(current != NULL) {

	//get length of name to cachar* username="";lculate spacing
	//then print name with proper spacing
		len = strlen(current->name);
		printf("%s", current->name);
		for (int i=0; i<18-len; i++) printf(" ");

	//get length of birthdate to calculate spacing
	//then print birthdate with proper spacing
		len = strlen(current->birthdate);
		printf("%s", current->birthdate);
		for (int i=0; i<18-len; i++) printf(" ");

	//print phone number
		printf("%s\n", current->phone);

		current = current->next;
	}
	
	return 0;
}

int clear(){
        if (head == NULL){//returns 1 if the list is already empty so cannot clear
                return 1;
        }
        struct PHONE_NODE *tmp = (struct PHONE_NODE*) malloc(sizeof(struct PHONE_NODE));
	
   	while (head != NULL){//loop through the list and frees each node
       		tmp = head;
       		head = head->next;
		free(tmp);
        }
	return 0;
}

int delete(char username[50]){
        if (head == NULL){//returns 1 if the list is already empty so cannot find
               return 1;
        }

	//removes the newline character from the input
	username[strcspn(username, "\n")]=0;

	if (strcmp(head->name, username)==0){
		
		struct PHONE_NODE *tmp = head->next;
		free(head);
		head = tmp;
		return 0;
	}

        struct PHONE_NODE *tmp = head;
        while (tmp->next != NULL){
		//if next name is the correct one it deletes next node, otherwise iterates again
                if (strcmp(tmp->next->name, username) == 0){
          		struct PHONE_NODE *tokill=tmp->next;
			tmp->next = tmp->next->next;
			free(tokill);	
                        return 0;

                }
                else{
                        tmp = tmp->next;
                }

        }

        //failed to find at this point
        return 1;

}
