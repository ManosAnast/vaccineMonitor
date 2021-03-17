# include "linkedlist.h"

LinkedList * LLInit()
{
    LinkedList * New=(LinkedList *)malloc(sizeof(LinkedList));
    New->Id=0; New->Next=(LinkedList **)calloc(Level, sizeof(LinkedList *));
    return New;
}


void LLInsert(LinkedList * List, KeyType Key, int CurrLevel)
{
    LLInsertHelper(&List, Key, CurrLevel);
    return;
}


void LLInsertHelper(LinkedList ** List, KeyType Key, int CurrLevel)
{
    LinkedList * Temp= *List, * Previous, * NewNode;
    Temp->Id -= 1;
    while (Temp->Next[CurrLevel] != NULL && Temp->Id < Key){
        Previous = Temp;
        Temp=Temp->Next[CurrLevel];
    }
    /*Make a new node*/
    NewNode=(LinkedList *)calloc(1, sizeof(LinkedList));
    NewNode->Next=(LinkedList **)calloc(Level, sizeof(LinkedList *));
    NewNode->Id=Key;

    /*Connect the new node to the correct position*/
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

void LLPrint(LinkedList * List, int Level)
{
    LinkedList * Temp=List;
    while (Temp != NULL){
        printf("%d",Temp->Id);
        Temp=Temp->Next[Level];
        if (Temp != NULL){
            printf(" -> ");
        }
    }
    printf("\n");
    return;
}

void LLDestroy(LinkedList ** List)
{
    LinkedList * Current=*List, *Next;
    while (Current!= NULL){
        Next=Current->Next[0];
        free(Current->Next);
        free(Current);
        Current=Next;
    }
    return;
}