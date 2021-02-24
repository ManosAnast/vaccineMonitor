# include "skiplist.h"

LinkedList * LLInit()
{
    LinkedList * New=(LinkedList *)malloc(sizeof(LinkedList));
    New->Id=-1; New->Next=(LinkedList **)calloc(Level, sizeof(LinkedList *));
    return New;
}

void LLInsert(LinkedList * List, KeyType Key, int CurrLevel)
{
    if(List == NULL){
        List=(LinkedList *) calloc(1,sizeof(LinkedList));
        List->Next=(LinkedList **) calloc(Level, sizeof(LinkedList *));
        List->Id=-1; List=List->Next[0];
        List=(LinkedList *) calloc(1,sizeof(LinkedList));
        List->Next[0]=NULL;
    }
    LLInsertHelper(&List, Key, CurrLevel);
    return;
}


void LLInsertHelper(LinkedList ** List, KeyType Key, int CurrLevel)
{
    LinkedList * Temp= *List, * Previous, * NewNode;
    while (Temp->Next[CurrLevel] != NULL && Temp->Id < Key){
        Previous = Temp;
        Temp=Temp->Next[CurrLevel];
    }
    /*Make a new node*/
    NewNode=(LinkedList *)calloc(1,sizeof(LinkedList));
    if (Level == 0){
        NewNode->Next=(LinkedList **) calloc(Level, sizeof(LinkedList *));
    }
    NewNode->Id=Key;

    if(Temp->Next[CurrLevel] == NULL && Temp->Id < Key){
        NewNode->Next[CurrLevel]=NULL;
        Temp->Next[CurrLevel]=NewNode;
    }
    else if (Temp->Id > Key){        
        Previous->Next[CurrLevel]=NewNode;
        NewNode->Next[CurrLevel]=Temp;
    }
    return;
}
