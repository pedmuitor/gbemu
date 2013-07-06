//
//  GBMemoryTest.m
//  GBEmu
//
//  Created by Jesús on 16/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBMemory.h"
#import "GBMemoryTest.h"
#import "GBMemory.h"
#import "GBRom.h"
#import "GBUtils.h"

@interface GBMemoryTest ()

@property (nonatomic, assign) int16_t dataLoadLength;

- (int8_t)wordForIndex:(int)index;
- (int16_t)dwordForIndex:(int)index memoryMode:(GBMemoryMode)memoryMode;

@end

@implementation GBMemoryTest

- (void)setUpClass
{
    self.dataLoadLength = 100;
}

- (void)tearDownClass
{
    
}

- (void)setUp
{
    int8_t dataLoad[self.dataLoadLength];
    for (int i = 0; i < self.dataLoadLength; i++) {
        dataLoad[i] = [self wordForIndex:i];
    }
    const int8_t * data = dataLoad;
    GBMemorySetData(data, self.dataLoadLength, GBMemoryModeBigEndian);
}

- (void)tearDown
{
    GBMemoryFreeData();
}

- (void)testRomMemoryEnabled
{
    GBMemorySetRomMemoryEnabled(false);
    GHAssertTrue(GBMemoryRomMemoryEnabled() == false, @"Rom memory must be disabled");
    
    GBMemorySetRomMemoryEnabled(true);
    GHAssertTrue(GBMemoryRomMemoryEnabled() == true, @"Rom memory must be enabled");
}

- (void)testReadWord
{
    //Big endian
    GBMemorySetMemoryMode(GBMemoryModeBigEndian);
    for (int i = 0; i < self.dataLoadLength; i++) {
        int8_t word = GBMemoryGetWordAt((int16_t)i);
        GHAssertTrue(word == [self wordForIndex:i], @"Stored word is incorrect");
    }
    
    //Little endian
    GBMemorySetMemoryMode(GBMemoryModeLittleEndian);
    for (int i = 0; i < self.dataLoadLength; i++) {
        int8_t word = GBMemoryGetWordAt((int16_t)i);
        GHAssertTrue(word == [self wordForIndex:i], @"Stored word is incorrect");
    }
}

- (void)testReadDWord
{
    //Big endian
    GBMemorySetMemoryMode(GBMemoryModeBigEndian);
    for (int i = 0; i < self.dataLoadLength / 2; i+= 2) {
        int16_t dword = GBMemoryGetDwordAt((int16_t)i);
        GHAssertTrue(dword == [self dwordForIndex:i memoryMode:GBMemoryMemoryMode()], @"Stored dword in incorrect");
    }
    
    //Little endian
    GBMemorySetMemoryMode(GBMemoryModeLittleEndian);
    for (int i = 0; i < self.dataLoadLength / 2; i+= 2) {
        int16_t dword = GBMemoryGetDwordAt((int16_t)i);
        GHAssertTrue(dword == [self dwordForIndex:i memoryMode:GBMemoryMemoryMode()], @"Stored dword in incorrect");
    }
}


- (void)testLoadWordFromRom
{
    NSString *romPath = [[NSBundle mainBundle] pathForResource:@"rom_sample.txt" ofType:nil];
    GBRomLoad([romPath cStringUsingEncoding:NSUTF8StringEncoding]);
    
    int nRomBytes = 12;
    GBMemoryWord romBytes[14] = {0x72, 0x6F, 0x6D, 0x5F, 0x73, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74};
    
    //Bank0
    for (GBMemoryAddress i = 0x00; i < nRomBytes; i++) {
        GBMemoryWord romData = GBMemoryGetWordAt(i);
        GHAssertTrue(romData == romBytes[i], @"Reading from memory must be equals to the rom");
    }
    
    //TODO: switchableBank
}


- (void)testLoadDWordFromRom
{
    NSString *romPath = [[NSBundle mainBundle] pathForResource:@"rom_sample.txt" ofType:nil];
    GBRomLoad([romPath cStringUsingEncoding:NSUTF8StringEncoding]);
    
    int nRomBytes = 12;
    GBMemoryWord romBytes[14] = {0x72, 0x6F, 0x6D, 0x5F, 0x73, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74};
    
    //Little endian
    GBMemorySetMemoryMode(GBMemoryModeLittleEndian);
    for (GBMemoryAddress i = 0x0000; i < nRomBytes / 2; i+= 2) {
        GBMemoryDWord romData = GBMemoryGetDwordAt(i);
        GHAssertTrue(romData == DWORD_FROM_HL(romBytes[i + 1], romBytes[i]), @"Rom data must be equal to rom bytes");
    }
    
    //Big endian
    GBMemorySetMemoryMode(GBMemoryModeBigEndian);
    for (GBMemoryAddress i = 0x0000; i < nRomBytes / 2; i+= 2) {
        GBMemoryDWord romData = GBMemoryGetDwordAt(i);
        GHAssertTrue(romData == DWORD_FROM_HL(romBytes[i], romBytes[i + 1]), @"Rom data must be equal to rom bytes");
    }
}


//TODO: Write tests


#pragma mark Private

- (int8_t)wordForIndex:(int)index
{
    return (int8_t)(index % 10 + index);
}

- (int16_t)dwordForIndex:(int)index memoryMode:(GBMemoryMode)memoryMode
{
    int8_t w1 = [self wordForIndex:index];
    int8_t w2 = [self wordForIndex:index + 1];
    
    if (memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&w1, &w2);
    }
    
    return DWORD_FROM_HL(w1, w2);
}


@end
