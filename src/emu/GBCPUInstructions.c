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
#include "GBCPUInstructions.h"
#include "GBMemory.h"

//----------------------------------------------//
//                                              //
//                 CPU Commands                 //
//                                              //
//----------------------------------------------//

void setUp(void)
{
    //TODO: setup registers initial values
    REG_SP = 0xFFFE;
}

void shutDown(void)
{
    
}

void cycle(void)
{
    uint8_t opCode = 0; //TODO: read opcode from memory
    int8_t n = 0;
    int16_t nn = 0;
    
    switch (opCode) {
            //8-Bit loads
        case 0x06:
            n = readOperationByteParameter();
            LD(&REG_B, n);
            break;
        case 0x0E:
            n = readOperationByteParameter();
            LD(&REG_C, n);
            break;
        case 0x16:
            n = readOperationByteParameter();
            LD(&REG_D, n);
            break;
        case 0x1E:
            n = readOperationByteParameter();
            LD(&REG_E, n);
            break;
        case 0x26:
            n = readOperationByteParameter();
            LD(&REG_H, n);
            break;
        case 0x2E:
            n = readOperationByteParameter();
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
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
            n = getByteAt(REG_HL);
            LD(&REG_L, n);
            break;
            
        case 0x70:
            writeByteAt(REG_HL, REG_B);
            break;
        case 0x71:
            writeByteAt(REG_HL, REG_C);
            break;
        case 0x72:
            writeByteAt(REG_HL, REG_D);
            break;
        case 0x73:
            writeByteAt(REG_HL, REG_E);
            break;
        case 0x74:
            writeByteAt(REG_HL, REG_H);
            break;
        case 0x75:
            writeByteAt(REG_HL, REG_L);
            break;
        case 0x36:
            n = readOperationByteParameter();
            writeByteAt(REG_HL, n);
            break;
            
            //LD A, n
        case 0x0A:
            n = getByteAt(REG_BC);
            LD(&REG_A, n);
            break;
        case 0x1A:
            n = getByteAt(REG_DE);
            LD(&REG_A, n);
            break;
        case 0xFA:
            //TODO: mirar si big endian o little endian
            nn = readOpertionWordParameter();
            n = getByteAt(nn);
            LD(&REG_A, n);
            break;
        case 0x3E:
            //TODO: A, # <- que significa esto??
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
            writeByteAt(REG_BC, REG_A);
            break;
        case 0x12:
            writeByteAt(REG_DE, REG_A);
            break;
        case 0x77:
            writeByteAt(REG_HL, REG_A);
            break;
        case 0xEA:
            nn = readOpertionWordParameter();
            writeByteAt(nn, REG_A);
            break;
            
            //LD A, (C)
        case 0xF2:
            n = getByteAt(0xFF00 + REG_C);
            LD(&REG_A, n);
            break;
            
            //LD (C), A
        case 0xE2:
            writeByteAt(0xFF00 + REG_C, REG_A);
            break;
            
            //LDD A, (HL)
        case 0x3A:
            n = getByteAt(REG_HL);
            LD(&REG_A, n);
            //TODO: DEC HL
            break;
            
            //LDD (HL), A
        case 0x32:
            writeByteAt(REG_HL, REG_A);
            //TODO: DEC HL
            break;
            
            //LDI A, (HL)
        case 0x2A:
            n = getByteAt(REG_HL);
            LD(&REG_A, n);
            //TODO: INC HL
            break;
            
            //LDI (HL), A
        case 0x22:
            writeByteAt(REG_HL, REG_A);
            //TODO: INC HL
            break;
            
            //LDH (n), A
        case 0xE0:
            n = readOperationByteParameter();
            writeByteAt(0xFF00 + n, REG_A);
            break;
            
            //LDH A, (n)
        case 0xF0:
            n = readOperationByteParameter();
            n = getByteAt(0xFF00 + n);
            LD(&REG_A, n);
            
            //16-bit ops
            //LD n, nn
        case 0x01:
            nn = readOpertionWordParameter();
            LD16HL(&REG_B, &REG_C, nn);
            break;
        case 0x11:
            nn = readOpertionWordParameter();
            LD16HL(&REG_D, &REG_E, nn);
            break;
        case 0x21:
            nn = readOpertionWordParameter();
            LD16HL(&REG_H, &REG_L, nn);
            break;
        case 0x31:
            nn = readOpertionWordParameter();
            LD16(&REG_SP, nn);
            break;
            
            //LD SP, HL
        case 0xF9:
            LD16(&REG_SP, REG_HL);
            break;
            
            //LDHL SP, n
        case 0xF8:
            n = readOperationByteParameter();
            LD16HL(&REG_H, &REG_L, REG_SP + n);
            //TODO: setear flags...
            break;
            
            //LD (nn), SP
        case 0x08:
            nn = readOpertionWordParameter();
            writeWordAt(nn, REG_SP);
            break;
            
            //PUSH nn
            //TODO: push register pair into stack
            //decrement stack pointer twice
        case 0xF5:
            writeWordAt(REG_SP, REG_AF);
            //TODO: INC REG_SP (x2)
            break;
        case 0xC5:
            writeWordAt(REG_SP, REG_AF);
            //TODO: INC REG_SP (x2)
            break;
        case 0xD5:
            writeWordAt(REG_SP, REG_AF);
            //TODO: INC REG_SP (x2)
            break;
        case 0xE5:
            writeWordAt(REG_SP, REG_AF);
            //TODO: INC REG_SP (x2)
            break;
            
            //POP nn
            //TODO: pop two bytes off stack into register pair nn
            //Increment stack pointer twice
        case 0xF1:
            nn = getByteAt(REG_SP);
            REG_A = nn & 0xFF00;
            REG_F = nn & 0x00FF;
            //TODO: INC REG_SP (x2)
            break;
        case 0xC1:
            nn = getByteAt(REG_SP);
            REG_B = nn & 0xFF00;
            REG_C = nn & 0x00FF;
            //TODO: INC REG_SP (x2)
            break;
        case 0xD1:
            nn = getByteAt(REG_SP);
            REG_D = nn & 0xFF00;
            REG_E = nn & 0x00FF;
            //TODO: INC REG_SP (x2)
            break;
        case 0xE1:
            nn = getByteAt(REG_SP);
            REG_H = nn & 0xFF00;
            REG_L = nn & 0x00FF;
            //TODO: INC REG_SP (x2)
            break;
        default:
            break;
    }
}


uint8_t readOperationByteParameter(void)
{
    uint8_t result = getByteAt(++REG_PC);
    return result;
}

uint16_t readOpertionWordParameter(void)
{
    //TODO: little endian o big endian?
    uint16_t result;
    uint8_t nH = getByteAt(++REG_PC);
    uint8_t nL = getByteAt(++REG_PC);
    result = ((0xFF00 & nH <<8) | (0x00FF & nL));
    
    return result;
}
