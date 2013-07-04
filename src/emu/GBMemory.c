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

GBMemoryAddress const GBMemoryAddressRomBank0Start = 0x0000;
GBMemoryAddress const GBMemoryAddressRomBank0End = 0x3FFF;

GBMemoryAddress const GBMemoryAddressRomBankSwitchableStart = 0x4000;
GBMemoryAddress const GBMemoryAddressRomBankSwitchableEnd = 0x7FFF;

GBMemoryAddress const GBMemoryAddressVideoRamStart = 0x8000;
GBMemoryAddress const GBMemoryAddressVideoRamEnd = 0x9FFF;

GBMemoryAddress const GBMemoryAddressSwitchableRamBankStart = 0xA000;
GBMemoryAddress const GBMemoryAddressSwitchableRamBankEnd = 0xBFFF;

GBMemoryAddress const GBMemoryAddressInternalRAM0Start = 0xC000;
GBMemoryAddress const GBMemoryAddressInternalRAM0End = 0xDFFF;

GBMemoryAddress const GBMemoryAddressInternalRAMEchoStart = 0xE000;
GBMemoryAddress const GBMemoryAddressInternalRAMEchoEnd = 0xFDFF;

GBMemoryAddress const GBMemoryAddressOAMStart = 0xFE00;
GBMemoryAddress const GBMemoryAddressOAMEnd = 0xFE9F;

GBMemoryAddress const GBMemoryAddressIOPortsStart = 0xFF00;
GBMemoryAddress const GBMemoryAddressIOPortsEnd = 0xFF4B;

GBMemoryAddress const GBMemoryAddressInternalRAM1Start = 0xFF80;
GBMemoryAddress const GBMemoryAddressInternalRAM1End = 0xFFFE;

GBMemoryAddress const GBMemoryAddressInterruptEnableRegister = 0xFFFF;

struct {
    GBMemoryWord *data;
    int16_t dataLength;
    GBMemoryMode memoryMode;
}GBMemory;

void GBMemory_setData(const GBMemoryWord *data, uint16_t dataLength, GBMemoryMode memoryMode)
{
    GBMemory.memoryMode = memoryMode;
    GBMemory.dataLength = dataLength;
    
    GBMemory.data = calloc(dataLength, sizeof(GBMemoryWord));
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

GBMemoryWord GBMemory_getWordAt(GBMemoryAddress address)
{
    GBMemoryWord result = GBMemory.data[address];
    return result;
}

GBMemoryDWord GBMemory_getDwordAt(GBMemoryAddress address)
{
    GBMemoryWord w1 = GBMemory_getWordAt(address);
    GBMemoryWord w2 = GBMemory_getWordAt(address + 1);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemoryDWord result = DWORD_FROM_HL(w1, w2);
    
    return result;
}

void GBMemory_writeWordAt(GBMemoryAddress address, GBMemoryWord value)
{
    GBMemory.data[address] = value;
}

void GBMemory_writeDwordAt(GBMemoryAddress address, GBMemoryDWord value)
{
    GBMemoryWord w1, w2;
    HL_FROM_DWORD(value, &w1, &w2);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemory_writeWordAt(address, w1);
    GBMemory_writeWordAt(address + 1, w2);
}
