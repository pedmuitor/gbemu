//
//  GBCPU.h
//  GBEmu
//
//  Created by Pedro Muiños on 31/05/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBCPU_h
#define GBEmu_GBCPU_h

#include <stdbool.h>

struct {
    struct {
        int8_t  A, B, C, D, E, H, L;
        uint16_t PC, SP;
    }_r;
    
    struct {
        bool   Z, N, H, C;
    }_flags;
    
}Z80;

#define REGISTERS       Z80._r
#define REG_A           REGISTERS.A
#define REG_B           REGISTERS.B
#define REG_C           REGISTERS.C
#define REG_D           REGISTERS.D
#define REG_E           REGISTERS.E
#define REG_H           REGISTERS.H
#define REG_L           REGISTERS.L
#define REG_SP          REGISTERS.SP

#define REG_BC          ((0xFF00 & REG_B <<8) | (0x00FF & REG_C))
#define REG_DE          ((0xFF00 & REG_D <<8) | (0x00FF & REG_E))
#define REG_HL          ((0xFF00 & REG_H <<8) | (0x00FF & REG_L))

#define FLAGS           Z80._flags
#define FLAG_Z          FLAGS.Z
#define FLAG_N          FLAGS.N
#define FLAG_H          FLAGS.H
#define FLAG_C          FLAGS.C

//----------------------------------------------//
//                                              //
//                  8-Bit Loads                 //
//                                              //
//----------------------------------------------//

// LD r,n         - r <- n
void LD (int8_t *r, int8_t n);


//----------------------------------------------//
//                                              //
//                  16-Bit Loads                //
//                                              //
//----------------------------------------------//

// LD HRLR,nn        - HRLR <- nn
void LD16 (int8_t *hr, int8_t *lr, int16_t nn);

//----------------------------------------------//
//                                              //
//                  8-Bit ALU                   //
//                                              //
//----------------------------------------------//


//ADC A,n        - Add n + Carry flag to A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Set if carry from bit 3.
//C - Set if carry from bit 7.
void ADC (int8_t n);

//ADD A,n        - Add n to A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Set if carry from bit 3.
//C - Set if carry from bit 7.
void ADD (int8_t n);

//SUB n          - Subtract n from A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Set.
//H - Set if no borrow from bit 4.
//C - Set if no borrow.
void SUB (int8_t n);

//SBC A,n        - Subtract n + Carry flag from A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Set.
//H - Set if no borrow from bit 4.
//C - Set if no borrow.
void SBC (int8_t n);

//AND n          - Logically AND n with A, result in A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Set.
//C - Reset.
void AND (int8_t n);

//OR n           - Logical OR n with register A, result in A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Reset.
//C - Reset.
void OR (int8_t n);

//XOR n          - Logical exclusive OR n with
//register A, result in A.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Reset.
//C - Reset.
void XOR (int8_t n);

//CP n           - Compare A with n.
//
//This is basically an A - n subtraction
//instruction but the results are thrown away.
//
//n = A,B,C,D,E,H,L,[HL],#
//
//Flags affected:
//Z - Set if result is zero. [Set if A = n.]
//N - Set.
//H - Set if no borrow from bit 4.
//C - Set for no borrow. [Set if A < n.]
void CP (int8_t n);

//INC n          - Increment register n.
//
//n = A,B,C,D,E,H,L,[HL]
//
//Flags affected:
//Z - Set if result is zero.
//N - Reset.
//H - Set if carry from bit 3.
//C - Not affected.
void INC (int8_t *r);

//DEC n          - Decrement register n.
//
//n = A,B,C,D,E,H,L,[HL]
//
//Flags affected:
//Z - Set if reselt is zero.
//N - Set.
//H - Set if no borrow from bit 4.
//C - Not affected.
void DEC (int8_t *r);


//----------------------------------------------//
//                                              //
//                  16-Bit ALU                  //
//                                              //
//----------------------------------------------//

//ADD HL,nn      - Add n to HL.
//
//nn = BC,DE,HL
//
//Flags affected:
//Z - Not affected.
//N - Reset.
//H - Set if carry from bit 11.
//C - Set if carry from bit 15.
void ADD16 (int16_t nn);

//ADD SP,n       - Add n to Stack Pointer [SP].
//
//n = one byte signed immediate value.
//
//Flags affected:
//Z - Reset.
//N - Reset.
//H - Set or reset according to operation.
//C - Set or reset according to operation.
void ADD_SP (int8_t n);

//INC nn         - Increment register nn.
//
//nn = BC,DE,HL,SP
//
//Flags affected:
//None.

void INC16 (int8_t *hr, int8_t *lr);

//DEC nn         - Decrement register nn.
//
//nn = BC,DE,HL,SP
//
//Flags affected:
//None

void DEC16 (int8_t *hr, int8_t *lr);


//----------------------------------------------//
//                                              //
//                Miscellaneous                 //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                Rotates & Shifts              //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                  Bit Opcodes                 //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                  Jumps                       //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                  Calls                       //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                  Restarts                    //
//                                              //
//----------------------------------------------//

//----------------------------------------------//
//                                              //
//                  Returns                     //
//                                              //
//----------------------------------------------//



#endif
