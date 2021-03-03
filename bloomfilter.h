# include "skiplist.h"

/* bloom is a struct that is used for a bloom filter
 * It keeps the number of bits that you want it to have and a array of char.
 * 
 * 
*/
typedef struct bloomfilter{
    int NumofBytes;
    char * bits;
}bloom;


/*Initialize a new bloom filter
 *
 * NumofBits: Number of bits that you want it to have.
 * 
*/
bloom bloomInit(int NumofBits);


void bloomSetBit(bloom * bloom, char * Id);

int bloomBitExist(bloom * bloom, char * Id);

unsigned long djb2(unsigned char *str);

unsigned long sdbm(unsigned char *str);

unsigned long hash_i(unsigned char *str, unsigned int i);