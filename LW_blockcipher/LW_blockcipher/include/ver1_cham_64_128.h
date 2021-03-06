#ifndef _VER1_CHAM_64_128_H_

//==========================================
//               CHAM 64/128(ver1)
//         Made by Byoungjin Seok
//              29 Aug, 2018
//==========================================

#include "define.h"

typedef struct _VER1_CHAM_64_
{
	uint16 rk[16];
} VER1_CHAM_64;

#define ROL(X, n) (((X) << (n)) | ((X) >> (16 - (n))))

int ver1_key_schedule(VER1_CHAM_64 *cham, uint16 k[8]);
int ver1_cham_enc(uint16 pt[4], VER1_CHAM_64 *cham);

#endif // !_VER1_CHAM_64_128_H_
