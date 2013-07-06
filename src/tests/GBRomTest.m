//
//  GBRomTest.m
//  GBEmu
//
//  Created by Jesús on 06/07/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBRomTest.h"
#import "GBMemory.h"
#import "GBRom.h"
#import "GBUtils.h"

@interface GBRomTest ()

@end

@implementation GBRomTest

- (void)setUp
{
    NSString *romPath = [[NSBundle mainBundle] pathForResource:@"rom_sample.txt" ofType:nil];
    GBRomLoad([romPath cStringUsingEncoding:NSUTF8StringEncoding]);
}

- (void)testOpenRom
{
    NSString *romPath = [[NSBundle mainBundle] pathForResource:@"rom_sample.txt" ofType:nil];
    bool result = GBRomLoad([romPath cStringUsingEncoding:NSUTF8StringEncoding]);
    GHAssertTrue(result == YES, @"Result must be true");
    GHAssertTrue(GBMemoryRomMemoryEnabled() == true, @"Memory rom enabled must be true");
}

- (void)testLoadWord
{
    int nRomBytes = 12;
    GBMemoryWord romBytes[14] = {0x72, 0x6F, 0x6D, 0x5F, 0x73, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74};
    
    for (GBMemoryAddress i = 0x0000; i < nRomBytes; i++) {
        GBMemoryWord romData = GBRomReadWord(i);
        GHAssertTrue(romData == romBytes[i], @"Rom data must be equal to rom bytes");
    }
}

- (void)testLoadDWord
{
    int nRomBytes = 12;
    GBMemoryWord romBytes[14] = {0x72, 0x6F, 0x6D, 0x5F, 0x73, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x2E, 0x74, 0x78, 0x74};
    
    //Little endian
    GBRomSetMemoryMode(GBMemoryModeLittleEndian);
    for (GBMemoryAddress i = 0x0000; i < nRomBytes / 2; i+= 2) {
        GBMemoryDWord romData = GBRomReaDWord(i);
        GHAssertTrue(romData == DWORD_FROM_HL(romBytes[i + 1], romBytes[i]), @"Rom data must be equal to rom bytes");
    }
    
    //Big endian
    GBRomSetMemoryMode(GBMemoryModeBigEndian);
    for (GBMemoryAddress i = 0x0000; i < nRomBytes / 2; i+= 2) {
        GBMemoryDWord romData = GBRomReaDWord(i);
        GHAssertTrue(romData == DWORD_FROM_HL(romBytes[i], romBytes[i + 1]), @"Rom data must be equal to rom bytes");
    }
}

- (void)testClose
{
    bool result = GBRomRelease();
    GHAssertTrue(result == YES, @"Close rom must return true");
    GHAssertTrue(GBMemoryRomMemoryEnabled() == false, @"Memory rom enabled must be false");
}

@end
