# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <stdbool.h>

extern int Level;

typedef struct hash{
    int citizenId;
    char * Name;
    char Country;
    int Age;
    char * Virus;
    bool Vaccinated;
    // Date;
}Citizens;
