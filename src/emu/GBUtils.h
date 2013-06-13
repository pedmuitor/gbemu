//
//  GBUtils.h
//  GBEmu
//
//  Created by Pedro on 12/06/13.
//  Copyright (c) 2013 None. All rights reserved.
//

#ifndef GBEmu_GBUtils_h
#define GBEmu_GBUtils_h

uint8_t bitAtIndex (int n, int index);

void setBitAtIndex (int8_t *r, int index, uint8_t value);

uint8_t moreSignificantBit (int n, int size);

uint8_t lessSignificantBit (int n);


#endif
