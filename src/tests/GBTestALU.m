//
//  GBTestALU.m
//  GBEmu
//
//  Created by Pedro Muiños on 08/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import "GBCPU.h"
#import "GBCPU_ALU.h"
#import "GBTestALU.h"

@implementation GBTestALU

- (void)setUp
{
    [super setUp];
    
    // Set-up code here.
}

- (void)tearDown
{
    // Tear-down code here.
    
    [super tearDown];
}

- (void)test8
{
    setFlagZ(0);
    setFlagN(0);
    setFlagH(0);
    setFlagC(0);
    
    REG_A = 0x01;
    ADD(0x01);
}

- (void)testALU
{
    [self test8];
}

@end
