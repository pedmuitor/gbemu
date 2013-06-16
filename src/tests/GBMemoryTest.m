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
    int8_t dataLoad[100];
    for (int i = 0; i < 100; i++) {
        dataLoad[i] = [self wordForIndex:i];
    }
    const int8_t * data = dataLoad;
    GBMemory_setData(data, self.dataLoadLength, GBMemoryModeBigEndian);
}

- (void)tearDown
{
    GBMemory_freeData();
}

- (void)testReadWord
{
    //Big endian
    GBMemory_setMemoryMode(GBMemoryModeBigEndian);
    for (int i = 0; i < self.dataLoadLength; i++) {
        int8_t word = GBMemory_getWordAt((int16_t)i);
        GHAssertTrue(word == [self wordForIndex:i], @"Stored word is incorrect");
    }
    
    //Little endian
    GBMemory_setMemoryMode(GBMemoryModeLittleEndian);
    for (int i = 0; i < self.dataLoadLength; i++) {
        int8_t word = GBMemory_getWordAt((int16_t)i);
        GHAssertTrue(word == [self wordForIndex:i], @"Stored word is incorrect");
    }
}

- (void)testReadDWord
{
    //Big endian
    GBMemory_setMemoryMode(GBMemoryModeBigEndian);
    for (int i = 0; i < self.dataLoadLength / 2; i+= 2) {
        int16_t dword = GBMemory_getDwordAt((int16_t)i);
        GHAssertTrue(dword == [self dwordForIndex:i memoryMode:GBMemory_memoryMode()], @"Stored dword in incorrect");
    }
    
    //Little endian
    GBMemory_setMemoryMode(GBMemoryModeLittleEndian);
    for (int i = 0; i < self.dataLoadLength / 2; i+= 2) {
        int16_t dword = GBMemory_getDwordAt((int16_t)i);
        GHAssertTrue(dword == [self dwordForIndex:i memoryMode:GBMemory_memoryMode()], @"Stored dword in incorrect");
    }
}



#pragma mark Private

- (int8_t)wordForIndex:(int)index
{
    return (int8_t)(index % 10 + index);
}

- (int16_t)dwordForIndex:(int)index memoryMode:(GBMemoryMode)memoryMode
{
    int8_t l = [self wordForIndex:index];
    int8_t h = [self wordForIndex:index + 1];
    
    if (memoryMode == GBMemoryModeLittleEndian) {
        SWAP_XY(&h, &l);
    }
    
    return DWORD_FROM_HL(h, l);
}


@end
