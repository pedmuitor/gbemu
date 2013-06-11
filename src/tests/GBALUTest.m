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

- (void)test8bitOps
{
    REG_A = 0x01;
    ADD(0x01);
    
    GHAssertTrue(REG_A == 0x02, @"REG_A value %#X, expected %#X", REG_A, 0x02);
}

@end
