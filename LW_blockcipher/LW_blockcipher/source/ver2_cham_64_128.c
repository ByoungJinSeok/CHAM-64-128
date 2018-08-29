#include "../include/ver2_cham_64_128.h"

int ver2_key_schedule(VER2_CHAM_64 *cham, uint16 k[8])
{
	int i = 0;
	uint32 rk[8] = { 0, }, tmp = 0;

	tmp = (((uint32)k[0]) << 16) | ((uint32)k[2]);
	rk[0] = T_ROL1(tmp) ^ T_ROL8(tmp) ^ tmp;
	rk[5] = T_ROL1(tmp) ^ T_ROL11(tmp) ^ tmp;
	tmp = (((uint32)k[1]) << 16) | ((uint32)k[3]);
	rk[1] = T_ROL1(tmp) ^ T_ROL8(tmp) ^ tmp;
	rk[4] = T_ROL1(tmp) ^ T_ROL11(tmp) ^ tmp;
	tmp = (((uint32)k[4]) << 16) | ((uint32)k[6]);
	rk[2] = T_ROL1(tmp) ^ T_ROL8(tmp) ^ tmp;
	rk[7] = T_ROL1(tmp) ^ T_ROL11(tmp) ^ tmp;
	tmp = (((uint32)k[5]) << 16) | ((uint32)k[7]);
	rk[3] = T_ROL1(tmp) ^ T_ROL8(tmp) ^ tmp;
	rk[6] = T_ROL1(tmp) ^ T_ROL11(tmp) ^ tmp;

	for (i = 0; i < 8; i++)
	{
		cham->rk[i] = rk[i];
		rk[i] = 0;
	}

	return 0;
}
int ver2_cham_enc(uint16 pt[4], VER2_CHAM_64 *cham)
{
	int i = 0;
	uint32 pair_odd = 0, pair_even = 0, tmp0 = 0, tmp1 = 0;

	pair_odd = ((uint32)pt[0] << 16) ^ (uint32)pt[2];
	pair_even = ((uint32)pt[1] << 16) ^ (uint32)pt[3];

	for (i = 0; i < 20; i++)
	{
		tmp0 = T_ROL1(pair_even) ^ cham->rk[(2*i) % 8];
		tmp0 += (pair_odd ^ ((4 * i) << 16) ^ ((4 * i) + 2));
		tmp0 -= (tmp0 & 0x0000FFFF) < ((pair_odd ^ ((4 * i) << 16) ^ ((4 * i) + 2)) & 0x0000FFFF) ? 0x00010000 : 0;
		tmp0 = T_ROL8(tmp0);

		tmp1 = T_ROL8( ( (pair_odd << 16) | (tmp0 >> 16) ) ) ^ cham->rk[((2*i)+1) % 8];
		tmp1 += (pair_even ^ (((4 * i) + 1) << 16) ^ (((4 * i) + 3)));
		tmp1 -= (tmp1 & 0x0000FFFF) < ((pair_even ^ (((4 * i) + 1) << 16) ^ (((4 * i) + 3))) & 0x0000FFFF) ? 0x00010000 : 0;
		tmp1 = T_ROL1(tmp1);

		pair_odd = tmp0;
		pair_even = tmp1;
	}

	pt[0] = (pair_odd >> 16);
	pt[1] = (pair_even >> 16);
	pt[2] = pair_odd;
	pt[3] = pair_even;

	return 0;
}