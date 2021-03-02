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
    int CurrLevel=1;
    while (CurrLevel < Level){
        while (LTemp != NULL)
        {
            if (rand() % 2){
                LList->Next[CurrLevel]=LTemp;
                LList=LTemp;
            }
            LTemp=LTemp->Next[CurrLevel-1];
        }
        LList->Next[CurrLevel]=NULL;
        CurrLevel += 1;
        LTemp=(*Slist)->Header;
    }
    STemp->CurrLevel=CurrLevel;
    return;
}


void SLPrint(SkipList * Slist)
{
    int MaxLevel=Slist->CurrLevel;
    
    for (int i = 0; i < MaxLevel; i++){
        LLPrint(Slist->Header, i);
    }
    return;
}