//
//  GBCPUInstructions.c
//  GBEmu
//
//  Created by Jesús on 02/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdio.h>
#include <stdint.h>

#include "GBMacros.h"
#include "GBCPU.h"
#include "GBCPU_ALU.h"
#include "GBMemory.h"
#include "GBUtils.h"

//----------------------------------------------//
//                                              //
//                  Helpers                     //
//                                              //
//----------------------------------------------//

void LD (int8_t *r, int8_t n)
{
    *r = n;
}

void LD16 (int16_t *rr, int16_t nn)
{
    *rr = nn;
}

void LD16_HL (int8_t *rh, int8_t *rl, int16_t nn)
{
    *rl = (0xFF & ((nn) >> 8));
    *rh = 0xFF & (nn);
}

void INC16_HL (int8_t *rh, int8_t *rl)
{
    int16_t r = DWORD_FROM_HL(*rh, *rl);
    INC16(&r);
    LD16_HL(rh, rl, r);
}

void DEC16_HL (int8_t *rh, int8_t *rl)
{
    int16_t r = DWORD_FROM_HL(*rh, *rl);
    DEC16(&r);
    LD16_HL(rh, rl, r);
}

bool getFlagZ()
{
    return bitAtIndex(REG_F, 7);
}

void setFlagZ(bool z)
{
    setBitAtIndex(&REG_F, 7, z);
}

bool getFlagN()
{
    return bitAtIndex(REG_F, 6);
}

void setFlagN(bool n)
{
    setBitAtIndex(&REG_F, 6, n);
}

bool getFlagH()
{
    return bitAtIndex(REG_F, 5);
}

void setFlagH(bool h)
{
    setBitAtIndex(&REG_F, 5, h);
}

bool getFlagC()
{
   return bitAtIndex(REG_F, 4);
}

void setFlagC(bool c)
{
    setBitAtIndex(&REG_F, 4, c);
}


void setHalt(bool halt)
{
    FLAGS_HALT = halt;
}

void setStop(bool stop)
{
    FLAGS_STOP = stop;
}

void setInterruptsEnabled(bool enabled)
{
    FLAGS_IE = enabled;
}


void setUp(void)
{
    //TODO: setup registers initial values
    REG_SP = 0xFFFE;
    
    FLAGS_IE = true;
    FLAGS_STOP = false;
    FLAGS_HALT = false;
}

void shutDown(void)
{
    
}

