# include "bloomfilter.h"

typedef struct Interface{
    char * VirusName;
    SkipList * vaccinated_persons;
    SkipList * not_vaccinated_persons;
    bloom filter;
    struct Interface * Next;
}Virus;

Virus * VirusInit();

void VirusInsert(Virus ** VList, char * CitizenId, char * VName, bool Vaccinated, char * DateStr);

void VirusSkipList(Virus ** Vlist);

void VirusDestroy(Virus ** VList);

Virus * VirusFind(Virus * Vlist, char * VirusName);
