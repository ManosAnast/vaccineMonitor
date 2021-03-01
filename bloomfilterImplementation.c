# include "bloomfilter.h"

bloom bloomInit(int NumOfBits)
{
    bloom filter;
    filter.NumofBits=NumOfBits; filter.bits=(char *)calloc(NumOfBits, sizeof(char));
    return filter;
}

void bloomSetBit(bloom * bloom, char * Id)
{   
    int num1, num2, num3;
    num1=djb2(Id)%(BloomNum*8); num2=sdbm(Id)%(BloomNum*8); num3=hash_i(Id, 3)%(BloomNum*8);
    if (bloomBitExist(bloom, num1) && bloomBitExist(bloom, num2) && bloomBitExist(bloom, num3)){// If the bits that we want to change are already 1 return
        return;
    }
    /*Set the bit that djb2 returned*/
    int Byte=num1/8, x=1;
    int N=num1 - 8*Byte - 1;
    int Number=bloom->bits[Byte];
    Number ^= (-x ^ Number) & (1UL << N);
    bloom->bits[Byte]=Number;
    
    /*Set the bit that sdbm returned*/
    Byte=num2/8; N=num2 - 8*Byte - 1; Number=bloom->bits[Byte];
    Number ^= (-x ^ Number) & (1UL << N);
    bloom->bits[Byte]=Number;
    
    /*Set the bit that hash_i returned*/
    Byte=num3/8; N=num3 - 8*Byte - 1; Number=bloom->bits[Byte];
    Number ^= (-x ^ Number) & (1UL << N);
    bloom->bits[Byte]=Number;
    return;
}

int bloomBitExist(bloom * bloom, int Num)
{
    int Byte=Num/8;
    int N=Num - 8*Byte - 1;
    int Number=bloom->bits[Byte];
    int bit=(Number >> N) & 1U;
    return bit;
}

/*
This algorithm (k=33) was first reported by dan bernstein many years 
ago in comp.lang.c. 
The magic of number 33 (why it works better than many other constants, 
prime or not) has never been adequately explained.
*/
unsigned long djb2(unsigned char *str) 
{
	unsigned long hash = 5381;
	int c; 
	while (c = *str++) {
		hash = ((hash << 5) + hash) + c; /* hash * 33 + c */
	}
	return hash;
}


/*
This algorithm was created for sdbm (a public-domain reimplementation of ndbm) 
database library. it was found to do well in scrambling bits, causing better 
distribution of the keys and fewer splits. it also happens to be a good 
general hashing function with good distribution. The actual function 
is hash(i) = hash(i - 1) * 65599 + str[i]; what is included below 
is the faster version used in gawk. There is even a faster, duff-device 
version. The magic constant 65599 was picked out of thin air while experimenting 
with different constants, and turns out to be a prime. this is one of the 
algorithms used in berkeley db (see sleepycat) and elsewhere.
*/
unsigned long sdbm(unsigned char *str) 
{
	unsigned long hash = 0;
	int c;

	while (c = *str++) {
		hash = c + (hash << 6) + (hash << 16) - hash;
	}

	return hash;
}


/* 
Return the result of the Kth hash funcation. This function uses djb2 and sdbm.
None of the functions used here is strong for cryptography purposes but they
are good enough for the purpose of the class.

The approach in this function is based on the paper:
https://www.eecs.harvard.edu/~michaelm/postscripts/rsa2008.pdf
*/
unsigned long hash_i(unsigned char *str, unsigned int i) 
{
	return djb2(str) + i*sdbm(str) + i*i;
}


