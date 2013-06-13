//
//  GBMemory.h
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMemory_h
#define GBEmu_GBMemory_h

int8_t GBMemory_getWordAt(int16_t address);
int16_t GBMemory_getDwordAt(int16_t address);

void GBMemory_writeWordAt(int16_t address, int8_t value);
void GBMemory_writeDwordAt(int16_t address, int16_t value);

#endif
