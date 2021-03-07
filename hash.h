# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>
# include <time.h>

extern int Level,BloomNum;

typedef struct hash{
    int citizenId;
    char * Name;
    char * Country;
    int Age;
    char * Virus;
    bool Vaccinated;
    struct hash * Next;
    // Date;
}Citizens;

// Creates the Hash Table
void HTCreate(int);

// Makes a new node with the given attributes
Citizens * NewRecord(int, char *, char *, int, char *, bool /*,Date*/);

// Insert at the hash table a new node.
void HTInsert(int Id, char * Name, char * Country, int Age, char * Virus, bool Vaccinated/*,Date*/);

// Prints all the nodes of a Table.
void HTPrint();

Citizens * HTSearch(int Item);