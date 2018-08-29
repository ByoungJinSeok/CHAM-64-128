#ifndef _VER2_CHAM_64_128_H_

//==========================================
//               CHAM 64/128(ver2)
//         Made by Byoungjin Seok
//              29 Aug, 2018
//==========================================

#include "define.h"

typedef struct _VER2_CHAM_64_
{
	uint32 rk[8];
} VER2_CHAM_64;

// 2-way ROL operation
//  -------------
//  | ROL | ROL |
//  -------------

#define T_ROL1(X)  ( ( ((X) << 1 ) & 0xFFFEFFFE ) | ( ((X) >> 15) & 0x00010001 ) )
#define T_ROL8(X)  ( ( ((X) << 8 ) & 0xFF00FF00 ) | ( ((X) >> 8 ) & 0x00FF00FF ) )
#define T_ROL11(X) ( ( ((X) << 11) & 0xF800F800 ) | ( ((X) >> 5 ) & 0x07FF07FF ) )
 
// 2-way key schedule
int ver2_key_schedule(VER2_CHAM_64 *cham, uint16 k[8]);
// 2-way cham64 encryption
int ver2_cham_enc(uint16 pt[4], VER2_CHAM_64 *cham);

#endif // !_VER2_CHAM_64_128_H_
