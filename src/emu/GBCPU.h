//
//  GBCPUInstructions.h
//  GBEmu
//
//  Created by Jesús on 02/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBCPUInstructions_h
#define GBEmu_GBCPUInstructions_h

#include <stdbool.h>

struct {
    struct {
        int8_t  A, B, C, D, E, F, H, L;
        int16_t PC, SP;
    }_r;
    
}Z80;

#define REGISTERS       Z80._r
#define REG_A           REGISTERS.A
#define REG_B           REGISTERS.B
#define REG_C           REGISTERS.C
#define REG_D           REGISTERS.D
#define REG_E           REGISTERS.E
#define REG_F           REGISTERS.F
#define REG_H           REGISTERS.H
#define REG_L           REGISTERS.L
#define REG_PC          REGISTERS.PC
#define REG_SP          REGISTERS.SP

#define REG_AF          DWORD_FROM_HL(REG_A, REG_F)
#define REG_BC          DWORD_FROM_HL(REG_B, REG_C)
#define REG_DE          DWORD_FROM_HL(REG_D, REG_E)
#define REG_HL          DWORD_FROM_HL(REG_H, REG_L)

//----------------------------------------------//
//                                              //
//                 CPU Commands                 //
//                                              //
//----------------------------------------------//

void setUp(void);
void shutDown(void);

void nextOperation(void);
int8_t readOperationWordParameter(void);
int16_t readOpertionDwordParameter(void);

#endif
