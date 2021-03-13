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
    printf("Level=%d\n", Level);
    while (CurrLevel < Level){
        while (LTemp != NULL)
        {
            if (rand() % 2){
                // LList->Next=(LinkedList **)realloc(LList->Next, (CurrLevel+1)*sizeof(LinkedList *));
                LList->Next[CurrLevel]=LTemp;
                LList=LTemp;
            }
            LTemp=LTemp->Next[CurrLevel-1];
        }
        // LList->Next=(LinkedList **)realloc(LList->Next, (CurrLevel+1)*sizeof(LinkedList *));
        LList->Next[CurrLevel]=NULL;
        CurrLevel += 1;
        LTemp=(*Slist)->Header;
    }
    STemp->CurrLevel=CurrLevel;
    return;
}


LinkedList * SLSearch(SkipList * Slist, KeyType Id)
{
    int MaxLevel=Slist->CurrLevel;
    LinkedList * Temp=Slist->Header;

    for (int i = MaxLevel-1; i >= 0; i--){
        while (Temp->Next[i] != NULL && Temp->Id < Id){
            Temp=Temp->Next[i];
        }
        if (Temp->Id == Id){
            return Temp;
        }
        if (Temp->Next[i] == NULL && i == 0 || Temp->Id > Id){
            return NULL;
        }
        
    }
    return NULL;
}


void SLPrint(SkipList * Slist)
{
    int MaxLevel=Slist->CurrLevel;
    
    for (int i = 0; i < MaxLevel; i++){
        LLPrint(Slist->Header, i);
    }
    return;
}

void SLDestroy(SkipList ** SList)
{
    if(*SList != NULL){
        LLDestroy(&(*SList)->Header);
        free(*SList);
    }
    return;
}