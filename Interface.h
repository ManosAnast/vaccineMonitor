# include "bloomfilter.h"
# define NULLstring " "

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

void VirusInsert(Virus ** VList, char * CitizenId, char * Name, char * Country, int Age, char * VName, bool Vaccinated/*,Date*/);

void VirusSkipList(Virus ** Vlist);

void VaccinateStatusBloom(Virus * Vlist, char * Id, char * VirusName);

void VaccinateStatus(Virus * Vlist, char * Id, char * VirusName);

void TTY(Virus * Vlist);