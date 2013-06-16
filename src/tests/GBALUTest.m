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
    int16_t initialValues[] = {
        0x405A,
        0xA896,
        0XFFFF,
        0x0000,
        0xB6A5,
        0x6794,
        0xA751,
        0xB796,
        0x013D,
        0x60AE
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
            int16_t expectedRes = rr +1;
            
            GHTestLog(@"Operation INC16(%#X)",rr);
            INC16(&rr);
            GHAssertTrue(rr == expectedRes, @"Result %#X --> expected %#X", rr, expectedRes); 
        }
    }
}

- (void) testDEC16
{
    int16_t initialValues[] = {
        0x405A,
        0xA896,
        0XFFFF,
        0x0000,
        0xB6A5,
        0x6794,
        0xA751,
        0xB796,
        0x013D,
        0x60AE
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
            int16_t expectedRes = rr - 1;
            
            GHTestLog(@"Operation %d DEC16(%#X)",i ,rr);
            DEC16(&rr);
            GHAssertTrue(rr == expectedRes, @"Result %#X --> expected %#X", rr, expectedRes);
        }
    }
}

- (void)testRL
{
    int8_t inValues[] = {
        0x88,
        0x00,
        0x00,
        0x00,
        0xA4,
        0x48,
        0x91,
        0x22,
        0x45,
        0x8A,
        0x14,
        0x29,
        0x52
    };
    
    int8_t outValues[] = {
        0x10,
        0x01,
        0x00,
        0x00,
        0x48,
        0x91,
        0x22,
        0x45,
        0x8A,
        0x14,
        0x29,
        0x52,
        0xA4
        
    };
    
    int8_t c[] = {
        1,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        0,
        1,
        0,
        0,
        0
    };
    
    int nTests = sizeof(inValues)/sizeof(int8_t);
    
    setFlagC(0);
    for (int i = 0; i < nTests; i++) {
        GHTestLog(@"Operation %i RL(%#X)", i, inValues[i]);
        REG_A = inValues[i];
        RL(&REG_A);
        GHAssertTrue(REG_A == outValues[i], @"Result %#X --> expected %#X", REG_A, outValues[i]);
        GHAssertTrue(ALU_FLAG_C == c[i], @"C %d --> expected %d", ALU_FLAG_C, c[i]);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        setFlagC(ALU_FLAG_C);
    }
    setFlagC(0);
}

- (void)testRLC
{
    int8_t inValues[] = {
        0x88,
        0x00,
        0x00,
        0x00,
        0xA4,
        0x49,
        0x92,
        0x25,
        0x4A
    };
    
    int8_t outValues[] = {
        0x11,
        0x00,
        0x00,
        0x00,
        0x49,
        0x92,
        0x25,
        0x4A,
        0x94
    };
    
    int8_t c[] = {
        1,
        0,
        0,
        0,
        1,
        0,
        1,
        0,
        0
    };
    
    int nTests = sizeof(inValues)/sizeof(int8_t);
    
    setFlagC(0);
    for (int i = 0; i < nTests; i++) {
        GHTestLog(@"Operation %i RLC(%#X)", i, inValues[i]);
        REG_A = inValues[i];
        RLC(&REG_A);
        GHAssertTrue(REG_A == outValues[i], @"Result %#X --> expected %#X", REG_A, outValues[i]);
        GHAssertTrue(ALU_FLAG_C == c[i], @"C %d --> expected %d", ALU_FLAG_C, c[i]);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        setFlagC(ALU_FLAG_C);
    }
    setFlagC(0);
}

- (void)testRR
{
    int8_t inValues[] = {
        0x88,
        0x44,
        0x22,
        0x11,
        0x08,
        0x84,
        0x42,
        0x21,
        0x10
    };
    
    int8_t outValues[] = {
        0x44,
        0x22,
        0x11,
        0x08,
        0x84,
        0x42,
        0x21,
        0x10,
        0x88
        
    };
    
    int8_t c[] = {
        0,
        0,
        0,
        1,
        0,
        0,
        0,
        1,
        0
    };
    
    int nTests = sizeof(inValues)/sizeof(int8_t);
    
    setFlagC(0);
    for (int i = 0; i < nTests; i++) {
        GHTestLog(@"Operation %i RR(%#X)", i, inValues[i]);
        REG_A = inValues[i];
        RR(&REG_A);
        GHAssertTrue(REG_A == outValues[i], @"Result %#X --> expected %#X", REG_A, outValues[i]);
        GHAssertTrue(ALU_FLAG_C == c[i], @"C %d --> expected %d", ALU_FLAG_C, c[i]);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        setFlagC(ALU_FLAG_C);
    }
    setFlagC(0);
}

- (void)testRRC
{
    int8_t inValues[] = {
        0x5D,
        0xAE,
        0x57,
        0xAB,
        0xD5,
        0xEA,
        0x75,
        0xBA,
        0x5D
    };
    
    int8_t outValues[] = {
        0xAE,
        0x57,
        0xAB,
        0xD5,
        0xEA,
        0x75,
        0xBA,
        0x5D,
        0xAE
    };
    
    int8_t c[] = {
        1,
        0,
        1,
        1,
        1,
        0,
        1,
        0,
        1
    };
    
    int nTests = sizeof(inValues)/sizeof(int8_t);
    
    setFlagC(0);
    for (int i = 0; i < nTests; i++) {
        GHTestLog(@"Operation %i RRC(%#X)", i, inValues[i]);
        REG_A = inValues[i];
        RRC(&REG_A);
        GHAssertTrue(REG_A == outValues[i], @"Result %#X --> expected %#X", REG_A, outValues[i]);
        GHAssertTrue(ALU_FLAG_C == c[i], @"C %d --> expected %d", ALU_FLAG_C, c[i]);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        setFlagC(ALU_FLAG_C);
    }
    setFlagC(0);
}

