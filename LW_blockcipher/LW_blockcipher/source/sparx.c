#include "../include/sparx.h"

uint16* SPECKEY(uint16 *x, uint16 *y)
{
	uint16 tmp[2];
	tmp[0] = ROTL((*x), 9) + (*y);
	tmp[1] = ROTL((*y), 2) ^ tmp[0];

	return tmp;
}
//void K_4(uint32 *out_k, uint32 *in_k, uint32 r)
//{
//	uint16 *tmp;
//	tmp = SPECKEY((uint16 *)in_k + 1, (uint16 *)in_k);
//	out_k[0] = in_k[3] + r + 1;
//	out_k[3] = in_k[2];
//	*(((uint16 *)out_k) + 5) = *(((uint16 *)in_k) + 3) + tmp[0];
//	*(((uint16 *)out_k) + 4) = *(((uint16 *)in_k) + 2) + tmp[1];
//	out_k[1] = ((uint32)tmp[0] << 16) ^ ((uint32)tmp[1]);
//}
void K_4(uint16 *in_k, uint16 r)
{
	uint16 *tmp;
	tmp = SPECKEY(in_k, in_k + 1);
	in_k[0] = in_k[6];
	in_k[1] = in_k[7] + r + 1;
	in_k[6] = in_k[4];
	in_k[7] = in_k[5];
	in_k[4] = tmp[0] + in_k[2];
	in_k[5] = tmp[1] + in_k[3];
	in_k[2] = tmp[0];
	in_k[3] = tmp[1];
}
void SPARX_KeySchedule(SPARX_RK *sparx_rk, uint16 *mk)
{
	uint16 i;

	for (i = 0; i < 8; i++)
	{
		*((uint16 *)sparx_rk->rk + (12 * i) + 1) = *mk;
		*((uint16 *)sparx_rk->rk + (12 * i) + 3) = *(mk + 1);
		*((uint16 *)sparx_rk->rk + (12 * i) + 5) = *(mk + 2);
		*((uint16 *)sparx_rk->rk + (12 * i) + 7) = *(mk + 3);
		*((uint16 *)sparx_rk->rk + (12 * i) + 9) = *(mk + 4);
		*((uint16 *)sparx_rk->rk + (12 * i) + 11) = *(mk + 5);
		K_4(mk, 2*i);
		*((uint16 *)sparx_rk->rk + (12 * i)) = *mk;
		*((uint16 *)sparx_rk->rk + (12 * i) + 2) = *(mk + 1);
		*((uint16 *)sparx_rk->rk + (12 * i) + 4) = *(mk + 2);
		*((uint16 *)sparx_rk->rk + (12 * i) + 6) = *(mk + 3);
		*((uint16 *)sparx_rk->rk + (12 * i) + 8) = *(mk + 4);
		*((uint16 *)sparx_rk->rk + (12 * i) + 10) = *(mk + 5);
		K_4(mk, (2 * i) + 1);
	}
	*((uint16 *)sparx_rk->rk + 97) = *mk;
	*((uint16 *)sparx_rk->rk + 99) = *(mk + 1);
	*((uint16 *)sparx_rk->rk + 96) = *(mk + 2);
	*((uint16 *)sparx_rk->rk + 98) = *(mk + 3);
	*((uint16 *)sparx_rk->rk + 101) = *(mk + 4);
	*((uint16 *)sparx_rk->rk + 100) = *(mk + 5);
}
void SPARX_Encrypt(uint32 *pt, SPARX_RK *sparx_rk)
{
	uint16 tmp;
	uint8 i, j;
	tmp = *((uint16 *)pt);
	*((uint16 *)pt) = *((uint16 *)pt + 3);
	*((uint16 *)pt + 3) = tmp;
	//step function - A^3
	for (j = 0; j < 8; j++)
	{
		for (i = 0; i < 3; i++)
		{
			*(pt) ^= *(sparx_rk->rk + (2 * i) + (6 * j));
			*(pt + 1) ^= *(sparx_rk->rk + (2 * i) + (6 * j) + 1);
			*(pt) = T_ROTR7(*(pt));
			*(pt) += *(pt + 1);
			*(pt) -= (*(pt) & 0x0000FFFF) < ((*(pt + 1)) & 0x0000FFFF)
				? 0x00010000 : 0;
			*(pt + 1) = T_ROTL2(*(pt + 1)) ^ *(pt);
		}
		//step function - L
		tmp = *((uint16 *)pt + 1) ^ *((uint16 *)pt + 3);
		tmp = ROTL(tmp, 8);
		*((uint16 *)pt + 1) ^= *((uint16 *)pt);
		*((uint16 *)pt + 3) ^= *((uint16 *)pt + 2);
		*((uint16 *)pt) ^= *((uint16 *)pt + 1);
		*((uint16 *)pt + 2) ^= *((uint16 *)pt + 3);
		*((uint16 *)pt + 1) ^= tmp;
		*((uint16 *)pt + 3) ^= tmp;
	}
	*(pt) ^= sparx_rk->rk[48];
	*(pt + 1) ^= sparx_rk->rk[49];
	
	tmp = *((uint16 *)pt);
	*((uint16 *)pt) = *((uint16 *)pt + 3);
	*((uint16 *)pt + 3) = tmp;
}