//
//  GBMemory.h
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMemory_h
#define GBEmu_GBMemory_h

int8_t getByteAt(int16_t address);
int16_t getWordAt(int16_t address);

void writeByteAt(int16_t address, int8_t value);
void writeWordAt(int16_t address, int16_t value);

#endif