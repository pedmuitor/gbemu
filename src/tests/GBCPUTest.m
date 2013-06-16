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
    int dataLength = 100;
    int8_t dataLoad[dataLength];
    for (int i = 0; i < dataLength; i++) {
        dataLoad[i] = [self wordForIndex:i];
    }
    const int8_t * data = dataLoad;
    GBMemory_setData(data, dataLength, GBMemoryModeBigEndian);

}

- (void)tearDown
{
    GBMemory_freeData();
}


#pragma mark Private

- (int8_t)wordForIndex:(int)index
{
    return (int8_t)(index % 10 + index);
}

@end
