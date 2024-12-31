struct PHONE_NODE {
        char name[50];
        char birthdate[12];
        char phone[15];
        struct PHONE_NODE *next;
};
extern struct PHONE_NODE *head; 
int loadCSV(char *);
int saveCSV(char *);
int addRecord(char[], char[], char[]);
int findRecord(char *);
int listRecords();
int clear();
int delete(char[]);
