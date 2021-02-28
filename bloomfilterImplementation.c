# include "bloomfilter.h"

bloom bloomInit(int NumOfBits)
{
    bloom filter;
    filter.NumofBits=NumOfBits; filter.bits=(char *)calloc(NumOfBits, sizeof(char));
    return filter;
}

void bloomSetBit(bloom * bloom, int Num)
{   
    if (bloomBitExist(bloom, Num)){
        return;
    }
    int Byte=Num/8, x=1;
    int N=Num - 8*Byte - 1;
    int Number=bloom->bits[Byte];
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