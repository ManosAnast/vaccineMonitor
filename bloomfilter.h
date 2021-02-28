# include "skiplist.h"

/* bloom is a struct that is used for a bloom filter
 * It keeps the number of bits that you want it to have and a array of char.
 * 
 * 
*/
typedef struct bloomfilter{
    int NumofBits;
    char * bits;
}bloom;


/*Initialize a new bloom filter
 *
 * NumofBits: Number of bits that you want it to have.
 * 
*/
bloom bloomInit(int NumofBits);


void bloomSetBit(bloom * bloom, int Num);

int bloomBitExist(bloom * bloom, int Num);