//
//  GBMemory.c
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>

#import "GBMacros.h"
#import "GBCPU.h"
#import "GBMemory.h"

int8_t getByteAt(int16_t address)
{
    //TODO: return byte at address
    return 0;
}

int16_t getWordAt(int16_t address)
{
    //TODO: big-low endian
    int8_t l = getByteAt(address);
    int8_t h = getByteAt(address + 1);
    
    int16_t result = DWORD_FROM_HL(h, l);
    
    return result;
}

void writeByteAt(int16_t address, int8_t value)
{
    //TODO: write byte at address
}

void writeWordAt(int16_t address, int16_t value)
{
    //TODO: write word at address
}