# include "skiplist.h"

SkipList * SLInit(int Level)
{
    SkipList * SList;
    SList=(SkipList *)calloc(1,sizeof(SkipList));
    SList->CurrLevel=0; SList->Header=LLInit();
    return SList;
}


void SLInsert(SkipList * Slist)
{
    SLInsertHelper(&Slist);
    return;
}


void SLInsertHelper(SkipList ** Slist)
{
    SkipList * STemp= *Slist;
    LinkedList * LTemp= (*Slist)->Header;
    LinkedList * LList= (*Slist)->Header;

    srand(time(NULL));   // Initialize for "toss a coin" operation.
    
    int r = rand();
    int CurrLevel=STemp->CurrLevel;
    while (CurrLevel<= Level){
        while (LTemp != NULL)
        {
            if (rand() % 2){
                LList->Next[CurrLevel]=LTemp;
                LList=LTemp;
            }
            LTemp=LTemp->Next[0];
        }
        LList->Next[CurrLevel]=LTemp;
        CurrLevel += 1;
        LTemp=(*Slist)->Header;
    }
    return;
}