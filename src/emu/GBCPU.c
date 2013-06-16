//
//  GBCPUInstructions.c
//  GBEmu
//
//  Created by Jesús on 02/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>

#include "GBCPU.h"
#include "GBCPU_ALU.h"
#include "GBMemory.h"
#include "GBUtils.h"

//----------------------------------------------//
//                                              //
//                  Helpers                     //
//                                              //
//----------------------------------------------//

void GBCPU_LD (int8_t *r, int8_t n)
{
    *r = n;
}

void GBCPU_LD16 (int16_t *rr, int16_t nn)
{
    *rr = nn;
}

void GBCPU_LD16_HL (int8_t *rh, int8_t *rl, int16_t nn)
{
    *rl = (0xFF & ((nn) >> 8));
    *rh = 0xFF & (nn);
}

void GBCPU_INC16_HL (int8_t *rh, int8_t *rl)
{
    int16_t r = DWORD_FROM_HL(*rh, *rl);
    INC16(&r);
    GBCPU_LD16_HL(rh, rl, r);
}

void GBCPU_DEC16_HL (int8_t *rh, int8_t *rl)
{
    int16_t r = DWORD_FROM_HL(*rh, *rl);
    DEC16(&r);
    GBCPU_LD16_HL(rh, rl, r);
}

bool GBCPU_getFlagZ()
{
    return bitAtIndex(REG_F, 7);
}

void GBCPU_setFlagZ(bool z)
{
    setBitAtIndex(&REG_F, 7, z);
}

bool GBCPU_getFlagN()
{
    return bitAtIndex(REG_F, 6);
}

void GBCPU_setFlagN(bool n)
{
    setBitAtIndex(&REG_F, 6, n);
}

bool GBCPU_getFlagH()
{
    return bitAtIndex(REG_F, 5);
}

void GBCPU_setFlagH(bool h)
{
    setBitAtIndex(&REG_F, 5, h);
}

bool GBCPU_getFlagC()
{
   return bitAtIndex(REG_F, 4);
}

void GBCPU_setFlagC(bool c)
{
    setBitAtIndex(&REG_F, 4, c);
}


void GBCPU_setHalt(bool halt)
{
    FLAGS_HALT = halt;
}

void GBCPU_setStop(bool stop)
{
    FLAGS_STOP = stop;
}

void GBCPU_setInterruptsEnabled(bool enabled)
{
    FLAGS_IE = enabled;
}

int8_t GBCPU_readOperationWordParameter(void)
{
    uint8_t result = GBMemory_getWordAt(REG_PC++);
    return result;
}

int16_t GBCPU_readOperationDwordParameter(void)
{
    uint16_t result = GBMemory_getDwordAt(REG_PC++);
    REG_PC++;
    
    return result;
}


void GBCPU_setUp(void)
{
    //TODO: GBCPU_setUp registers initial values
    REG_SP = 0xFFFE;
    
    FLAGS_IE = true;
    FLAGS_STOP = false;
    FLAGS_HALT = false;
}

void GBCPU_shuwdown(void)
{
    
}

