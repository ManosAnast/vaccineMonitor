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
    if(Slist!=NULL){
        Slist->CurrLevel=Log( Slist->Header->Id * (-1) );
        Slist->Header->Id=-1;
        SLInsertHelper(&Slist);
    }
    return;
}


void SLInsertHelper(SkipList ** Slist)
{
    SkipList * STemp= *Slist;
    LinkedList * LTemp= STemp->Header;
    LinkedList * LList= STemp->Header;
    srand(time(NULL));   // Initialize for "toss a coin" operation.
    int r = rand();
    int CurrLevel=1;
    int level=STemp->CurrLevel;
    while (CurrLevel < level){
        while (LTemp != NULL)
        {
            if (rand() % 2){
                LList->Next=(LinkedList **)realloc(LList->Next, (CurrLevel+1)*sizeof(LinkedList *));
                LList->Next[CurrLevel]=NULL;
                LList->Next[CurrLevel]=LTemp;
                LList=LList->Next[CurrLevel];
            }
            LTemp=LTemp->Next[CurrLevel-1]; 
        }
        LList->Next=(LinkedList **)realloc(LList->Next, (CurrLevel+1)*sizeof(LinkedList *));
        LList->Next[CurrLevel]=NULL;
        CurrLevel += 1;
        LTemp=STemp->Header;
        LList=LTemp;
    }
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

void SLDelete(SkipList ** Slist, int Id)
{
    int MaxLevel=(*Slist)->CurrLevel;
    LinkedList * Temp=(*Slist)->Header, * Previous;
    LinkedList * Keeper=SLSearch((*Slist), Id);

    for (int i = MaxLevel-1; i >= 0; i--){
        while (Temp->Next[i] != NULL && Temp->Id < Id){
            Previous = Temp;
            Temp=Temp->Next[i];
        }
        if (Temp->Id == Id){
            Previous->Next[i]=Temp->Next[i];
        } 
        Temp=(*Slist)->Header;
    }
    free(Keeper->Next);
    free(Keeper);
    return;
}

void SLPrint(SkipList * Slist)
{
    if(Slist!= NULL){
        int MaxLevel=Slist->CurrLevel;
        
        for (int i = 0; i < MaxLevel; i++){
            LLPrint(Slist->Header, i);
        }
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

unsigned int Log(unsigned int n) 
{ 
    return (n > 1) ? 1 + Log(n / 2) : 0; 
} 