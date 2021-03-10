# include "bloomfilter.h"
# define NULLstring " "

typedef struct Country{
    char * CName;
    int Population;
    struct Country * Next;
}Country;

Country * CountryCreate();

Country * CountrySearch(Country * CList, char * Name);

void CountryInsert(Country ** CList, char * CName);



typedef struct Interface{
    char * VirusName;
    SkipList * vaccinated_persons;
    SkipList * not_vaccinated_persons;
    bloom filter;
    struct Interface * Next;
}Virus;


char ** BreakString(char * str, const char * s, int Num);

/* Takes a file and insert it's contents in hash.
 *
 * fp: File that contains the data that you want to insert.
 * 
*/
void Insert(FILE * fp);

Virus * VirusInit();

void VirusInsert(Virus ** VList, char * CitizenId, char * VName, bool Vaccinated, char * DateStr);

void VirusSkipList(Virus ** Vlist);

void VaccinateStatusBloom(Virus * Vlist, char * Id, char * VirusName);

void VaccinateStatus(Virus * Vlist, char * Id, char * VirusName);

void TTY(Virus * Vlist, Country * CList);

void ListNonVaccinated(Virus * Vlist, char * VName);

void InsertCitizenRecord(Virus * Vlist, Country * CList, char ** Array);

void VaccinateNow(Virus * Vlist, char ** Array);

Virus * VirusFind(Virus * Vlist, char * VirusName);

void populationStatus(Virus * VList, Country * CList, char ** Array);

int CalculateVaccinated(SkipList * SList, char * Country);

void popStatusByAge(Virus * Vlist, Country * CList, char ** Array);