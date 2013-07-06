//
//  GBMemory.h
//  GBEmu
//
//  Created by Jesús on 01/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMemory_h
#define GBEmu_GBMemory_h

#import <stdint.h>
#import <stdbool.h>

typedef int16_t GBMemoryAddress;
typedef int8_t GBMemoryWord;
typedef int16_t GBMemoryDWord;

typedef enum {
    GBMemoryModeLittleEndian,   //Most significative byte last
    GBMemoryModeBigEndian       //Most significative byte first
}GBMemoryMode;

struct GBMemoryRange {
    GBMemoryAddress start;
    GBMemoryAddress end;
};

/*
 * GBMemoryRange
 */

typedef struct GBMemoryRange GBMemoryRange;

extern GBMemoryRange const GBMemoryAddressRomBank0;
extern GBMemoryRange const GBMemoryAddressRomBankSwitchable;
extern GBMemoryRange const GBMemoryAddressRomBankSwitchable;
extern GBMemoryRange const GBMemoryAddressVideoRam;
extern GBMemoryRange const GBMemoryAddressSwitchableRamBank;
extern GBMemoryRange const GBMemoryAddressInternalRAM;
extern GBMemoryRange const GBMemoryAddressInternalRAMEcho;
extern GBMemoryRange const GBMemoryAddressOAMStart;
extern GBMemoryRange const GBMemoryAddressIOPorts;
extern GBMemoryRange const GBMemoryAddressInternalRAM1;
extern GBMemoryRange const GBMemoryAddressInterruptEnableRegister;

GBMemoryRange GBMemoryRangeMake(GBMemoryAddress start, GBMemoryAddress end);
bool GBMemoryRangeContains(GBMemoryRange range, GBMemoryAddress address);

/*
 * GBMemory
 */

void GBMemorySetData(const GBMemoryWord *data, uint16_t dataLength, GBMemoryMode memoryMode);
void GBMemoryFreeData();

void GBMemorySetMemoryMode(GBMemoryMode memoryMode);
GBMemoryMode GBMemoryMemoryMode();

void GBMemorySetRomMemoryEnabled(bool enabled);
bool GBMemoryRomMemoryEnabled();

GBMemoryWord GBMemoryGetWordAt(GBMemoryAddress address);
GBMemoryDWord GBMemoryGetDwordAt(GBMemoryAddress address);

void GBMemoryWriteWordAt(GBMemoryAddress address, GBMemoryWord value);
void GBMemoryWriteDwordAt(GBMemoryAddress address, GBMemoryDWord value);

#endif
