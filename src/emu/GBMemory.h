//
//  GBMemory.h
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMemory_h
#define GBEmu_GBMemory_h

typedef enum {
    GBMemoryModeLittleEndian,
    GBMemoryModeBigEndian
}GBMemoryMode;

void GBMemory_setData(const int8_t *data, uint16_t dataLength, GBMemoryMode memoryMode);
void GBMemory_freeData();

void GBMemory_setMemoryMode(GBMemoryMode memoryMode);
GBMemoryMode GBMemory_memoryMode();


int8_t GBMemory_getWordAt(int16_t address);
int16_t GBMemory_getDwordAt(int16_t address);

void GBMemory_writeWordAt(int16_t address, int8_t value);
void GBMemory_writeDwordAt(int16_t address, int16_t value);

#endif
