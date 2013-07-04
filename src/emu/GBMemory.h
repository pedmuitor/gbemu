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
    GBMemoryModeLittleEndian,   //Most significative byte last
    GBMemoryModeBigEndian       //Most significative byte first
}GBMemoryMode;

typedef int16_t GBMemoryAddress;
typedef int8_t GBMemoryWord;
typedef int16_t GBMemoryDWord;

void GBMemory_setData(const GBMemoryWord *data, uint16_t dataLength, GBMemoryMode memoryMode);
void GBMemory_freeData();

void GBMemory_setMemoryMode(GBMemoryMode memoryMode);
GBMemoryMode GBMemory_memoryMode();


GBMemoryWord GBMemory_getWordAt(GBMemoryAddress address);
GBMemoryDWord GBMemory_getDwordAt(GBMemoryAddress address);

void GBMemory_writeWordAt(GBMemoryAddress address, GBMemoryWord value);
void GBMemory_writeDwordAt(GBMemoryAddress address, GBMemoryDWord value);

#endif
