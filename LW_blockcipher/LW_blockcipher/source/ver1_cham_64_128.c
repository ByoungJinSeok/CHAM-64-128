#include "../include/ver1_cham_64_128.h"

int ver1_key_schedule(VER1_CHAM_64 *cham, uint16 k[8])
{
	int i;
	uint16 rk[16] = { 0, };

	rk[0] = k[0] ^ ROL(k[0], 1) ^ ROL(k[0], 8);
	rk[9] = k[0] ^ ROL(k[0], 1) ^ ROL(k[0], 11);
	rk[1] = k[1] ^ ROL(k[1], 1) ^ ROL(k[1], 8);
	rk[8] = k[1] ^ ROL(k[1], 1) ^ ROL(k[1], 11);
	rk[2] = k[2] ^ ROL(k[2], 1) ^ ROL(k[2], 8);
	rk[11] = k[2] ^ ROL(k[2], 1) ^ ROL(k[2], 11);
	rk[3] = k[3] ^ ROL(k[3], 1) ^ ROL(k[3], 8);
	rk[10] = k[3] ^ ROL(k[3], 1) ^ ROL(k[3], 11);
	rk[4] = k[4] ^ ROL(k[4], 1) ^ ROL(k[4], 8);
	rk[13] = k[4] ^ ROL(k[4], 1) ^ ROL(k[4], 11);
	rk[5] = k[5] ^ ROL(k[5], 1) ^ ROL(k[5], 8);
	rk[12] = k[5] ^ ROL(k[5], 1) ^ ROL(k[5], 11);
	rk[6] = k[6] ^ ROL(k[6], 1) ^ ROL(k[6], 8);
	rk[15] = k[6] ^ ROL(k[6], 1) ^ ROL(k[6], 11);
	rk[7] = k[7] ^ ROL(k[7], 1) ^ ROL(k[7], 8);
	rk[14] = k[7] ^ ROL(k[7], 1) ^ ROL(k[7], 11);

	for (i = 0; i < 16; i++)
	{
		cham->rk[i] = rk[i];
		rk[i] = 0;
	}

	return 0;
}
int ver1_cham_enc(uint16 pt[4], VER1_CHAM_64 *cham)
{
	int i;
	uint16 tmp, X0, X1, X2, X3;

	X0 = pt[0];
	X1 = pt[1];
	X2 = pt[2];
	X3 = pt[3];

	for (i = 0; i < 80; i++)
	{
		if (i % 2 == 0)
		{
			tmp = ROL(X1, 1) ^ cham->rk[i % 16];
			tmp += (X0 ^ i);
			tmp = ROL(tmp, 8);
		}
		else
		{
			tmp = ROL(X1, 8) ^ cham->rk[i % 16];
			tmp += (X0 ^ i);
			tmp = ROL(tmp, 1);
		}

		X0 = X1;
		X1 = X2;
		X2 = X3;
		X3 = tmp;
	}

	pt[0] = X0;
	pt[1] = X1;
	pt[2] = X2;
	pt[3] = X3;
	
	return 0;
}