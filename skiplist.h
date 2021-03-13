# include "linkedlist.h"

/* Struct that implements a SkipList.
 * 
 * Level: Current level of skip list
 * Header: A pointer at the LinkedList Header.
 *
*/
typedef struct skiplist{
    int CurrLevel;
    LinkedList * Header;
}SkipList;

SkipList * SLInit(int);

void SLInsert(SkipList * Slist);

void SLInsertHelper(SkipList ** Slist);

void SLPrint(SkipList * Slist);

LinkedList * SLSearch(SkipList * Slist, KeyType Id);

void SLDestroy(SkipList ** SList);