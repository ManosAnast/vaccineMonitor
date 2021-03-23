# include "Virus.h"

typedef struct Country{
    char * CName;
    int Population;
    struct Country * Next;
}Country;

Country * CountryCreate();

Country * CountrySearch(Country * CList, char * Name);

void CountryInsert(Country ** CList, char * CName);

void CountryDestroy(Country ** CList);
