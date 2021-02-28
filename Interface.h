# include "bloomfilter.h"
# define NULLstring " "

typedef struct Interface{
    char * VirusName;
    SkipList * vaccinated_persons;
    SkipList * not_vaccinated_persons;
    bloom filter;
    struct Interface * Next;
}Virus;


/* Takes a file and insert it's contents in hash.
 *
 * fp: File that contains the data that you want to insert.
 * 
*/
void Insert(FILE * fp);

Virus * VirusInit();

void VirusInsert(Virus ** VList, char * CitizenId, char * Name, char * Country, int Age, char * VName, bool Vaccinated/*,Date*/);
