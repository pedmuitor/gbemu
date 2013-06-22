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
#import "GBUtils.h"

@interface GBCPUTest ()

- (void)loadTestDataInMemory:(int8_t *)testData length:(int)testDataLength;
- (void)resetGBCPU_PC;


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


- (void)testLoadDirect
{
    //R <- n
    int instructions = 6;
    int nTestData = 12;
    int8_t testData[] = {
        0x06, 0x0B,
        0x0E, 0x0C,
        0x16, 0x0D,
        0x1E, 0x0E,
        0x26, 0x01,
        0x2E, 0x02
    };
    [self loadTestDataInMemory:testData length:nTestData];
    
    for (int i = 0; i < instructions; i++) {
        GBCPU_nextOperation();
    }
    
    GHAssertTrue(REG_B == 0x0B, @"Data not loaded in REG_B");
    GHAssertTrue(REG_C == 0x0C, @"Data not loaded in REG_C");
    GHAssertTrue(REG_D == 0x0D, @"Data not loaded in REG_D");
    GHAssertTrue(REG_E == 0x0E, @"Data not loaded in REG_E");
    GHAssertTrue(REG_H == 0x01, @"Data not loaded in REG_H");
    GHAssertTrue(REG_L == 0x02, @"Data not loaded in REG_L");
}

- (void)testLoadRegister {
    
    //R1 <- R2
    int nDestRegisters = 2;
    int nInstructions = 7;
    int8_t * destRegisters[] = {
      &REG_A, &REG_B, &REG_C, &REG_D, &REG_E, &REG_H, &REG_L
    };
    int8_t testDataLoad[7][7] = {
        //A
        {0x78, 0x79, 0x7A, 0x7B, 0x7C, 0x7D, 0x7E},
        //B
        {0x40, 0x41, 0x42, 0x43, 0x44, 0x45, 0x46},
        //C
        {0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E},
        //D
        {0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56},
        //E
        {0x58, 0x59, 0x5A, 0x5B, 0x5C, 0x5D, 0x5E},
        //H
        {0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66},
        //L
        {0x68, 0x69, 0x6A, 0x6B, 0x6C, 0x6D, 0x6E},
    };
    
    for (int i = 0; i < nDestRegisters; i++) {
        int8_t * destRegister = destRegisters[i];
        
        [self loadTestDataInMemory:testDataLoad[i] length:nInstructions];
        [self setDefaultRegistersValues];
        
        int regB = REG_B;
        int regC = REG_C;
        int regD = REG_D;
        int regE = REG_E;
        int regH = REG_H;
        int regL = REG_L;
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regB, @"Register must have B value");
        GHAssertTrue(REG_B == regB, @"Register must have its value");
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regC, @"Register must have C value");
        GHAssertTrue(REG_C == regC, @"Register must have his value");
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regD, @"Register must have D value");
        GHAssertTrue(REG_D == regD, @"Register must have his value");
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regE, @"Register must have E value");
        GHAssertTrue(REG_E == regE, @"Register must have his value");
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regH, @"Register must have H value");
        GHAssertTrue(REG_H == regH, @"Register must have his value");
        
        GBCPU_nextOperation();
        GHAssertTrue(*destRegister == regL, @"Register must have L value");
        GHAssertTrue(REG_L == regL, @"Register must have his value");
        
        [self setDefaultRegistersValues];
        
        GBCPU_nextOperation();
        int16_t hlAddress = DWORD_FROM_HL(REG_H, REG_L);
        int8_t byteAtHL = GBMemory_getWordAt(hlAddress);
        GHAssertTrue(byteAtHL == testDataLoad[i][hlAddress], @"Byte at (HL) needs to be equal to 0x0C");
        GHAssertTrue(*destRegister == byteAtHL, @"Register must have (HL) value");
        GHAssertTrue(REG_H == regH, @"Register must have his value");
        GHAssertTrue(REG_L == regL, @"Register must have his value");
    }
    
    
    
    
}


#pragma mark Private

- (void)loadTestDataInMemory:(int8_t *)testData length:(int)testDataLength
{
    int nDataLength = 100;
    int8_t dataLoad[nDataLength];
    
    for (int i = 0; i < nDataLength; i++) {
        dataLoad[i] = 0x00;
    }
    
    for (int i = 0; i < testDataLength; i++) {
        dataLoad[i] = testData[i];
    }
    GBMemory_setData(dataLoad, nDataLength, GBMemoryModeBigEndian);
    [self resetGBCPU_PC];
}

- (void)setDefaultRegistersValues
{
    REG_A = 0x0A;
    REG_B = 0x0B;
    REG_C = 0x0C;
    REG_D = 0x0D;
    REG_E = 0x0E;
    REG_H = 0x00;
    REG_L = 0x02;
}

- (void)resetGBCPU_PC
{
    REG_PC = 0;
}

@end
