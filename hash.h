# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>

extern int Level,BloomNum;

typedef struct date{
    int Days;
    int Month;
    int Year;
}Date;

Date * CreateDate(char * DateStr);

void PrintDate(Date * Timing);

bool CheckDate(Date * Timing1, Date * Timing2);


typedef struct hash{
    int citizenId;
    char * FirstName;
    char * LastName;
    char * Country;
    int Age;
    char * Virus;
    bool Vaccinated;
    struct hash * Next;
    Date * Timing;
}Citizens;

// Creates the Hash Table
void HTCreate(int);

// Makes a new node with the given attributes
Citizens * NewRecord(int, char *, char *, char *, int, char *, bool, char * DateStr);

// Insert at the hash table a new node.
void HTInsert(int Id, char * FirstName, char * LastName, char * Country, int Age, char * Virus, bool Vaccinated, char * DateStr);

// Prints all the nodes of a Table.
void HTPrint();

Citizens * HTSearch(int Item, char * Virus);

void HTDestroy();