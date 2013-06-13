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

int8_t GBMemory_getWordAt(int16_t address)
{
    //TODO: return byte at address
    return 0;
}

int16_t GBMemory_getDwordAt(int16_t address)
{
    //TODO: big-low endian
    int8_t l = GBMemory_getWordAt(address);
    int8_t h = GBMemory_getWordAt(address + 1);
    
    int16_t result = DWORD_FROM_HL(h, l);
    
    return result;
}

void GBMemory_writeWordAt(int16_t address, int8_t value)
{
    //TODO: write byte at address
}

void GBMemory_writeDwordAt(int16_t address, int16_t value)
{
    //TODO: write word at address
}
