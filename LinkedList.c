# include "skiplist.h"

void LLInsert(LinkedList * List, KeyType Key, int CurrLevel)
{
    if(List == NULL){
        List=(LinkedList *) calloc(1,sizeof(LinkedList));
        List->Next=(LinkedList **) calloc(Level, sizeof(LinkedList *));
        List->Id=Key ; List->Next[0]=NULL;
    }
    LLInsertHelper(&List, Key, CurrLevel);
    return;
}


void LLInsertHelper(LinkedList ** List, KeyType Key, int CurrLevel)
{
    LinkedList * Temp= *List;
    while (Temp->Next[CurrLevel] != NULL){
        Temp=Temp->Next[CurrLevel];
    }
    LinkedList * NewNode=(LinkedList *)calloc(1,sizeof(LinkedList));
    if (Level == 1){
        NewNode->Next=(LinkedList **) calloc(Level, sizeof(LinkedList *));
    }
    NewNode->Id=Key; NewNode->Next[CurrLevel]=NULL;
    Temp->Next[CurrLevel]=NewNode;
      
    return;
}


