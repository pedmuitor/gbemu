//
//  GBRom.h
//  GBEmu
//
//  Created by Jesús on 05/07/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBRom_h
#define GBEmu_GBRom_h

#import <stdbool.h>
#import "GBMemory.h"

bool GBRomLoad(const char* romName);
bool GBRomRelease();

void GBRomSetMemoryMode(GBMemoryMode memoryMode);

GBMemoryWord GBRomReadWord(GBMemoryAddress address);
GBMemoryDWord GBRomReaDWord(GBMemoryAddress address);


#endif
