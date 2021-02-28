# include "hash.h"
# define KeyType int


/* Struct that implements a LinkedList.
 * 
 * Id: HashId that is used to find the citizen and hers/his informations.
 * Next: Array of pointers that "shows" to the next populated node.
 *
*/
typedef struct node{
    KeyType Id;
    struct node ** Next;
}LinkedList;

LinkedList * LLInit();

void LLInsert(LinkedList * List, KeyType Key, int Level);

void LLInsertHelper(LinkedList **, KeyType Key, int Level);

void LLDelete(LinkedList *, KeyType Key);

void LLPrint(LinkedList * List);