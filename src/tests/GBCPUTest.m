//
//  GBACPUTest.m
//  GBEmu
//
//  Created by Jesús on 16/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBCPUTest.h"
#import "GBMemory.h"
#import "GBCPU.h"

@interface GBCPUTest ()

- (int8_t)wordForIndex:(int)index;

@end

@implementation GBCPUTest

- (void)setUpClass
{
    
}

- (void)tearDownClass
{
    
}

- (void)setUp
{
    GBCPU_setUp();
}

- (void)tearDown
{
    GBCPU_shutDown();
}


- (void)testLoadInstructions
{
    int nDataLength = 100;
    int8_t dataLoad[nDataLength];
    
    //Operaciones de carga directas R <- n
    int nLoadCommands = 6;
    int8_t loadCommands[] = {
        0x06, 0x0E, 0x16, 0x1E, 0x26, 0x2E
    };
    for (int i = 0; i < nLoadCommands; i++) {
        dataLoad[2 * i] = loadCommands[i];
        dataLoad[2 * i + 1] = [self wordForIndex:i];
    }
    
    GBMemory_setData(dataLoad, nDataLength, GBMemoryModeBigEndian);
    for (int i = 0; i < nLoadCommands; i++) {
        GBCPU_nextOperation();
    }
    
    GHAssertTrue(REG_B == [self wordForIndex:0], @"Data not loaded in REG_B");
    GHAssertTrue(REG_C == [self wordForIndex:1], @"Data not loaded in REG_C");
    GHAssertTrue(REG_D == [self wordForIndex:2], @"Data not loaded in REG_D");
    GHAssertTrue(REG_E == [self wordForIndex:3], @"Data not loaded in REG_E");
    GHAssertTrue(REG_H == [self wordForIndex:4], @"Data not loaded in REG_H");
    GHAssertTrue(REG_L == [self wordForIndex:5], @"Data not loaded in REG_L");
    
    //Operaciones de carga indirectas R <- (HL)
    
    GBMemory_freeData();
}


#pragma mark Private

- (int8_t)wordForIndex:(int)index
{
    return (int8_t)(index % 10 + index);
}

@end
