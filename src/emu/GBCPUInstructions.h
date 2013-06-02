//
//  GBCPUInstructions.h
//  GBEmu
//
//  Created by Jesús on 02/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBCPUInstructions_h
#define GBEmu_GBCPUInstructions_h

//----------------------------------------------//
//                                              //
//                 CPU Commands                 //
//                                              //
//----------------------------------------------//

void setUp(void);
void shutDown(void);

void nextOperation(void);
uint8_t readOperationByteParameter(void);
uint16_t readOpertionWordParameter(void);

#endif
