//
//  GBALUTest.m
//  GBEmu
//
//  Created by Pedro Muiños on 11/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBALUTest.h"

#import "GBCPU.h"
#import "GBCPU_ALU.h"

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
        
        //H Tests
        0x07,
        //C Tests
        0x78
    };
    
    int8_t numbersToAdd [] = {
        0x00,
        0x2C,
        0xD2,
        0x06,
        0x69
    };
    
    int8_t expectedResult [] = {
        0x01,
        0xB6,
        0x83,
        0x0D,
        0xE1
    };
    
    int8_t expectedZ [] = {
        0,
        0,
        0,
        0,
        0
    };
    
    int8_t expectedH [] = {
        0,
        1,
        0,
        1,
        1
    };
    
    int8_t expectedC [] = {
        0,
        0,
        0,
        0,
        1
    };

    int nTests = sizeof(numbersToAdd)/sizeof(int8_t);
    
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

@end
