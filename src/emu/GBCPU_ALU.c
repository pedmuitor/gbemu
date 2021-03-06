//
//  GBCPU.c
//  GBEmu
//
//  Created by Pedro Muiños on 31/05/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>

#include "GBUtils.h"    
#include "GBCPU.h"
#include "GBCPU_ALU.h"

//----------------------------------------------//
//                                              //
//                  8-Bit ALU                   //
//                                              //
//----------------------------------------------//

//Helpers
void add8(int8_t *r ,int8_t n, bool c, bool hFlag, bool cFlag);
void addA (int8_t n, bool c);
void sub8(int8_t *r ,int8_t n, bool c, bool hFlag, bool cFlag, bool store);
void subA (int8_t n, bool c, bool store);

void add8(int8_t *r ,int8_t n, bool c, bool hFlag, bool cFlag)
{
    if (c) {
        c = GBCPU_getFlagC();
    }
    
    int8_t number    = n + c;
    int8_t rval      = *r;
    int8_t  sum      = rval + number;

    ALU_FLAG_N      = 0;
    ALU_FLAG_Z      = (0 == sum);
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    //Half overflow
    if (hFlag) {
        int8_t hn       = number & 0x0F;
        int8_t hr       = rval & 0x0F;
        int8_t msbn     = bitAtIndex(hn, 3);
        int8_t msbr     = bitAtIndex(hr, 3);
        
        if (msbn ^ msbr) {
            ALU_FLAG_H          = 0;
        }else {
            int8_t msbs         = bitAtIndex((hn + hr) & 0x08, 3);
            ALU_FLAG_H          = (0 != (msbs ^ msbn));
        }
    }
    
    //Overflow
    if (cFlag) {
        int8_t msbn      = moreSignificantBit(number, sizeof(int8_t));
        int8_t msbr      = moreSignificantBit(rval, sizeof(int8_t));

        if (msbn ^ msbr) {
            ALU_FLAG_C      = 0;
        }else {
            int8_t msbs   = moreSignificantBit(sum, sizeof(int8_t));
            ALU_FLAG_C      = (0 != (msbs ^ msbn));
        }
    }
    
    *r  = sum;
    *r &= 0xFF;
}

void addA (int8_t n, bool c)
{
    add8(&(REG_A), n, c, true, true);
}

void sub8(int8_t *r ,int8_t n, bool c, bool hFlag, bool cFlag, bool store)
{
    if (c) {
        c = GBCPU_getFlagC();
    }
    
    int8_t number      = ~(n + c) + 0x01;
    int8_t rval        = *r;
    int8_t sub         = rval + number;
    
    ALU_FLAG_N  = 1;
    ALU_FLAG_Z  = (0 == sub);
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    //Half overflow
    if (hFlag) {
        int8_t hn       = number & 0x0F;
        int8_t hr       = rval & 0x0F;
        int8_t msbn     = bitAtIndex(hn, 3);
        int8_t msbr     = bitAtIndex(hr, 3);
        
        if (msbn ^ msbr) {
            ALU_FLAG_H          = 1;
        }else {
            int8_t msbs         = bitAtIndex((hn + hr) & 0x08, 3);
            ALU_FLAG_H          = (0 == (msbs ^ msbn));
        }
    }
    
    //Overflow
    if (cFlag) {
        int8_t msbn      = moreSignificantBit(number, sizeof(int8_t));
        int8_t msbr      = moreSignificantBit(rval, sizeof(int8_t));
        
        
        if (msbn ^ msbr) {
            ALU_FLAG_C      = 1;
        }else {
            int8_t msbs   = moreSignificantBit(sub, sizeof(int8_t));
            ALU_FLAG_C      = (0 == (msbs ^ msbn));
        }
    }
    
    if (store) {
        *r  = sub;
        *r &= 0xFF;
    }
}

void subA (int8_t n, bool c, bool store)
{
    sub8(&(REG_A), n, c, true, true, store);
}


void ADC (int8_t n)
{
    addA(n, true);
}

void ADD (int8_t n)
{
    addA(n, false);
}

void SUB (int8_t n)
{
    subA(n, false, true);
}

void SBC (int8_t n)
{
    subA(n, true, true);
}

void AND (int8_t n)
{
    REG_A &= n;
    
    ALU_FLAG_Z = (0 == REG_A)? 1:0;
    ALU_FLAG_N  = 0;
    ALU_FLAG_H  = 1;
    ALU_FLAG_C  = 0;
}

void OR (int8_t n)
{
    REG_A |= n;
    
    ALU_FLAG_Z = (0 == REG_A)? 1:0;
    ALU_FLAG_N  = 0;
    ALU_FLAG_H  = 0;
    ALU_FLAG_C  = 0;
}

void XOR (int8_t n)
{
    REG_A ^= n;
   
    ALU_FLAG_Z = (0 == REG_A)? 1:0;
    ALU_FLAG_N  = 0;
    ALU_FLAG_H  = 0;
    ALU_FLAG_C  = 0;
}

