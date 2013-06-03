//
//  GBCPU.h
//  GBEmu
//
//  Created by Pedro Muiños on 31/05/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBCPU_ALU_h
#define GBEmu_GBCPU_ALU_h


//----------------------------------------------//
//                                              //
//                  8-Bit ALU                   //
//                                              //
//----------------------------------------------//


void ADC (int8_t n);

void ADD (int8_t n);

void SUB (int8_t n);

void SBC (int8_t n);

void AND (int8_t n);

void OR (int8_t n);

void XOR (int8_t n);

void CP (int8_t n);

void INC (int8_t *r);

void DEC (int8_t *r);

void DAA ();

void CPL ();


//----------------------------------------------//
//                                              //
//                  16-Bit ALU                  //
//                                              //
//----------------------------------------------//

void ADD16 (int16_t* rr, int16_t nn);

void INC16 (int16_t* rr);

void DEC16 (int16_t* rr);

//----------------------------------------------//
//                                              //
//                Rotates & Shifts              //
//                                              //
//----------------------------------------------//

void RL (int8_t *r);

void RLC (int8_t *r);

void RR (int8_t *r);

void RRC (int8_t *r);

void SLA (int8_t *r);

void SRA (int8_t *r);

void SRL (int8_t *r);

void SWAP (int8_t *r);

//----------------------------------------------//
//                                              //
//              SingleBit Opcodes               //
//                                              //
//----------------------------------------------//

void BIT (int8_t r, int8_t n);
void SET (int8_t *r, int8_t n);
void RES (int8_t *r, int8_t n);



#endif
