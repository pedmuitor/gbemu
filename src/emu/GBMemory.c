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
#include "GBRom.h"
#include "GBUtils.h"

GBMemoryRange const GBMemoryAddressRomBank0 = {.start = 0x0000, .end = 0x3FFF};
GBMemoryRange const GBMemoryAddressRomBankSwitchable = {.start = 0x4000, .end = 0x7FFF};
GBMemoryRange const GBMemoryAddressVideoRam = {.start = 0x8000, .end = 0x9FFF};
GBMemoryRange const GBMemoryAddressSwitchableRamBank = {.start = 0xA000, .end = 0xBFFF};
GBMemoryRange const GBMemoryAddressInternalRAM = {.start = 0xC000, .end = 0xDFFF};
GBMemoryRange const GBMemoryAddressInternalRAMEcho = {.start = 0xE000, .end = 0xFDFF};
GBMemoryRange const GBMemoryAddressOAMStart = {.start = 0xFE00, .end = 0xFE9F};
GBMemoryRange const GBMemoryAddressIOPorts = {.start = 0xFF00, .end = 0xFF4B};
GBMemoryRange const GBMemoryAddressInternalRAM1 = {.start = 0xFF80, .end = 0xFF4B};
GBMemoryRange const GBMemoryAddressInterruptEnableRegister = {.start = 0xFFFF, .end = 0xFFFF};

GBMemoryRange GBMemoryRangeMake(GBMemoryAddress start, GBMemoryAddress end){
    GBMemoryRange result = {.start = start, .end = end};
    return result;
}

bool GBMemoryRangeContains(GBMemoryRange range, GBMemoryAddress address){
    return (address >= range.start) && (address <= range.end);
}

struct {
    GBMemoryWord *data;
    int16_t dataLength;
    GBMemoryMode memoryMode;
    bool romMemory;
}GBMemory;


bool _GBMemoryIsRomAddress(GBMemoryAddress address)
{
    bool result = GBMemoryRangeContains(GBMemoryAddressRomBank0, address);
    result |= GBMemoryRangeContains(GBMemoryAddressRomBankSwitchable, address);
    return result;
}


void GBMemorySetData(const GBMemoryWord *data, uint16_t dataLength, GBMemoryMode memoryMode)
{
    GBMemory.memoryMode = memoryMode;
    GBMemory.dataLength = dataLength;
    GBMemory.data = calloc(dataLength, sizeof(GBMemoryWord));
    GBMemory.romMemory = false;
    memcpy(GBMemory.data, data, dataLength);
}

void GBMemoryFreeData()
{
    free(GBMemory.data);
    GBMemory.dataLength = -1;
}

void GBMemorySetMemoryMode(GBMemoryMode memoryMode)
{
    GBMemory.memoryMode = memoryMode;
}

GBMemoryMode GBMemoryMemoryMode()
{
    return GBMemory.memoryMode;
}

void GBMemorySetRomMemoryEnabled(bool enabled)
{
    GBMemory.romMemory = enabled;
}

bool GBMemoryRomMemoryEnabled()
{
    return GBMemory.romMemory;
}

GBMemoryWord GBMemoryGetWordAt(GBMemoryAddress address)
{
    GBMemoryWord result;
    if (GBMemory.romMemory && _GBMemoryIsRomAddress(address)) {
        GBMemoryAddress romAddress = address;
        if (GBMemoryRangeContains(GBMemoryAddressRomBank0, address)) {
            result = GBRomReadWord(romAddress);
        } else {
            //TODO: switchable ram bank, add offset to address
            result = 0x00;
        }
    } else {
        result = GBMemory.data[address];
    }
    
    
    return result;
}

GBMemoryDWord GBMemoryGetDwordAt(GBMemoryAddress address)
{
    GBMemoryWord w1 = GBMemoryGetWordAt(address);
    GBMemoryWord w2 = GBMemoryGetWordAt(address + 1);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemoryDWord result = DWORD_FROM_HL(w1, w2);
    
    return result;
}

void GBMemoryWriteWordAt(GBMemoryAddress address, GBMemoryWord value)
{
    if (GBMemory.romMemory && _GBMemoryIsRomAddress(address)) {
        //TODO: nothing here, trying to write on rom address
    } else {
        GBMemory.data[address] = value;
    }
}

void GBMemoryWriteDwordAt(GBMemoryAddress address, GBMemoryDWord value)
{
    GBMemoryWord w1, w2;
    HL_FROM_DWORD(value, &w1, &w2);
    if (GBMemory.memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    GBMemoryWriteWordAt(address, w1);
    GBMemoryWriteWordAt(address + 1, w2);
}
