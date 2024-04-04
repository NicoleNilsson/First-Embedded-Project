#ifndef __BIT_MANIPULATION_H
#define __BIT_MANIPULATION_H

//set bit on byte as 1
#define BIT_SET(byte, nbit) ((byte) |= (1 << (nbit))) 
//set bit on byte as 0
#define BIT_CLEAR(byte ,nbit) ((byte) &= ~(1 << (nbit)))
//check if bit on byte is 1 
#define BIT_CHECK(byte, nbit) ((byte) & (1 << (nbit))) 
//flip all bits (so all 1 set as 0, all 0 set as 1)
#define BIT_FLIP(byte, nbit) ((byte) ^= (1 << (nbit))) 

#endif