void nextOperation(void)
{
    uint8_t opCode = GBMemory_getWordAt(REG_PC++);
    int8_t n = 0;
    int16_t nn = 0;
    
    switch (opCode) {
            //8-Bit loads
        case 0x06:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_B, n);
            break;
        case 0x0E:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_C, n);
            break;
        case 0x16:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_D, n);
            break;
        case 0x1E:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_E, n);
            break;
        case 0x26:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_H, n);
            break;
        case 0x2E:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_L, n);
            break;
            
            //GBCPU_LD r1, r2
        case 0x7F:
            GBCPU_LD(&REG_A, REG_A);
            break;
        case 0x78:
            GBCPU_LD(&REG_A, REG_B);
            break;
        case 0x79:
            GBCPU_LD(&REG_A, REG_C);
            break;
        case 0x7A:
            GBCPU_LD(&REG_A, REG_D);
            break;
        case 0x7B:
            GBCPU_LD(&REG_A, REG_E);
            break;
        case 0x7C:
            GBCPU_LD(&REG_A, REG_H);
            break;
        case 0x7D:
            GBCPU_LD(&REG_A, REG_L);
            break;
        case 0x7E:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_A, n);
            break;
            
        case 0x40:
            GBCPU_LD(&REG_B, REG_B);
            break;
        case 0x41:
            GBCPU_LD(&REG_B, REG_C);
            break;
        case 0x42:
            GBCPU_LD(&REG_B, REG_D);
            break;
        case 0x43:
            GBCPU_LD(&REG_B, REG_E);
            break;
        case 0x44:
            GBCPU_LD(&REG_B, REG_H);
            break;
        case 0x45:
            GBCPU_LD(&REG_B, REG_L);
            break;
        case 0x46:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_B, n);
            break;
            
        case 0x48:
            GBCPU_LD(&REG_C, REG_B);
            break;
        case 0x49:
            GBCPU_LD(&REG_C, REG_C);
            break;
        case 0x4A:
            GBCPU_LD(&REG_C, REG_D);
            break;
        case 0x4B:
            GBCPU_LD(&REG_C, REG_E);
            break;
        case 0x4C:
            GBCPU_LD(&REG_C, REG_H);
            break;
        case 0x4D:
            GBCPU_LD(&REG_C, REG_L);
            break;
        case 0x4E:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_C, n);
            break;
            
        case 0x50:
            GBCPU_LD(&REG_D, REG_B);
            break;
        case 0x51:
            GBCPU_LD(&REG_D, REG_C);
            break;
        case 0x52:
            GBCPU_LD(&REG_D, REG_D);
            break;
        case 0x53:
            GBCPU_LD(&REG_D, REG_E);
            break;
        case 0x54:
            GBCPU_LD(&REG_D, REG_H);
            break;
        case 0x55:
            GBCPU_LD(&REG_D, REG_L);
            break;
        case 0x56:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_D, n);
            break;
            
        case 0x58:
            GBCPU_LD(&REG_E, REG_B);
            break;
        case 0x59:
            GBCPU_LD(&REG_E, REG_C);
            break;
        case 0x5A:
            GBCPU_LD(&REG_E, REG_D);
            break;
        case 0x5B:
            GBCPU_LD(&REG_E, REG_E);
            break;
        case 0x5C:
            GBCPU_LD(&REG_E, REG_H);
            break;
        case 0x5D:
            GBCPU_LD(&REG_E, REG_L);
            break;
        case 0x5E:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_E, n);
            break;
            
        case 0x60:
            GBCPU_LD(&REG_H, REG_B);
            break;
        case 0x61:
            GBCPU_LD(&REG_H, REG_C);
            break;
        case 0x62:
            GBCPU_LD(&REG_H, REG_D);
            break;
        case 0x63:
            GBCPU_LD(&REG_H, REG_E);
            break;
        case 0x64:
            GBCPU_LD(&REG_H, REG_H);
            break;
        case 0x65:
            GBCPU_LD(&REG_H, REG_L);
            break;
        case 0x66:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_H, n);
            break;
            
        case 0x68:
            GBCPU_LD(&REG_L, REG_B);
            break;
        case 0x69:
            GBCPU_LD(&REG_L, REG_C);
            break;
        case 0x6A:
            GBCPU_LD(&REG_L, REG_D);
            break;
        case 0x6B:
            GBCPU_LD(&REG_L, REG_E);
            break;
        case 0x6C:
            GBCPU_LD(&REG_L, REG_H);
            break;
        case 0x6D:
            GBCPU_LD(&REG_L, REG_L);
            break;
        case 0x6E:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_L, n);
            break;
            
        case 0x70:
            GBMemory_writeWordAt(REG_HL, REG_B);
            break;
        case 0x71:
            GBMemory_writeWordAt(REG_HL, REG_C);
            break;
        case 0x72:
            GBMemory_writeWordAt(REG_HL, REG_D);
            break;
        case 0x73:
            GBMemory_writeWordAt(REG_HL, REG_E);
            break;
        case 0x74:
            GBMemory_writeWordAt(REG_HL, REG_H);
            break;
        case 0x75:
            GBMemory_writeWordAt(REG_HL, REG_L);
            break;
        case 0x36:
            n = GBCPU_readOperationWordParameter();
            GBMemory_writeWordAt(REG_HL, n);
            break;
            
            //GBCPU_LD A, n
        case 0x0A:
            n = GBMemory_getWordAt(REG_BC);
            GBCPU_LD(&REG_A, n);
            break;
        case 0x1A:
            n = GBMemory_getWordAt(REG_DE);
            GBCPU_LD(&REG_A, n);
            break;
        case 0xFA:
            nn = GBCPU_readOperationDwordParameter();
            n = GBMemory_getWordAt(nn);
            GBCPU_LD(&REG_A, n);
            break;
        case 0x3E:
            n = GBCPU_readOperationWordParameter();
            GBCPU_LD(&REG_A, n);
            break;
            
            //GBCPU_LD n, A
        case 0x47:
            GBCPU_LD(&REG_B, REG_A);
            break;
        case 0x4F:
            GBCPU_LD(&REG_C, REG_A);
            break;
        case 0x57:
            GBCPU_LD(&REG_D, REG_A);
            break;
        case 0x5F:
            GBCPU_LD(&REG_E, REG_A);
            break;
        case 0x67:
            GBCPU_LD(&REG_H, REG_A);
            break;
        case 0x6F:
            GBCPU_LD(&REG_L, REG_A);
            break;
        case 0x02:
            GBMemory_writeWordAt(REG_BC, REG_A);
            break;
        case 0x12:
            GBMemory_writeWordAt(REG_DE, REG_A);
            break;
        case 0x77:
            GBMemory_writeWordAt(REG_HL, REG_A);
            break;
        case 0xEA:
            nn = GBCPU_readOperationDwordParameter();
            GBMemory_writeWordAt(nn, REG_A);
            break;
            
            //GBCPU_LD A, (C)
        case 0xF2:
            n = GBMemory_getWordAt(0xFF00 + REG_C);
            GBCPU_LD(&REG_A, n);
            break;
            
            //GBCPU_LD (C), A
        case 0xE2:
            GBMemory_writeWordAt(0xFF00 + REG_C, REG_A);
            break;
            
            //GBCPU_LDD A, (HL)
        case 0x3A:
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_A, n);
            GBCPU_DEC16_HL(&REG_H, &REG_L);
            break;
            
            //GBCPU_LDD (HL), A
        case 0x32:
            GBMemory_writeWordAt(REG_HL, REG_A);
            GBCPU_DEC16_HL(&REG_H, &REG_L);
            break;
            
            //GBCPU_LDI A, (HL)
        case 0x2A: 
            n = GBMemory_getWordAt(REG_HL);
            GBCPU_LD(&REG_A, n);
            GBCPU_INC16_HL(&REG_H, &REG_L);
            break;
            
            //GBCPU_LDI (HL), A
        case 0x22:
            GBMemory_writeWordAt(REG_HL, REG_A);
            GBCPU_INC16_HL(&REG_H, &REG_L);
            break;
            
            //GBCPU_LDH (n), A
        case 0xE0:
            n = GBCPU_readOperationWordParameter();
            GBMemory_writeWordAt(0xFF00 + n, REG_A);
            break;
            
            //GBCPU_LDH A, (n)
        case 0xF0:
            n = GBCPU_readOperationWordParameter();
            n = GBMemory_getWordAt(0xFF00 + n);
            GBCPU_LD(&REG_A, n);
            
            //16-bit ops
            //GBCPU_LD n, nn
        case 0x01:
            nn = GBCPU_readOperationDwordParameter();
            GBCPU_LD16_HL(&REG_B, &REG_C, nn);
            break;
        case 0x11:
            nn = GBCPU_readOperationDwordParameter();
            GBCPU_LD16_HL(&REG_D, &REG_E, nn);
            break;
        case 0x21:
            nn = GBCPU_readOperationDwordParameter();
            GBCPU_LD16_HL(&REG_H, &REG_L, nn);
            break;
        case 0x31:
            nn = GBCPU_readOperationDwordParameter();
            GBCPU_LD16(&REG_SP, nn);
            break;
            
            //GBCPU_LD SP, HL
        case 0xF9:
            GBCPU_LD16(&REG_SP, REG_HL);
            break;
            
            //GBCPU_LDHL SP, n
        case 0xF8: {
            n = GBCPU_readOperationWordParameter();
            
            int16_t nn = REG_SP;
            ADD16(&nn, n);
            GBCPU_LD16_HL(&REG_H, &REG_L, nn);
            GBCPU_setFlagZ(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            
            break;
        }
            
            //GBCPU_LD (nn), SP
        case 0x08:
            nn = GBCPU_readOperationDwordParameter();
            GBMemory_writeDwordAt(nn, REG_SP);
            break;
            
            //PUSH nn
        case 0xF5:
            GBMemory_writeDwordAt(REG_SP, REG_AF);
            REG_SP -= 2;
            break;
        case 0xC5:
            GBMemory_writeDwordAt(REG_SP, REG_BC);
            REG_SP -= 2;
            break;
        case 0xD5:
            GBMemory_writeDwordAt(REG_SP, REG_DE);
            REG_SP -= 2;
            break;
        case 0xE5:
            GBMemory_writeDwordAt(REG_SP, REG_HL);
            REG_SP -= 2;
            break;
            
            //POP nn
        case 0xF1:
            nn = GBMemory_getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_A, &REG_F);
            REG_SP += 2;
            break;
        case 0xC1:
            nn = GBMemory_getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_B, &REG_C);
            REG_SP += 2;
            break;
        case 0xD1:
            nn = GBMemory_getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_D, &REG_E);
            REG_SP += 2;
            break;
        case 0xE1:
            nn = GBMemory_getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            REG_SP += 2;
            break;
            
            //ADD A, n
        case 0x87:
            ADD(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
        
        case 0x80:
            ADD(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
        
        case 0x81:
            ADD(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
        
        case 0x82:
            ADD(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
        
        case 0x84:
            ADD(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x85:
            ADD(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x86:
            n = GBMemory_getWordAt(REG_HL);
            ADD(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0xC6:
            n = GBCPU_readOperationWordParameter();
            ADD(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        //ADC A,n
        case 0x8F:
            ADD(REG_A + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x88:
            ADD(REG_B + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x89:
            ADD(REG_C + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8A:
            ADD(REG_D + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8B:
            ADD(REG_E + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8C:
            ADD(REG_H + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8D:
            ADD(REG_L + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8E:
            n = GBMemory_getWordAt(REG_HL);
            ADD(n + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0xCE:
            n = GBCPU_readOperationWordParameter();
            ADD(n + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        //SUB n
        case 0x97:
            SUB(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x90:
            SUB(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x91:
            SUB(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x92:
            SUB(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x93:
            SUB(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x94:
            SUB(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x95:
            SUB(REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x96:
            n = GBMemory_getWordAt(REG_HL);
            SUB(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0xD6:
            n = GBCPU_readOperationWordParameter();
            SUB(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        //SUBC n
        case 0x9F:
            SUB(REG_A + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x98:
            SUB(REG_B + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x99:
            SUB(REG_C + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9A:
            SUB(REG_D + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9B:
            SUB(REG_E + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9C:
            SUB(REG_H + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9D:
            SUB(REG_L + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9E:
            n = GBMemory_getWordAt(REG_HL);
            SUB(n + GBCPU_getFlagC());
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagN(ALU_FLAG_N);
            break;
            
//        case 0x??:
//            n = GBCPU_readOperationWordParameter();
//            SUB(n  + GBCPU_getFlagC());
//            GBCPU_setFlagZ(ALU_FLAG_Z);
//            GBCPU_setFlagN(1);
//            GBCPU_setFlagH(ALU_FLAG_H);
//            GBCPU_setFlagN(ALU_FLAG_N);
//            break;
            
        //AND n
        case 0xA7:
            AND(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
        
        case 0xA0:
            AND(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA1:
            AND(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA2:
            AND(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA3:
            AND(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA4:
            AND(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA5:
            AND(REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA6:
            n = GBMemory_getWordAt(REG_HL);
            AND(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xE6:
            n = GBCPU_readOperationWordParameter();
            AND(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
        
        //OR n
        case 0xB7:
            OR(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB0:
            OR(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB1:
            OR(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB2:
            OR(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB3:
            OR(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB4:
            OR(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB5:
            OR(REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xB6:
            n = GBMemory_getWordAt(REG_HL);
            OR(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xF6:
            n = GBCPU_readOperationWordParameter();
            OR(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
        
        //XOR n
        case 0xAF:
            XOR(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA8:
            XOR(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xA9:
            XOR(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xAA:
            XOR(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xAB:
            XOR(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xAC:
            XOR(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xAD:
            XOR(REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(1);
            GBCPU_setFlagC(0);
            break;
            
        case 0xAE:
            n = GBMemory_getWordAt(REG_HL);
            XOR(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        case 0xEE:
            n = GBCPU_readOperationWordParameter();
            XOR(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(0);
            break;
            
        //CP n
        case 0xBF:
            CP(REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        case 0xB8:
            CP(REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xB9:
            CP(REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBA:
            CP(REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBB:
            CP(REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBC:
            CP(REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBD:
            CP(REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBE:
            n = GBMemory_getWordAt(REG_HL);
            CP(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0xFE:
            n = GBCPU_readOperationWordParameter();
            CP(n);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        //INC n
        case 0x3C:
            INC(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x04:
            INC(&REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x0C:
            INC(&REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x14:
            INC(&REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x1C:
            INC(&REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x24:
            INC(&REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x2C:
            INC(&REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x34:
            n = GBMemory_getWordAt(REG_HL);
            INC(&n);
            GBMemory_writeWordAt(REG_HL, n);
            
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
        
        //DEC n
        case 0x3D:
            DEC(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x05:
            DEC(&REG_B);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x0D:
            DEC(&REG_C);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x15:
            DEC(&REG_D);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x1D:
            DEC(&REG_E);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x25:
            DEC(&REG_H);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x2D:
            DEC(&REG_L);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
            
        case 0x35:
            n = GBMemory_getWordAt(REG_HL);
            DEC(&n);
            GBMemory_writeWordAt(REG_HL, n);
            
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(ALU_FLAG_H);
            break;
        
        //ADD HL, n
        case 0x09:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_B, REG_C));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        case 0x19:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_D, REG_E));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0x29:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_H, REG_L));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        case 0x39:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, REG_SP);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        //ADD SP, n
        case 0xE8:
            n = GBCPU_readOperationWordParameter();
            ADD16(&REG_SP, n);
            GBCPU_setFlagZ(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(ALU_FLAG_H);
            GBCPU_setFlagC(ALU_FLAG_C);
            
        //INC nn
        case 0x03:
            nn = DWORD_FROM_HL(REG_B, REG_C);
            INC16(&nn);
            HL_FROM_DWORD(nn, &REG_B, &REG_C);
            break;
        
        case 0x13:
            nn = DWORD_FROM_HL(REG_D, REG_E);
            INC16(&nn);
            HL_FROM_DWORD(nn, &REG_D, &REG_E);
            break;
            
        case 0x23:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            INC16(&nn);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            break;
            
        case 0x33:
            INC16(&REG_SP);
            break;
            
        //DEC nn
        case 0x0B:
            nn = DWORD_FROM_HL(REG_B, REG_C);
            DEC16(&nn);
            HL_FROM_DWORD(nn, &REG_B, &REG_C);
            break;
            
        case 0x1B:
            nn = DWORD_FROM_HL(REG_D, REG_E);
            DEC16(&nn);
            HL_FROM_DWORD(nn, &REG_D, &REG_E);
            break;
            
        case 0x2B:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            DEC16(&nn);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            break;
            
        case 0x3B:
            DEC16(&REG_SP);
            break;
            
        //Miscellanous
        case 0xCB: {
            
            uint8_t opCode2 = GBCPU_readOperationWordParameter();
            
            switch (opCode2) {
                //SWAP n
                case 0x37:
                    SWAP(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x30:
                    SWAP(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x31:
                    SWAP(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x32:
                    SWAP(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x33:
                    SWAP(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x34:
                    SWAP(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x35:
                    SWAP(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                    
                case 0x36:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SWAP(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(0);
                    break;
                
                    
                //RLC n
                case 0x07:
                    RLC(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                
                case 0x00:
                    RLC(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                
                case 0x01:
                    RLC(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x02:
                    RLC(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x03:
                    RLC(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x04:
                    RLC(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x05:
                    RLC(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x06:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RLC(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                //RL n
                case 0x17:
                    RL(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x10:
                    RL(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x11:
                    RL(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x12:
                    RL(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x13:
                    RL(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x14:
                    RL(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x15:
                    RL(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x16:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RL(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                //RRC n
                case 0x0F:
                    RRC(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x08:
                    RRC(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x09:
                    RRC(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0A:
                    RRC(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0B:
                    RRC(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0C:
                    RRC(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0D:
                    RRC(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0E:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RRC(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                
                //RR n
                case 0x1F:
                    RR(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x18:
                    RR(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x19:
                    RR(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1A:
                    RR(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1B:
                    RR(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1C:
                    RR(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1D:
                    RR(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1E:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RR(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                //SLA n
                case 0x27:
                    SLA(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x20:
                    SLA(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x21:
                    SLA(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x22:
                    SLA(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x23:
                    SLA(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x24:
                    SLA(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x25:
                    SLA(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x26:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SLA(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                
                //SRA n
                case 0x2F:
                    SRA(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x28:
                    SRA(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x29:
                    SRA(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2A:
                    SRA(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2B:
                    SRA(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2C:
                    SRA(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2D:
                    SRA(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2E:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SRA(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                
                //SRL n
                case 0x3F:
                    SRL(&REG_A);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x38:
                    SRL(&REG_B);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x39:
                    SRL(&REG_C);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3A:
                    SRL(&REG_D);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3B:
                    SRL(&REG_E);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3C:
                    SRL(&REG_H);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3D:
                    SRL(&REG_L);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3E:
                    n = GBMemory_getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SRL(&n);
                    GBMemory_writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(0);
                    GBCPU_setFlagC(ALU_FLAG_C);
                    break;
                    
                //BIT b,r
                case 0x47:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_A, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                
                case 0x40:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_B, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                
                case 0x41:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_C, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                    
                case 0x42:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_D, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                    
                case 0x43:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_E, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                    
                case 0x44:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_H, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                    
                case 0x45:
                    n = GBCPU_readOperationWordParameter();
                    BIT(REG_L, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                    
                case 0x46: {
                    n = GBCPU_readOperationWordParameter();
                    int8_t n2 = GBMemory_getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
                    BIT(n2, n);
                    GBCPU_setFlagZ(ALU_FLAG_Z);
                    GBCPU_setFlagN(0);
                    GBCPU_setFlagH(1);
                    break;
                }
                    
                    
                //SET b,r
                case 0xC7:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_A, n);
                    break;
                    
                case 0xC0:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_B, n);
                    break;
                    
                case 0xC1:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_C, n);
                    break;
                    
                case 0xC2:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_D, n);
                    break;
                    
                case 0xC3:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_E, n);
                    break;
                    
                case 0xC4:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_H, n);
                    break;
                    
                case 0xC5:
                    n = GBCPU_readOperationWordParameter();
                    SET(&REG_L, n);
                    break;
                    
                case 0xC6: {
                    n = GBCPU_readOperationWordParameter();
                    int8_t n2 = GBMemory_getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SET(&n2, n);
                    break;
                }
                    
                //RES b,r
                case 0x87:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_A, n);
                    break;
                    
                case 0x80:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_B, n);
                    break;
                    
                case 0x81:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_C, n);
                    break;
                    
                case 0x82:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_D, n);
                    break;
                    
                case 0x83:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_E, n);
                    break;
                    
                case 0x84:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_H, n);
                    break;
                    
                case 0x85:
                    n = GBCPU_readOperationWordParameter();
                    RES(&REG_L, n);
                    break;
                    
                case 0x86: {
                    n = GBCPU_readOperationWordParameter();
                    int8_t n2 = GBMemory_getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RES(&n2, n);
                    break;
                }
                    
                default:
                    break;
            }
            
        }
            
        //DAA
        case 0x27:
            DAA();
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        //CPL
        case 0x2F:
            CPL();
            GBCPU_setFlagN(1);
            GBCPU_setFlagH(1);
            break;
            
        //CCF
        case 0x3F:
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(!GBCPU_getFlagC());
            break;
        
        //SCF
        case 0x37:
            GBCPU_setFlagN(0);
            GBCPU_setFlagH(0);
            GBCPU_setFlagC(1);
            break;
        
        //NOP
        case 0x00:
            break;
            
        //HALT
        case 0x76:
            GBCPU_setHalt(1);
            break;
            
        case 0x10: {
            
            uint8_t opCode2 = GBCPU_readOperationWordParameter();
            switch (opCode2) {
                //STOP
                case 0x00:
                    GBCPU_setStop(1);
                    break;
                default:
                    break;
            }
        }
            
        //DI
        case 0xF3:
            GBCPU_setInterruptsEnabled(0);
            break;
        
        //EI
        case 0xFB:
            GBCPU_setInterruptsEnabled(1);
            break;
            
        //RLCA
        case 0x07:
            RLC(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagH(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        //RLA
        case 0x17:
            RL(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagH(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
            
        //RRCA
        case 0x0F:
            RRC(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagH(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        //RRA
        case 0x1F:
            RR(&REG_A);
            GBCPU_setFlagZ(ALU_FLAG_Z);
            GBCPU_setFlagH(0);
            GBCPU_setFlagN(0);
            GBCPU_setFlagC(ALU_FLAG_C);
            break;
        
        //Jumps
        //JP nn
        case 0xC3:
            nn = GBCPU_readOperationDwordParameter();
            //TODO: checkear si es esto
            REG_PC = nn;
            break;
        
        //JP cc, nn
        case 0xC2:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagZ() == 0) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xCA:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagZ() == 1) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xD2:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagC() == 0) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xDA:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagC() == 1) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
        
        //JP (HL)
        case 0xE9:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            REG_PC = nn;
            break;
        
        //JR n
        case 0x18:
            n = GBCPU_readOperationWordParameter();
            REG_PC += n;
            break;
        
        //JR cc, n
        case 0x20:
            n = GBCPU_readOperationWordParameter();
            if (GBCPU_getFlagZ() == 0) {
                REG_PC += n;
            }
            break;
            
        case 0x28:
            n = GBCPU_readOperationWordParameter();
            if (GBCPU_getFlagZ() == 1) {
                REG_PC += n;
            }
            break;
            
        case 0x30:
            n = GBCPU_readOperationWordParameter();
            if (GBCPU_getFlagC() == 0) {
                REG_PC += n;
            }
            break;
            
        case 0x38:
            n = GBCPU_readOperationWordParameter();
            if (GBCPU_getFlagC() == 1) {
                REG_PC += n;
            }
            break;
            
        //CALL nn
        case 0xCD:
            nn = GBCPU_readOperationDwordParameter();
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = nn;
            break;
            
        //CALL cc, nn
        case 0xC4:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagZ() == 0) {
                GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xCC:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagZ() == 1) {
                GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xD4:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagC() == 0) {
                GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xDD:
            nn = GBCPU_readOperationDwordParameter();
            if (GBCPU_getFlagC() == 1) {
                GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        //RST n
        case 0xC7:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x00;
            break;
        
        case 0xCF:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x08;
            break;
            
        case 0xD7:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x10;
            break;
            
        case 0xDF:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x08;
            break;
            
        case 0xE7:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x20;
            break;
            
        case 0xEF:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x28;
            break;
            
        case 0xF7:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x30;
            break;
            
        case 0xFF:
            GBMemory_writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x38;
            break;
            
        //RET
        case 0xC9:
            //TODO: mirar little, big endian
            REG_PC = GBMemory_getDwordAt(REG_SP);
            REG_SP += 2;
            break;
            
        //RET cc
        case 0xC0:
            //TODO: mirar little, big endian
            if (GBCPU_getFlagZ() == 0) {
                REG_PC = GBMemory_getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xC8:
            //TODO: mirar little, big endian
            if (GBCPU_getFlagZ() == 1) {
                REG_PC = GBMemory_getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xD0:
            //TODO: mirar little, big endian
            if (GBCPU_getFlagC() == 0) {
                REG_PC = GBMemory_getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xD8:
            //TODO: mirar little, big endian
            if (GBCPU_getFlagC() == 1) {
                REG_PC = GBMemory_getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        
        //RETI
        case 0xD9:
            REG_PC = GBMemory_getDwordAt(REG_SP);
            REG_SP += 2;
            GBCPU_setInterruptsEnabled(true);
            break;
            
        default:
            break;
    }
}
