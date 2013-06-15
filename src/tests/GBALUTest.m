//
//  GBALUTest.m
//  GBEmu
//
//  Created by Pedro Muiños on 11/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBALUTest.h"

#include "GBCPU.h"
#include "GBCPU_ALU.h"
#include "GBUtils.h"

@implementation GBALUTest

- (void)setUpClass {
    // Run at start of all tests in the class
}

- (void)tearDownClass {
    // Run at end of all tests in the class
}

- (void)setUp {
    // Run before each test method
}

- (void)tearDown {
    // Run after each test method
}

- (void)testADD
{
    int8_t initialValues [] = {
        0x01,
        0x8A,
        0xB1,
        0x07,
        0x78,
        0xFD,
        0x80,
        0x9B,
        0x26,
        0xAA,
        0x5A
    };
    
    int8_t numbersToAdd [] = {
        0x00,
        0x2C,
        0xD2,
        0x06,
        0x69,
        0x03,
        0x80,
        0x61,
        0x76,
        0xBB,
        0xA6
    };
    
    int8_t expectedResult [] = {
        0x01,
        0xB6,
        0x83,
        0x0D,
        0xE1,
        0x00,
        0x00,
        0xFC,
        0x9C,
        0x65,
        0x00
    };
    
    int8_t expectedZ [] = {
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        0,
        0,
        0,
        1
    };
    
    int8_t expectedH [] = {
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        0
    };
    
    int8_t expectedC [] = {
        0,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        1,
        1,
        0
    };

    int nTests = sizeof(numbersToAdd)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X + %#X", i, REG_A, numbersToAdd[i]);
            ADD(numbersToAdd[i]);
            
            GHAssertTrue(REG_A == expectedResult[i], @"Result %#X --> expected %#X", REG_A, expectedResult[i]);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ[i], @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ[i]);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void)testADC
{
    int8_t initialValues [] = {
        0x01,
        0x8A,
        0xB1,
        0x07,
        0x78,
        0xFD,
        0x80,
        0x9B,
        0x26,
        0xAA,
        0x5A,
        0xFE,
        0x15,
    };
    
    int8_t numbersToAdd [] = {
        0x00,
        0x2C,
        0xD2,
        0x06,
        0x69,
        0x03,
        0x80,
        0x61,
        0x76,
        0xBB,
        0xA6,
        0x01,
        0xA2,
    };
    
    int8_t expectedResult_cReset [] = {
        0x01,
        0xB6,
        0x83,
        0x0D,
        0xE1,
        0x00,
        0x00,
        0xFC,
        0x9C,
        0x65,
        0x00,
        0xFF,
        0xB7,
    };
    
    int8_t expectedResult_cSet [] = {
        0x02,
        0xB7,
        0x84,
        0x0E,
        0xE2,
        0x01,
        0x01,
        0xFD,
        0x9D,
        0x66,
        0x01,
        0x00,
        0xB8,
    };
    
    int8_t expectedZ_cReset [] = {
        0,
        0,
        0,
        0,
        0,
        1,
        1,
        0,
        0,
        0,
        1,
        0,
        0,
    };
    
    int8_t expectedZ_cSet [] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        1,
        0,
    };
    
    int8_t expectedH_cReset [] = {
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        0,
        0,
        0,
    };
    
    int8_t expectedH_cSet [] = {
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        0,
        1,
        1,
        0,
        0,
        1,
    };
    
    int8_t expectedC_cReset [] = {
        0,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        0,
    };
    
    int8_t expectedC_cSet [] = {
        0,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        1,
        1,
        0,
        0,
        0,
    };
    
    int nTests = sizeof(numbersToAdd)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        int8_t *expectedResult = nil;
        int8_t *expectedZ = nil;
        int8_t *expectedH = nil;
        int8_t *expectedC = nil;
        
        
        
        if (0 == j) {
            expectedResult = expectedResult_cReset;
            expectedZ = expectedZ_cReset;
            expectedH = expectedH_cReset;
            expectedC = expectedC_cReset;
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            expectedResult = expectedResult_cSet;
            expectedZ = expectedZ_cSet;
            expectedH = expectedH_cSet;
            expectedC = expectedC_cSet;
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X + %#X + %d", i, REG_A, numbersToAdd[i], getFlagC());
            ADC(numbersToAdd[i]);
            
            GHAssertTrue(REG_A == expectedResult[i], @"Result %#X --> expected %#X", REG_A, expectedResult[i]);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ[i], @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ[i]);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void)testSUB
{
    int8_t initialValues [] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x39
    };
    
    int8_t numbersToSub [] = {
        0x00,
        0xD7,
        0xC0,
        0x04,
        0x3A,
        0xAF
    };
    
    int8_t expectedResult [] = {
        0x01,
        0x00,
        0xBF,
        0x07,
        0x6B,
        0x8A
    };
    
    int8_t expectedZ [] = {
        0,
        1,
        0,
        0,
        0,
        0
    };
    
    int8_t expectedH [] = {
        1,
        1,
        1,
        0,
        0,
        1
    };
    
    int8_t expectedC [] = {
        1,
        1,
        0,
        1,
        0,
        0
    };
    
    int nTests = sizeof(numbersToSub)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X - %#X", i, REG_A, numbersToSub[i]);
            SUB(numbersToSub[i]);
            
            GHAssertTrue(REG_A == expectedResult[i], @"Result %#X --> expected %#X", REG_A, expectedResult[i]);
            GHAssertTrue(ALU_FLAG_N == 1, @"N %d --> expected %d", ALU_FLAG_N, 1);
            GHAssertTrue(ALU_FLAG_Z == expectedZ[i], @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ[i]);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void)testSBC
{
    int8_t initialValues [] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x39
    };
    
    int8_t numbersToSub [] = {
        0x00,
        0xD7,
        0xC0,
        0x04,
        0x3A,
        0xAF
    };
    
    int8_t expectedResult_cReset [] = {
        0x01,
        0x00,
        0xBF,
        0x07,
        0x6B,
        0x8A
    };
    
    int8_t expectedResult_cSet [] = {
        0x00,
        0xFF,
        0xBE,
        0x06,
        0x6A,
        0x89
    };
    
    int8_t expectedZ_cReset [] = {
        0,
        1,
        0,
        0,
        0,
        0
    };
    
    int8_t expectedZ_cSet [] = {
        1,
        0,
        0,
        0,
        0,
        0
    };
    
    int8_t expectedH_cReset [] = {
        1,
        1,
        1,
        0,
        0,
        1
    };
    
    int8_t expectedH_cSet [] = {
        1,
        1,
        1,
        0,
        0,
        1
    };
    
    int8_t expectedC_cReset [] = {
        1,
        1,
        0,
        1,
        0,
        0
    };
    
    int8_t expectedC_cSet [] = {
        1,
        1,
        0,
        1,
        0,
        0
    };
    
    int nTests = sizeof(numbersToSub)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        int8_t *expectedResult = nil;
        int8_t *expectedZ = nil;
        int8_t *expectedH = nil;
        int8_t *expectedC = nil;
        
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            expectedResult = expectedResult_cReset;
            expectedZ = expectedZ_cReset;
            expectedH = expectedH_cReset;
            expectedC = expectedC_cReset;
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
            expectedResult = expectedResult_cSet;
            expectedZ = expectedZ_cSet;
            expectedH = expectedH_cSet;
            expectedC = expectedC_cSet;
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X - %#X - %d", i, REG_A, numbersToSub[i], getFlagC());
            SBC(numbersToSub[i]);
            
            GHAssertTrue(REG_A == expectedResult[i], @"Result %#X --> expected %#X", REG_A, expectedResult[i]);
            GHAssertTrue(ALU_FLAG_N == 1, @"N %d --> expected %d", ALU_FLAG_N, 1);
            GHAssertTrue(ALU_FLAG_Z == expectedZ[i], @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ[i]);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void)testAND
{
    int8_t initialValues[] = {
        0x00,
        0xB3,
        0xC0,
        0x04,
        0x3A,
        0xAF,
        0x9D
    };
    
    int8_t numbers[] = {
        0xFF,
        0xA5,
        0xC0,
        0x00,
        0xA2,
        0x01,
        0x76
    };
    

    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X & %#X", i, REG_A, numbers[i]);
            AND(numbers[i]);
            
            int8_t expectedResult = (initialValues[i] & numbers[i]);
            int8_t expectedZ = (0 == expectedResult)? 1:0;
            
            GHAssertTrue(REG_A == expectedResult, @"Result %#X --> expected %#X", REG_A, expectedResult);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == 1, @"H %d --> expected %d", ALU_FLAG_H, 1);
            GHAssertTrue(ALU_FLAG_C == 0, @"C %d --> expected %d", ALU_FLAG_C, 0);
        }
    }
}

