#include "../include/ver1_cham_64_128.h"

int key_schedule(CHAM_64 *cham, uint16 k[8])
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
		//printf("rk[%d] = %04X\n", i, cham->rk[i]);
	}

	return 0;
}
int cham_enc(uint16 pt[4], CHAM_64 *cham)
{
	int i;

	printf("pt = ");
	for (i = 0; i < 4; i++)
	{
		printf("%04X ", pt[i]);
	}
	printf("\n");
	for (i = 0; i < 16; i++)
	{
		printf("rk[%d] = %04X\n", i, cham->rk[i]);
	}
	printf("\n");



}