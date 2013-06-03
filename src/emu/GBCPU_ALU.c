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

#include "GBMacros.h"
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
    int8_t number    = n + c;
    int8_t rval      = *r;
    int8_t  sum      = rval + number;

    FLAG_N      = 0;
    FLAG_Z      = (0 == sum);
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    //Half overflow
    if (hFlag) {
        int8_t hn       = number & 0x0F;
        int8_t hr       = rval & 0x0F;
        int8_t msbn     = (hn & 0x08) >> 3;
        int8_t msbr     = (hr & 0x08) >> 3;
        
        if (msbn ^ msbr) {
            FLAG_H          = 0;
        }else {
            int8_t msbs     = ((hn + hr) & 0x08) >> 3;
            FLAG_H          = (0 != (msbs ^ msbn));
        }
    }
    
    //Overflow
    if (cFlag) {
        int8_t msbn      = (number & 0x80) >> 7;
        int8_t msbr      = (rval & 0x80) >> 7;
        
        
        if (msbn ^ msbr) {
            FLAG_C      = 0;
        }else {
            int8_t msbs   = (sum & 0x80) >> 7;
            FLAG_C      = (0 != (msbs ^ msbn));
        }
    }
    
    *r  = sum;
}

void addA (int8_t n, bool c)
{
    add8(&(REG_A), n, c, true, true);
}

void sub8(int8_t *r ,int8_t n, bool c, bool hFlag, bool cFlag, bool store)
{
    int8_t number      = ~(n + c) + 0x01;
    int8_t rval        = *r;
    int8_t sub         = rval + number;
    
    FLAG_N  = 1;
    FLAG_Z  = (0 == sub);
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    //Half overflow
    if (hFlag) {
        int8_t hn       = number & 0x0F;
        int8_t hr       = rval & 0x0F;
        int8_t msbn     = (hn & 0x08) >> 3;
        int8_t msbr     = (hr & 0x08) >> 3;
        
        if (msbn ^ msbr) {
            FLAG_H          = 1;
        }else {
            int8_t msbs     = ((hn + hr) & 0x08) >> 3;
            FLAG_H          = (0 == (msbs ^ msbn));
        }
    }
    
    //Overflow
    if (cFlag) {
        int8_t msbn      = (number & 0x80) >> 7;
        int8_t msbr      = (rval & 0x80) >> 7;
        
        
        if (msbn ^ msbr) {
            FLAG_C      = 1;
        }else {
            int8_t msbs   = (sub & 0x80) >> 7;
            FLAG_C      = (0 == (msbs ^ msbn));
        }
    }
    
    if (store) {
        *r  = sub;
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
    if (0 == REG_A) {
        FLAG_Z  = 1;
    }
    
    FLAG_N  = 0;
    FLAG_H  = 1;
    FLAG_C  = 0;
}

void OR (int8_t n)
{
    REG_A |= n;
    if (0 == REG_A) {
        FLAG_Z  = 1;
    }
    
    FLAG_N  = 0;
    FLAG_H  = 0;
    FLAG_C  = 0;
}

void XOR (int8_t n)
{
    REG_A ^= n;
    if (0 == REG_A) {
        FLAG_Z  = 1;
    }
    
    FLAG_N  = 0;
    FLAG_H  = 0;
    FLAG_C  = 0;
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
    FLAG_H  = 0;
    
    //TODO;
}

void CPL ()
{
    FLAG_N = 1;
    FLAG_H = 1;
    
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
    
    FLAG_N  = 0;
    
    //Overflow check:
    //-----------------
    //Operands with different signs never cause overflow
    //It happens when adding operands with like signs and the result has a different sign
    
    int16_t hl11        = (rVal & 0x0FFF);
    int16_t nn11        = (nn & 0x0FFF);
    int8_t hl11msb      = hl11 >> 11;
    int8_t nn11msb     = nn11 >> 11;
    
    if (hl11msb ^ nn11msb) {
        FLAG_H  = 0;
    }else {
        int16_t hsum11        = (sum & 0x0FFF);
        int8_t hsum11msb      = hsum11 >> 11;
        FLAG_H  = (0 != (hsum11msb ^ nn11msb));
    }
    
    int8_t hlmsb = (rVal >> 15) & 0x01;
    int8_t nnmsb = (nn >> 15) & 0x01;
    
    if (hlmsb ^ nnmsb) {
        FLAG_C  = 0;
    }else {
        int8_t summsb = (sum >> 15) & 0x01;
        FLAG_C = (0 != (summsb ^nnmsb));
    }
}

void ADD16 (int16_t* rr, int16_t nn)
{    
    add16(rr, nn);
    
    if (rr == ((int16_t*)&(REG_SP))) {
        FLAG_Z  = 0;
    }
}

void INC16 (int16_t* rr)
{
    (*rr) += 1;
}

void DEC16 (int16_t* rr)
{
    (*rr) -= 1;
}


void setFlagZ(bool z)
{
    REG_F &= 0x7F;
    if (z) {
        REG_F|= 0x80;
    }
}

void setFlagN(bool n)
{
    REG_F &= 0xBF;
    if (n) {
        REG_F |= 0x40;
    }
}


void setFlagC(bool c)
{
    REG_F &= 0xEF;
    if (c) {
        REG_F |= 0x10;
    }
}

void setFlagH(bool h)
{
    REG_F &= 0xDF;
    if (h) {
        REG_F |= 0x20;
    }
}