- (void)testOR
{
    int8_t initialValues[] = {
        0x00,
        0xB3,
        0xC0,
        0x04,
        0x3A,
        0xAF,
        0x9D
    };
    
    int8_t numbers[] = {
        0x31,
        0xA5,
        0xC0,
        0x00,
        0xA2,
        0x01,
        0x76
    };
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X | %#X", i, REG_A, numbers[i]);
            OR(numbers[i]);
            
            int8_t expectedResult = (initialValues[i] | numbers[i]);
            int8_t expectedZ = (0 == expectedResult)? 1:0;
            
            GHAssertTrue(REG_A == expectedResult, @"Result %#X --> expected %#X", REG_A, expectedResult);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
            GHAssertTrue(ALU_FLAG_C == 0, @"C %d --> expected %d", ALU_FLAG_C, 0);
        }
    }
}

- (void)testXOR
{
    int8_t initialValues[] = {
        0x00,
        0xB3,
        0xC0,
        0x04,
        0x3A,
        0xAF,
        0x9D,
        0xE1,
        0x2A
    };
    
    int8_t numbers[] = {
        0x31,
        0xA5,
        0xC0,
        0x00,
        0xA2,
        0x01,
        0x76,
        0xE1,
        0xD5
    };
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: %#X ^ %#X", i, REG_A, numbers[i]);
            XOR(numbers[i]);
            
            int8_t expectedResult = (initialValues[i] ^ numbers[i]);
            int8_t expectedZ = (0 == expectedResult)? 1:0;
            
            GHAssertTrue(REG_A == expectedResult, @"Result %#X --> expected %#X", REG_A, expectedResult);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
            GHAssertTrue(ALU_FLAG_C == 0, @"C %d --> expected %d", ALU_FLAG_C, 0);
        }
    }
}