void CP (int8_t n)
{
    subA(n, false, false);
}

void INC (int8_t *r)
{
    add8(r, 1, false, true, false);
}

void DEC (int8_t *r)
{
    sub8(r, 1, false, true, false, true);
}

void DAA ()
{
    ALU_FLAG_H  = 0;
    
    uint8_t n    = (uint8_t)REG_A;
    int8_t res  = 0;
    
    int8_t i = 0;
    while (n > 0) {
        res  |= (n % 10) << 4*i;
        n /= 10;
        i++;
    }

    REG_A  = res;
    
    ALU_FLAG_Z = (0 == REG_A)? 1:0;
}

void CPL ()
{
    ALU_FLAG_N = 1;
    ALU_FLAG_H = 1;
    
    REG_A  ^= 0xFF;
}

//----------------------------------------------//
//                                              //
//                  16-Bit ALU                  //
//                                              //
//----------------------------------------------//

//Helpers
void add16 (int16_t *r, int16_t nn);

void add16 (int16_t *r, int16_t nn)
{
    int16_t rVal   = *r;
    int16_t sum    = rVal + nn;
    
    ALU_FLAG_N  = 0;
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    int8_t hl11msb      = bitAtIndex(rVal, 11);
    int8_t nn11msb     = bitAtIndex(nn, 11);
    
    if (hl11msb ^ nn11msb) {
        ALU_FLAG_H  = 0;
    }else {
        int8_t hsum11msb      = bitAtIndex(sum, 11);
        ALU_FLAG_H  = (0 != (hsum11msb ^ nn11msb));
    }
    
    int8_t hlmsb = bitAtIndex(rVal, 15);
    int8_t nnmsb = bitAtIndex(nn, 15);
    
    if (hlmsb ^ nnmsb) {
        ALU_FLAG_C  = 0;
    }else {
        int8_t summsb = bitAtIndex(sum, 15);
        ALU_FLAG_C = (0 != (summsb ^nnmsb));
    }
    
    *r = sum;
    *r &= 0xFFFF;
}

void ADD16 (int16_t* rr, int16_t nn)
{    
    add16(rr, nn);
}

void INC16 (int16_t* rr)
{
    (*rr) += 1;
}

void DEC16 (int16_t* rr)
{
    (*rr) -= 1;
}

//----------------------------------------------//
//                                              //
//                Rotates & Shifts              //
//                                              //
//----------------------------------------------//

void RL (int8_t *r)
{
    uint8_t msb = moreSignificantBit(*r, sizeof(int8_t));
    SLA(r);
    *r |= GBCPU_getFlagC();
    ALU_FLAG_C = msb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void RLC (int8_t *r)
{
    uint8_t msb = moreSignificantBit(*r, sizeof(int8_t));
    SLA(r);
    *r |= msb;
    ALU_FLAG_C = msb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void RR (int8_t *r)
{
    uint8_t lsb = lessSignificantBit(*r);
    SRL(r);
    *r |= ((GBCPU_getFlagC() << 7) & 0x80);
    ALU_FLAG_C = lsb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
}

void RRC (int8_t *r)
{
    uint8_t lsb = lessSignificantBit(*r);
    SRL(r);
    *r |= ((lsb << 7) & 0x80);
    ALU_FLAG_C = lsb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void SLA (int8_t *r)
{
    uint8_t msb = moreSignificantBit(*r, sizeof(int8_t));
    *r = (*r) << 1;
    *r &= 0xFE;
    
    ALU_FLAG_C = msb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void SRA (int8_t *r)
{
    uint8_t msb = moreSignificantBit(*r, sizeof(int8_t));
    uint8_t lsb = lessSignificantBit(*r);
    SRL(r);
    if (msb) {
        *r |= 0x80;
    }
    
    ALU_FLAG_C = lsb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void SRL (int8_t *r)
{
    uint8_t lsb = lessSignificantBit(*r);
    *r = (*r) >> 1;
    *r &= 0x7F;
    
    ALU_FLAG_C = lsb;
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
}

void SWAP (int8_t *r)
{
    int8_t rh = (*r) &0xF0;
    int8_t rl = (*r) &0x0F;
    
    *r = ((rh >>4) & 0x0F) | ((rl << 4) & 0xF0);
    
    ALU_FLAG_Z = (0 == (*r));
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 0;
    ALU_FLAG_C = 0;
}

//----------------------------------------------//
//                                              //
//              SingleBit Opcodes               //
//                                              //
//----------------------------------------------//

void BIT (int8_t r, int8_t n)
{
    uint8_t b = bitAtIndex(r, n);
    
    ALU_FLAG_Z = (0 == b);
    ALU_FLAG_N = 0;
    ALU_FLAG_H = 1;
}

void SET (int8_t *r, int8_t n)
{
    setBitAtIndex(r, n, 1);
}

void RES (int8_t *r, int8_t n)
{
    setBitAtIndex(r, n, 0);
}
