//
//  GBRom.c
//  GBEmu
//
//  Created by Jesús on 05/07/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdio.h>
#include "GBRom.h"
#include "GBUtils.h"

struct {
    GBMemoryMode memoryMode;
    FILE *romFile;
}GBMemoryRomData;

bool GBRomLoad(const char* romName)
{
    GBRomRelease();
    GBMemoryRomData.romFile = fopen(romName, "r");
    
    bool result = GBMemoryRomData.romFile != NULL;
    if (result) {
        GBMemorySetRomMemoryEnabled(true);
    }
    return result;
}

bool GBRomRelease()
{
    if (GBMemoryRomData.romFile != NULL) {
        fclose(GBMemoryRomData.romFile);
        GBMemorySetRomMemoryEnabled(false);
        GBMemoryRomData.romFile = NULL;
    }
    return GBMemoryRomData.romFile == NULL;
}

void GBRomSetMemoryMode(GBMemoryMode memoryMode)
{
    GBMemoryRomData.memoryMode = memoryMode;
}

GBMemoryWord GBRomReadWord(GBMemoryAddress address)
{
    GBMemoryWord result = 0;
    fseek(GBMemoryRomData.romFile, address, SEEK_SET);
    fread(&result, sizeof(GBMemoryWord), 1, GBMemoryRomData.romFile);
    return result;
}

GBMemoryDWord GBRomReaDWord(GBMemoryAddress address)
{
    GBMemoryWord w1 = GBRomReadWord(address);
    GBMemoryWord w2 = GBRomReadWord(address + 1);
    if (GBMemoryRomData.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemoryDWord result = DWORD_FROM_HL(w1, w2);
    return result;
}