- (void)testCP
{
    int8_t initialValues[] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x39,
        0x1A,
        0x00,
        0xFF
    };
    
    int8_t numbers[] = {
        0x00,
        0xD7,
        0xC0,
        0x04,
        0x3A,
        0xAF,
        0x1A,
        0x00,
        0xFF
    };
    
    int8_t expectedH[] = {
        1,
        1,
        1,
        0,
        0,
        1,
        1,
        1,
        1
    };
    
    int8_t expectedC[] = {
        1,
        1,
        0,
        1,
        0,
        0,
        1,
        1,
        1
    };
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: CP(%#X,%#X)", i, REG_A, numbers[i]);
            CP(numbers[i]);
            
            int8_t expectedZ = (REG_A == numbers[i])? 1:0;
            
            GHAssertTrue(REG_A == initialValues[i], @"Result %#X --> expected %#X", REG_A, initialValues[i]);
            GHAssertTrue(ALU_FLAG_N == 1, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void)testINC
{
    int8_t initialValues[] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x39,
        0x17,
        0x00,
        0xFF
    };
    
    int8_t expectedH[] = {
        0,
        1,
        0,
        0,
        0,
        0,
        1,
        0,
        0
    };
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: INC(%#X)", i, REG_A);
            INC(&REG_A);
            
            int8_t expectedZ = (REG_A == 0)? 1:0;
            int8_t expectedRes = initialValues[i] + 1;
            
            GHAssertTrue(REG_A == expectedRes, @"Result %#X --> expected %#X", REG_A, expectedRes);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
        }
    }
}

