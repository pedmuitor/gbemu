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
void LD16 (int16_t *rr, int16_t nn);
void LD16_HL (int8_t *rh, int8_t *rl, int16_t nn);


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

void DAA ();

void CPL ();



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
void ADD16 (int16_t* rr, int16_t nn);

//INC nn         - Increment register nn.
//
//nn = BC,DE,HL,SP
//
//Flags affected:
//None.

void INC16 (int16_t* rr);
void INC16_HL (int8_t *rh, int8_t *rl);

//DEC nn         - Decrement register nn.
//
//nn = BC,DE,HL,SP
//
//Flags affected:
//None

void DEC16 (int16_t* rr);
void DEC16_HL (int8_t *rh, int8_t *rl);


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
