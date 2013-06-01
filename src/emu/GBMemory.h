//
//  GBMemory.h
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMemory_h
#define GBEmu_GBMemory_h

uint8_t getByteAt(uint16_t address);
uint16_t getWordAt(uint16_t address);

void writeByteAt(uint16_t address, uint8_t value);
void writeWordAt(uint16_t address, uint16_t value);

#endif
