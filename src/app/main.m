//
//  main.m
//  GBEmu
//
//  Created by Pedro Muiños on 31/05/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#import <Foundation/Foundation.h>
#include "GBCPU.h"

int main(int argc, const char * argv[])
{

    @autoreleasepool {
        
        for (int i = 0; i < 30; i++) {
            INC(&REG_A);
        }
        
        NSLog(@"A %d", REG_A);
        
        for (int i = 0; i < 7; i++) {
            DEC(&REG_A);
        }
        
        NSLog(@"A %d", REG_A);
        
        REG_H = 0x7F;
        REG_L = 0xFF;
        
        
    }
    return 0;
}