void nextOperation(void)
{
    uint8_t opCode = getWordAt(REG_PC++);
    int8_t n = 0;
    int16_t nn = 0;
    
    switch (opCode) {
            //8-Bit loads
        case 0x06:
            n = readOperationWordParameter();
            LD(&REG_B, n);
            break;
        case 0x0E:
            n = readOperationWordParameter();
            LD(&REG_C, n);
            break;
        case 0x16:
            n = readOperationWordParameter();
            LD(&REG_D, n);
            break;
        case 0x1E:
            n = readOperationWordParameter();
            LD(&REG_E, n);
            break;
        case 0x26:
            n = readOperationWordParameter();
            LD(&REG_H, n);
            break;
        case 0x2E:
            n = readOperationWordParameter();
            LD(&REG_L, n);
            break;
            
            //LD r1, r2
        case 0x7F:
            LD(&REG_A, REG_A);
            break;
        case 0x78:
            LD(&REG_A, REG_B);
            break;
        case 0x79:
            LD(&REG_A, REG_C);
            break;
        case 0x7A:
            LD(&REG_A, REG_D);
            break;
        case 0x7B:
            LD(&REG_A, REG_E);
            break;
        case 0x7C:
            LD(&REG_A, REG_H);
            break;
        case 0x7D:
            LD(&REG_A, REG_L);
            break;
        case 0x7E:
            n = getWordAt(REG_HL);
            LD(&REG_A, n);
            break;
            
        case 0x40:
            LD(&REG_B, REG_B);
            break;
        case 0x41:
            LD(&REG_B, REG_C);
            break;
        case 0x42:
            LD(&REG_B, REG_D);
            break;
        case 0x43:
            LD(&REG_B, REG_E);
            break;
        case 0x44:
            LD(&REG_B, REG_H);
            break;
        case 0x45:
            LD(&REG_B, REG_L);
            break;
        case 0x46:
            n = getWordAt(REG_HL);
            LD(&REG_B, n);
            break;
            
        case 0x48:
            LD(&REG_C, REG_B);
            break;
        case 0x49:
            LD(&REG_C, REG_C);
            break;
        case 0x4A:
            LD(&REG_C, REG_D);
            break;
        case 0x4B:
            LD(&REG_C, REG_E);
            break;
        case 0x4C:
            LD(&REG_C, REG_H);
            break;
        case 0x4D:
            LD(&REG_C, REG_L);
            break;
        case 0x4E:
            n = getWordAt(REG_HL);
            LD(&REG_C, n);
            break;
            
        case 0x50:
            LD(&REG_D, REG_B);
            break;
        case 0x51:
            LD(&REG_D, REG_C);
            break;
        case 0x52:
            LD(&REG_D, REG_D);
            break;
        case 0x53:
            LD(&REG_D, REG_E);
            break;
        case 0x54:
            LD(&REG_D, REG_H);
            break;
        case 0x55:
            LD(&REG_D, REG_L);
            break;
        case 0x56:
            n = getWordAt(REG_HL);
            LD(&REG_D, n);
            break;
            
        case 0x58:
            LD(&REG_E, REG_B);
            break;
        case 0x59:
            LD(&REG_E, REG_C);
            break;
        case 0x5A:
            LD(&REG_E, REG_D);
            break;
        case 0x5B:
            LD(&REG_E, REG_E);
            break;
        case 0x5C:
            LD(&REG_E, REG_H);
            break;
        case 0x5D:
            LD(&REG_E, REG_L);
            break;
        case 0x5E:
            n = getWordAt(REG_HL);
            LD(&REG_E, n);
            break;
            
        case 0x60:
            LD(&REG_H, REG_B);
            break;
        case 0x61:
            LD(&REG_H, REG_C);
            break;
        case 0x62:
            LD(&REG_H, REG_D);
            break;
        case 0x63:
            LD(&REG_H, REG_E);
            break;
        case 0x64:
            LD(&REG_H, REG_H);
            break;
        case 0x65:
            LD(&REG_H, REG_L);
            break;
        case 0x66:
            n = getWordAt(REG_HL);
            LD(&REG_H, n);
            break;
            
        case 0x68:
            LD(&REG_L, REG_B);
            break;
        case 0x69:
            LD(&REG_L, REG_C);
            break;
        case 0x6A:
            LD(&REG_L, REG_D);
            break;
        case 0x6B:
            LD(&REG_L, REG_E);
            break;
        case 0x6C:
            LD(&REG_L, REG_H);
            break;
        case 0x6D:
            LD(&REG_L, REG_L);
            break;
        case 0x6E:
            n = getWordAt(REG_HL);
            LD(&REG_L, n);
            break;
            
        case 0x70:
            writeWordAt(REG_HL, REG_B);
            break;
        case 0x71:
            writeWordAt(REG_HL, REG_C);
            break;
        case 0x72:
            writeWordAt(REG_HL, REG_D);
            break;
        case 0x73:
            writeWordAt(REG_HL, REG_E);
            break;
        case 0x74:
            writeWordAt(REG_HL, REG_H);
            break;
        case 0x75:
            writeWordAt(REG_HL, REG_L);
            break;
        case 0x36:
            n = readOperationWordParameter();
            writeWordAt(REG_HL, n);
            break;
            
            //LD A, n
        case 0x0A:
            n = getWordAt(REG_BC);
            LD(&REG_A, n);
            break;
        case 0x1A:
            n = getWordAt(REG_DE);
            LD(&REG_A, n);
            break;
        case 0xFA:
            //TODO: mirar si big endian o little endian
            nn = readOpertionDwordParameter();
            n = getWordAt(nn);
            LD(&REG_A, n);
            break;
        case 0x3E:
            n = readOperationWordParameter();
            LD(&REG_A, n);
            break;
            
            //LD n, A
        case 0x47:
            LD(&REG_B, REG_A);
            break;
        case 0x4F:
            LD(&REG_C, REG_A);
            break;
        case 0x57:
            LD(&REG_D, REG_A);
            break;
        case 0x5F:
            LD(&REG_E, REG_A);
            break;
        case 0x67:
            LD(&REG_H, REG_A);
            break;
        case 0x6F:
            LD(&REG_L, REG_A);
            break;
        case 0x02:
            writeWordAt(REG_BC, REG_A);
            break;
        case 0x12:
            writeWordAt(REG_DE, REG_A);
            break;
        case 0x77:
            writeWordAt(REG_HL, REG_A);
            break;
        case 0xEA:
            nn = readOpertionDwordParameter();
            writeWordAt(nn, REG_A);
            break;
            
            //LD A, (C)
        case 0xF2:
            n = getWordAt(0xFF00 + REG_C);
            LD(&REG_A, n);
            break;
            
            //LD (C), A
        case 0xE2:
            writeWordAt(0xFF00 + REG_C, REG_A);
            break;
            
            //LDD A, (HL)
        case 0x3A:
            n = getWordAt(REG_HL);
            LD(&REG_A, n);
            DEC16_HL(&REG_H, &REG_L);
            break;
            
            //LDD (HL), A
        case 0x32:
            writeWordAt(REG_HL, REG_A);
            DEC16_HL(&REG_H, &REG_L);
            break;
            
            //LDI A, (HL)
        case 0x2A: 
            n = getWordAt(REG_HL);
            LD(&REG_A, n);
            INC16_HL(&REG_H, &REG_L);
            break;
            
            //LDI (HL), A
        case 0x22:
            writeWordAt(REG_HL, REG_A);
            INC16_HL(&REG_H, &REG_L);
            break;
            
            //LDH (n), A
        case 0xE0:
            n = readOperationWordParameter();
            writeWordAt(0xFF00 + n, REG_A);
            break;
            
            //LDH A, (n)
        case 0xF0:
            n = readOperationWordParameter();
            n = getWordAt(0xFF00 + n);
            LD(&REG_A, n);
            
            //16-bit ops
            //LD n, nn
        case 0x01:
            nn = readOpertionDwordParameter();
            LD16_HL(&REG_B, &REG_C, nn);
            break;
        case 0x11:
            nn = readOpertionDwordParameter();
            LD16_HL(&REG_D, &REG_E, nn);
            break;
        case 0x21:
            nn = readOpertionDwordParameter();
            LD16_HL(&REG_H, &REG_L, nn);
            break;
        case 0x31:
            nn = readOpertionDwordParameter();
            LD16(&REG_SP, nn);
            break;
            
            //LD SP, HL
        case 0xF9:
            LD16(&REG_SP, REG_HL);
            break;
            
            //LDHL SP, n
        case 0xF8: {
            n = readOperationWordParameter();
            
            int16_t nn = REG_SP;
            ADD16(&nn, n);
            LD16_HL(&REG_H, &REG_L, nn);
            setFlagZ(0);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            
            break;
        }
            
            //LD (nn), SP
        case 0x08:
            nn = readOpertionDwordParameter();
            writeDwordAt(nn, REG_SP);
            break;
            
            //PUSH nn
        case 0xF5:
            writeDwordAt(REG_SP, REG_AF);
            REG_SP -= 2;
            break;
        case 0xC5:
            writeDwordAt(REG_SP, REG_BC);
            REG_SP -= 2;
            break;
        case 0xD5:
            writeDwordAt(REG_SP, REG_DE);
            REG_SP -= 2;
            break;
        case 0xE5:
            writeDwordAt(REG_SP, REG_HL);
            REG_SP -= 2;
            break;
            
            //POP nn
        case 0xF1:
            nn = getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_A, &REG_F);
            REG_SP += 2;
            break;
        case 0xC1:
            nn = getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_B, &REG_C);
            REG_SP += 2;
            break;
        case 0xD1:
            nn = getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_D, &REG_E);
            REG_SP += 2;
            break;
        case 0xE1:
            nn = getDwordAt(REG_SP);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            REG_SP += 2;
            break;
            
            //ADD A, n
        case 0x87:
            ADD(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
        
        case 0x80:
            ADD(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
        
        case 0x81:
            ADD(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
        
        case 0x82:
            ADD(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
        
        case 0x84:
            ADD(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x85:
            ADD(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x86:
            n = getWordAt(REG_HL);
            ADD(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0xC6:
            n = readOperationWordParameter();
            ADD(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        //ADC A,n
        case 0x8F:
            ADD(REG_A + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x88:
            ADD(REG_B + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x89:
            ADD(REG_C + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8A:
            ADD(REG_D + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8B:
            ADD(REG_E + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8C:
            ADD(REG_H + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8D:
            ADD(REG_L + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x8E:
            n = getWordAt(REG_HL);
            ADD(n + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0xCE:
            n = readOperationWordParameter();
            ADD(n + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        //SUB n
        case 0x97:
            SUB(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x90:
            SUB(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x91:
            SUB(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x92:
            SUB(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x93:
            SUB(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x94:
            SUB(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x95:
            SUB(REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x96:
            n = getWordAt(REG_HL);
            SUB(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0xD6:
            n = readOperationWordParameter();
            SUB(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        //SUBC n
        case 0x9F:
            SUB(REG_A + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x98:
            SUB(REG_B + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x99:
            SUB(REG_C + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9A:
            SUB(REG_D + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9B:
            SUB(REG_E + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9C:
            SUB(REG_H + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9D:
            SUB(REG_L + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
        case 0x9E:
            n = getWordAt(REG_HL);
            SUB(n + getFlagC());
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagN(ALU_FLAG_N);
            break;
            
//        case 0x??:
//            n = readOperationWordParameter();
//            SUB(n  + getFlagC());
//            setFlagZ(ALU_FLAG_Z);
//            setFlagN(1);
//            setFlagH(ALU_FLAG_H);
//            setFlagN(ALU_FLAG_N);
//            break;
            
        //AND n
        case 0xA7:
            AND(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
        
        case 0xA0:
            AND(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA1:
            AND(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA2:
            AND(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA3:
            AND(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA4:
            AND(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA5:
            AND(REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xA6:
            n = getWordAt(REG_HL);
            AND(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xE6:
            n = readOperationWordParameter();
            AND(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
        
        //OR n
        case 0xB7:
            OR(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB0:
            OR(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB1:
            OR(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB2:
            OR(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB3:
            OR(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB4:
            OR(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xB5:
            OR(REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xB6:
            n = getWordAt(REG_HL);
            OR(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xF6:
            n = readOperationWordParameter();
            OR(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
        
        //XOR n
        case 0xAF:
            XOR(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xA8:
            XOR(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xA9:
            XOR(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xAA:
            XOR(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xAB:
            XOR(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xAC:
            XOR(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xAD:
            XOR(REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(1);
            setFlagC(0);
            break;
            
        case 0xAE:
            n = getWordAt(REG_HL);
            XOR(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        case 0xEE:
            n = readOperationWordParameter();
            XOR(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(0);
            setFlagC(0);
            break;
            
        //CP n
        case 0xBF:
            CP(REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
        
        case 0xB8:
            CP(REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xB9:
            CP(REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBA:
            CP(REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBB:
            CP(REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBC:
            CP(REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBD:
            CP(REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xBE:
            n = getWordAt(REG_HL);
            CP(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0xFE:
            n = readOperationWordParameter();
            CP(n);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        //INC n
        case 0x3C:
            INC(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x04:
            INC(&REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x0C:
            INC(&REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x14:
            INC(&REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x1C:
            INC(&REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x24:
            INC(&REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x2C:
            INC(&REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x34:
            n = getWordAt(REG_HL);
            INC(&n);
            writeWordAt(REG_HL, n);
            
            setFlagZ(ALU_FLAG_Z);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            break;
        
        //DEC n
        case 0x3D:
            DEC(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x05:
            DEC(&REG_B);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x0D:
            DEC(&REG_C);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x15:
            DEC(&REG_D);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x1D:
            DEC(&REG_E);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x25:
            DEC(&REG_H);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x2D:
            DEC(&REG_L);
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
            
        case 0x35:
            n = getWordAt(REG_HL);
            DEC(&n);
            writeWordAt(REG_HL, n);
            
            setFlagZ(ALU_FLAG_Z);
            setFlagN(1);
            setFlagH(ALU_FLAG_H);
            break;
        
        //ADD HL, n
        case 0x09:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_B, REG_C));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
        
        case 0x19:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_D, REG_E));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0x29:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, DWORD_FROM_HL(REG_H, REG_L));
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        case 0x39:
            nn = DWORD_FROM_HL(REG_H, REG_L);
            ADD16(&nn, REG_SP);
            HL_FROM_DWORD(nn, &REG_H, &REG_L);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            break;
            
        //ADD SP, n
        case 0xE8:
            n = readOperationWordParameter();
            ADD16(&REG_SP, n);
            setFlagZ(0);
            setFlagN(0);
            setFlagH(ALU_FLAG_H);
            setFlagC(ALU_FLAG_C);
            
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
            
            uint8_t opCode2 = readOperationWordParameter();
            
            switch (opCode2) {
                //SWAP n
                case 0x37:
                    SWAP(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x30:
                    SWAP(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x31:
                    SWAP(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x32:
                    SWAP(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x33:
                    SWAP(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x34:
                    SWAP(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x35:
                    SWAP(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                    
                case 0x36:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SWAP(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(0);
                    break;
                
                    
                //RLC n
                case 0x07:
                    RLC(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                
                case 0x00:
                    RLC(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                
                case 0x01:
                    RLC(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x02:
                    RLC(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x03:
                    RLC(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x04:
                    RLC(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x05:
                    RLC(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x06:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RLC(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                //RL n
                case 0x17:
                    RL(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x10:
                    RL(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x11:
                    RL(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x12:
                    RL(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x13:
                    RL(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x14:
                    RL(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x15:
                    RL(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x16:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RL(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                //RRC n
                case 0x0F:
                    RRC(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x08:
                    RRC(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x09:
                    RRC(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0A:
                    RRC(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0B:
                    RRC(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0C:
                    RRC(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0D:
                    RRC(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x0E:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RRC(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                
                //RR n
                case 0x1F:
                    RR(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x18:
                    RR(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x19:
                    RR(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1A:
                    RR(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1B:
                    RR(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1C:
                    RR(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1D:
                    RR(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x1E:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    RR(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                //SLA n
                case 0x27:
                    SLA(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x20:
                    SLA(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x21:
                    SLA(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x22:
                    SLA(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x23:
                    SLA(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x24:
                    SLA(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x25:
                    SLA(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x26:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SLA(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                
                //SRA n
                case 0x2F:
                    SRA(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x28:
                    SRA(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x29:
                    SRA(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2A:
                    SRA(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2B:
                    SRA(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2C:
                    SRA(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2D:
                    SRA(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x2E:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SRA(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                
                //SRL n
                case 0x3F:
                    SRL(&REG_A);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x38:
                    SRL(&REG_B);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x39:
                    SRL(&REG_C);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3A:
                    SRL(&REG_D);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3B:
                    SRL(&REG_E);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3C:
                    SRL(&REG_H);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3D:
                    SRL(&REG_L);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                case 0x3E:
                    n = getWordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SRL(&n);
                    writeWordAt(DWORD_FROM_HL(REG_H, REG_L), n);
                    
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(0);
                    setFlagC(ALU_FLAG_C);
                    break;
                    
                //BIT b,r
                case 0x47:
                    n = readOperationWordParameter();
                    BIT(REG_A, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                
                case 0x40:
                    n = readOperationWordParameter();
                    BIT(REG_B, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                
                case 0x41:
                    n = readOperationWordParameter();
                    BIT(REG_C, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                    
                case 0x42:
                    n = readOperationWordParameter();
                    BIT(REG_D, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                    
                case 0x43:
                    n = readOperationWordParameter();
                    BIT(REG_E, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                    
                case 0x44:
                    n = readOperationWordParameter();
                    BIT(REG_H, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                    
                case 0x45:
                    n = readOperationWordParameter();
                    BIT(REG_L, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                    
                case 0x46: {
                    n = readOperationWordParameter();
                    int8_t n2 = getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
                    BIT(n2, n);
                    setFlagZ(ALU_FLAG_Z);
                    setFlagN(0);
                    setFlagH(1);
                    break;
                }
                    
                    
                //SET b,r
                case 0xC7:
                    n = readOperationWordParameter();
                    SET(&REG_A, n);
                    break;
                    
                case 0xC0:
                    n = readOperationWordParameter();
                    SET(&REG_B, n);
                    break;
                    
                case 0xC1:
                    n = readOperationWordParameter();
                    SET(&REG_C, n);
                    break;
                    
                case 0xC2:
                    n = readOperationWordParameter();
                    SET(&REG_D, n);
                    break;
                    
                case 0xC3:
                    n = readOperationWordParameter();
                    SET(&REG_E, n);
                    break;
                    
                case 0xC4:
                    n = readOperationWordParameter();
                    SET(&REG_H, n);
                    break;
                    
                case 0xC5:
                    n = readOperationWordParameter();
                    SET(&REG_L, n);
                    break;
                    
                case 0xC6: {
                    n = readOperationWordParameter();
                    int8_t n2 = getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
                    SET(&n2, n);
                    break;
                }
                    
                //RES b,r
                case 0x87:
                    n = readOperationWordParameter();
                    RES(&REG_A, n);
                    break;
                    
                case 0x80:
                    n = readOperationWordParameter();
                    RES(&REG_B, n);
                    break;
                    
                case 0x81:
                    n = readOperationWordParameter();
                    RES(&REG_C, n);
                    break;
                    
                case 0x82:
                    n = readOperationWordParameter();
                    RES(&REG_D, n);
                    break;
                    
                case 0x83:
                    n = readOperationWordParameter();
                    RES(&REG_E, n);
                    break;
                    
                case 0x84:
                    n = readOperationWordParameter();
                    RES(&REG_H, n);
                    break;
                    
                case 0x85:
                    n = readOperationWordParameter();
                    RES(&REG_L, n);
                    break;
                    
                case 0x86: {
                    n = readOperationWordParameter();
                    int8_t n2 = getDwordAt(DWORD_FROM_HL(REG_H, REG_L));
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
            setFlagZ(ALU_FLAG_Z);
            setFlagH(0);
            setFlagC(ALU_FLAG_C);
            break;
        
        //CPL
        case 0x2F:
            CPL();
            setFlagN(1);
            setFlagH(1);
            break;
            
        //CCF
        case 0x3F:
            setFlagN(0);
            setFlagH(0);
            setFlagC(!getFlagC());
            break;
        
        //SCF
        case 0x37:
            setFlagN(0);
            setFlagH(0);
            setFlagC(1);
            break;
        
        //NOP
        case 0x00:
            break;
            
        //HALT
        case 0x76:
            setHalt(1);
            break;
            
        case 0x10: {
            
            uint8_t opCode2 = readOperationWordParameter();
            switch (opCode2) {
                //STOP
                case 0x00:
                    setStop(1);
                    break;
                default:
                    break;
            }
        }
            
        //DI
        case 0xF3:
            setInterruptsEnabled(0);
            break;
        
        //EI
        case 0xFB:
            setInterruptsEnabled(1);
            break;
            
        //RLCA
        case 0x07:
            RLC(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagH(0);
            setFlagN(0);
            setFlagC(ALU_FLAG_C);
            break;
        
        //RLA
        case 0x17:
            RL(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagH(0);
            setFlagN(0);
            setFlagC(ALU_FLAG_C);
            break;
            
        //RRCA
        case 0x0F:
            RRC(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagH(0);
            setFlagN(0);
            setFlagC(ALU_FLAG_C);
            break;
        
        //RRA
        case 0x1F:
            RR(&REG_A);
            setFlagZ(ALU_FLAG_Z);
            setFlagH(0);
            setFlagN(0);
            setFlagC(ALU_FLAG_C);
            break;
        
        //Jumps
        //JP nn
        case 0xC3:
            //TODO: check little-big endian
            nn = readOpertionDwordParameter();
            //TODO: checkear si es esto
            REG_PC = nn;
            break;
        
        //JP cc, nn
        case 0xC2:
            nn = readOpertionDwordParameter();
            if (getFlagZ() == 0) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xCA:
            nn = readOpertionDwordParameter();
            if (getFlagZ() == 1) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xD2:
            nn = readOpertionDwordParameter();
            if (getFlagC() == 0) {
                //TODO: checkear si es esto
                REG_PC = nn;
            }
            break;
            
        case 0xDA:
            nn = readOpertionDwordParameter();
            if (getFlagC() == 1) {
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
            n = readOperationWordParameter();
            REG_PC += n;
            break;
        
        //JR cc, n
        case 0x20:
            n = readOperationWordParameter();
            if (getFlagZ() == 0) {
                REG_PC += n;
            }
            break;
            
        case 0x28:
            n = readOperationWordParameter();
            if (getFlagZ() == 1) {
                REG_PC += n;
            }
            break;
            
        case 0x30:
            n = readOperationWordParameter();
            if (getFlagC() == 0) {
                REG_PC += n;
            }
            break;
            
        case 0x38:
            n = readOperationWordParameter();
            if (getFlagC() == 1) {
                REG_PC += n;
            }
            break;
            
        //CALL nn
        case 0xCD:
            //TODO: mirar little, big endian
            nn = readOpertionDwordParameter();
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = nn;
            break;
            
        //CALL cc, nn
        case 0xC4:
            //TODO: mirar little, big endian
            nn = readOpertionDwordParameter();
            if (getFlagZ() == 0) {
                writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xCC:
            //TODO: mirar little, big endian
            nn = readOpertionDwordParameter();
            if (getFlagZ() == 1) {
                writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xD4:
            //TODO: mirar little, big endian
            nn = readOpertionDwordParameter();
            if (getFlagC() == 0) {
                writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        case 0xDD:
            //TODO: mirar little, big endian
            nn = readOpertionDwordParameter();
            if (getFlagC() == 1) {
                writeDwordAt(REG_SP - 2, REG_PC);
                REG_SP -= 2;
                REG_PC = nn;
            }
            break;
            
        //RST n
        case 0xC7:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x00;
            break;
        
        case 0xCF:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x08;
            break;
            
        case 0xD7:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x10;
            break;
            
        case 0xDF:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x08;
            break;
            
        case 0xE7:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x20;
            break;
            
        case 0xEF:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x28;
            break;
            
        case 0xF7:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x30;
            break;
            
        case 0xFF:
            writeDwordAt(REG_SP - 2, REG_PC);
            REG_SP -= 2;
            REG_PC = 0x38;
            break;
            
        //RET
        case 0xC9:
            //TODO: mirar little, big endian
            REG_PC = getDwordAt(REG_SP);
            REG_SP += 2;
            break;
            
        //RET cc
        case 0xC0:
            //TODO: mirar little, big endian
            if (getFlagZ() == 0) {
                REG_PC = getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xC8:
            //TODO: mirar little, big endian
            if (getFlagZ() == 1) {
                REG_PC = getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xD0:
            //TODO: mirar little, big endian
            if (getFlagC() == 0) {
                REG_PC = getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        case 0xD8:
            //TODO: mirar little, big endian
            if (getFlagC() == 1) {
                REG_PC = getDwordAt(REG_SP);
                REG_SP += 2;
            }
            break;
            
        
        //RETI
        case 0xD9:
            REG_PC = getDwordAt(REG_SP);
            REG_SP += 2;
            setInterruptsEnabled(true);
            break;
            
        default:
            break;
    }
}


int8_t readOperationWordParameter(void)
{
    uint8_t result = getWordAt(REG_PC++);
    return result;
}

int16_t readOpertionDwordParameter(void)
{
    //TODO: little endian o big endian?
    uint16_t result;
    uint8_t nH = getWordAt(REG_PC++);
    uint8_t nL = getWordAt(REG_PC++);
    result = DWORD_FROM_HL(nH, nL);
    
    return result;
}
