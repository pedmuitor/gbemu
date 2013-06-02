//
//  GBMacros.h
//  GBEmu
//
//  Created by Jesús on 02/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBMacros_h
#define GBEmu_GBMacros_h

#define DWORD_FROM_HL(_H, _L)                 (0xFF00 & _H << 8) | (0x00FF & _L)
#define HL_FROM_DWORD(_DWORD, ptrH, ptrL)     *(ptrH) = (0xFF00 & _DWORD) >> 8; *(ptrL) = (0x00FF & _DWORD);


#endif
