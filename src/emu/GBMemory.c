//
//  GBMemory.c
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "GBCPU.h"
#include "GBMemory.h"
#include "GBUtils.h"

struct {
    int8_t *data;
    int16_t dataLength;
    GBMemoryMode memoryMode;
}GBMemory;

void GBMemory_setData(const int8_t *data, uint16_t dataLength, GBMemoryMode memoryMode)
{
    GBMemory.memoryMode = memoryMode;
    GBMemory.dataLength = dataLength;
    
    GBMemory.data = calloc(dataLength, sizeof(int8_t));
    memcpy(GBMemory.data, data, dataLength);
}

void GBMemory_freeData()
{
    free(GBMemory.data);
    GBMemory.dataLength = -1;
}

void GBMemory_setMemoryMode(GBMemoryMode memoryMode)
{
    GBMemory.memoryMode = memoryMode;
}

GBMemoryMode GBMemory_memoryMode()
{
    return GBMemory.memoryMode;
}


int8_t GBMemory_getWordAt(int16_t address)
{
    int8_t result = GBMemory.data[address];
    return result;
}

int16_t GBMemory_getDwordAt(int16_t address)
{
    int8_t w1 = GBMemory_getWordAt(address);
    int8_t w2 = GBMemory_getWordAt(address + 1);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    int16_t result = DWORD_FROM_HL(w1, w2);
    
    return result;
}

void GBMemory_writeWordAt(int16_t address, int8_t value)
{
    GBMemory.data[address] = value;
}

void GBMemory_writeDwordAt(int16_t address, int16_t value)
{
    int8_t w1, w2;
    HL_FROM_DWORD(value, &w1, &w2);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemory_writeWordAt(address, w1);
    GBMemory_writeWordAt(address + 1, w2);
}
