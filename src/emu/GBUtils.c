//
//  GBUtils.c
//  GBEmu
//
//  Created by Pedro on 12/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <math.h>

uint8_t bitAtIndex (int n, int index)
{
	int mask = (int)pow(2, index);
    uint8_t result = (n & mask) >> (index);
    return result;
}

void setBitAtIndex (int8_t *r, int index, uint8_t value)
{
    uint8_t mask = ~((int8_t)pow(2, index));
    *r &= mask;
    
    if (value) {
        *r |= (0x01) << index;
    }
    
    *r &= 0xFF;
}

uint8_t moreSignificantBit (int n, int size)
{
	int sizeInBits	= size*8;
	int bit 		= sizeInBits - 1;
    
	return bitAtIndex(n, bit);
}

uint8_t lessSignificantBit (int n)
{
    return bitAtIndex(n, 0);
}