- (void)testSLA
{
    int8_t n = 0x9A;
    REG_A = n;
    int i = 0;
    
    int8_t c[] = {
        1,
        0,
        0,
        1,
        1,
        0,
        1,
        0
    };
    
    while (abs(n) > 0) {
        GHTestLog(@"Operation %i SLA(%#X)", i, n);
        SLA(&REG_A);
        n <<= 1;
        GHAssertTrue(REG_A == n, @"Result %#X --> expected %#X", REG_A, n);
        GHAssertTrue(ALU_FLAG_C == c[i], @"C %d --> expected %d", ALU_FLAG_C, c[i]);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        
        i++;
    }
}

- (void)testSRA
{
    for (int i = 0; i < 2; i++) {
        int8_t n = (i==0)?0xF3:0x6F;
        REG_A = n;
        
        for (int j = 0; j < sizeof(int8_t)*8; j++) {
            GHTestLog(@"Operation %i SRA(%#X)", j, n);
            int8_t c = lessSignificantBit(n);
            SRA(&REG_A);
            n >>= 1;
            GHAssertTrue(REG_A == n, @"Result %#X --> expected %#X", REG_A, n);
            GHAssertTrue(ALU_FLAG_C == c, @"C %d --> expected %d", ALU_FLAG_C, c);
            GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        }
    }
}

- (void)testSRL
{
    for (int i = 0; i < 2; i++) {
        int8_t n = (i==0)?0xF3:0x6F;
        REG_A = n;
        
        for (int j = 0; j < sizeof(int8_t)*8; j++) {
            GHTestLog(@"Operation %d SRL(%#X)", j, n);
            int8_t c = lessSignificantBit(n);
            SRL(&REG_A);
            n = n>>1 & 0x7F;
            GHAssertTrue(REG_A == n, @"Result %#X --> expected %#X", REG_A, n);
            GHAssertTrue(ALU_FLAG_C == c, @"C %d --> expected %d", ALU_FLAG_C, c);
            GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
            GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
            GHAssertTrue(ALU_FLAG_Z == (REG_A == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (REG_A == 0));
        }
    }
}

- (void)testSWAP
{
    int8_t inValues[] = {
        0x00,
        0xFF,
        0x3A,
        0x0F,
        0x9C,
        0xB1,
        0x2D
    };
    
    int8_t outValues[] = {
        0x00,
        0xFF,
        0xA3,
        0xF0,
        0xC9,
        0x1B,
        0xD2
    };
    
    int nTests = sizeof(inValues)/sizeof(int8_t);
    
    for (int i = 0; i < nTests; i++) {
        GHTestLog(@"Operation %i SWAP(%#X)",i, inValues[i]);
        SWAP(&inValues[i]);
        GHAssertTrue(outValues[i] == inValues[i], @"Result %#X --> expected %#X", outValues[i], inValues[i]);
        GHAssertTrue(ALU_FLAG_C == 0, @"C %d --> expected %d", ALU_FLAG_C, 0);
        GHAssertTrue(ALU_FLAG_H == 0, @"H %d --> expected %d", ALU_FLAG_H, 0);
        GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
        GHAssertTrue(ALU_FLAG_Z == (outValues[i] == 0), @"Z %d --> expected %d", ALU_FLAG_Z, (outValues[i] == 0));
    }
}

- (void)testBIT
{
    for (int i = 0; i < 2; i++) {
        int8_t n = (0 == i)?0xFF:0x00;
        
        for (int j = 0; j <= sizeof(int8_t)*8; j++) {
            if (i == 0) {
                n-=pow(2, j);
            }else {
                n+=pow(2, j);
            }
            
            for (int k = 0; k < sizeof(int8_t)*8; k++) {
                uint8_t z;
                
                if (i == 0) {
                    z = (k > j);
                }else {
                    z = (k <= j);
                }
                
                GHTestLog(@"Operation %i BIT(%#X)",k, n);
                
                BIT(n, k);
                GHAssertTrue(ALU_FLAG_N == 0, @"N %d --> expected %d", ALU_FLAG_N, 0);
                GHAssertTrue(ALU_FLAG_H == 1, @"H %d --> expected %d", ALU_FLAG_H, 1);
                GHAssertTrue(ALU_FLAG_Z == (z == 0), @"Z %d --> expected %d", ALU_FLAG_Z, z);
            }
        }
    }
    
}

- (void)testSET
{
    int8_t n = 0x00;
    int8_t res = 0x00;
    
    for (int i = 0; i <= sizeof(int8_t)*8; i++) {
        GHTestLog(@"Operation %i SET(%#X, %i)",i, n, i);
        res+= pow(2, i);
        SET(&n, i);
        GHAssertTrue(n == res, @"Result %#X --> expected %#X", res, n);
    }
}

- (void)testRES
{
    int8_t n = 0xFF;
    int8_t res = 0xFF;
    
    for (int i = 0; i <= sizeof(int8_t)*8; i++) {
        GHTestLog(@"Operation %i RES(%#X, %i)",i, n, i);
        res-= pow(2, i);
        RES(&n, i);
        GHAssertTrue(n == res, @"Result %#X --> expected %#X", res, n);
    }
}



@end