- (void)testDEC
{
    int8_t initialValues[] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x38,
        0x17,
        0x00,
        0x48
    };
    
    int8_t expectedH[] = {
        1,
        1,
        1,
        1,
        1,
        0,
        1,
        1,
        0
    };
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: DEC(%#X)", i, REG_A);
            DEC(&REG_A);
            
            int8_t expectedZ = (REG_A == 0)? 1:0;
            int8_t expectedRes = initialValues[i] - 1;
            
            GHAssertTrue(REG_A == expectedRes, @"Result %#X --> expected %#X", REG_A, expectedRes);
            GHAssertTrue(ALU_FLAG_N == 1, @"N %d --> expected %d", ALU_FLAG_N, 1);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
        }
    }
}

- (void)testCPL
{
    int8_t initialValues[] = {
        0x01,
        0xD7,
        0x7F,
        0x0B,
        0xA5,
        0x38,
        0x17,
        0x00,
        0x48
    };
    
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: CPL(%#X)", i, REG_A);
            CPL(&REG_A);
            
            int8_t expectedRes = ~(initialValues[i]);
            
            GHAssertTrue(REG_A == expectedRes, @"Result %#X --> expected %#X", REG_A, expectedRes);
            GHAssertTrue(ALU_FLAG_N == 1, @"N %d --> expected %d", ALU_FLAG_N, 1);
            GHAssertTrue(ALU_FLAG_H == 1, @"H %d --> expected %d", ALU_FLAG_H, 1);
        }
    }
}

- (void)testDAA
{
    int8_t initialValues[] = {
        0x5B,
        0x01,
        0x36,
        0x08,
        0x14,
        0xAE,
        0xE9
    };
    
    int8_t expected[] = {
        0x91,
        0x01,
        0x54,
        0x08,
        0x20,
        0x74,
        0x33
    };
    
    
    
    int nTests = sizeof(initialValues)/sizeof(int8_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            REG_A = initialValues[i];
            GHTestLog(@"Operation %d: DAA(%#X)", i, REG_A);
            DAA();
            
            int8_t expectedRes = expected[i];
            int8_t expectedZ = (0 == expected[i]);
            
            GHAssertTrue(REG_A == expectedRes, @"Result %#X --> expected %#X", REG_A, expectedRes);
            GHAssertTrue(ALU_FLAG_Z == expectedZ, @"Z %d --> expected %d", ALU_FLAG_Z, expectedZ);
            GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 1);
        }
    }
}


- (void) testADD16
{
    int16_t initialValues[] = {
        0x405A,
        0xA896,
        0XFFFF,
        0x0000,
        0xB6A5,
        0x6794,
        0xA751,
        0xB796
    };
    
    int16_t numbers[] = {
        0x0001,
        0x58A8,
        0x0001,
        0x57B3,
        0xC137,
        0x71B9,
        0x54BB,
        0xA21C
    };
    
    int8_t expectedH[] = {
        0,
        1,
        0,
        0,
        0,
        1,
        1,
        1
    };
    
    int8_t expectedC[] = {
        0,
        0,
        0,
        0,
        1,
        1,
        0,
        1
    };
    
    int nTests = sizeof(initialValues)/sizeof(int16_t);
    
    for (int j = 0; j < 2; j++) {
        if (0 == j) {
            GHTestLog(@"Carry flag reset");
            setFlagC(0);
        }else {
            setFlagC(1);
            GHTestLog(@"Carry flag set");
        }
        
        for (int i = 0; i < nTests; i++) {
            int16_t rr = initialValues[i];
            int16_t expectedRes = rr + numbers[i];
            
            GHTestLog(@"Operation ADD16(%#X, %#X)", rr, numbers[i]);
            ADD16(&rr, numbers[i]);
            GHAssertTrue(rr == expectedRes, @"Result %#X --> expected %#X", rr, expectedRes);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_H == expectedH[i], @"H %d --> expected %d", ALU_FLAG_H, expectedH[i]);
            GHAssertTrue(ALU_FLAG_C == expectedC[i], @"C %d --> expected %d", ALU_FLAG_C, expectedC[i]);
        }
    }
}

- (void) testINC16
{

}

- (void) testDEC16
{
    
}


@end
