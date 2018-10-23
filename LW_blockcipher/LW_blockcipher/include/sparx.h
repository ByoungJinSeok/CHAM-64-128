#ifndef _SPARX_H_

#include "define.h"

#define N_BRANCHES 2
#define N_STEPS 8
#define ROUNDS_PER_STEPS 3


typedef struct _SPARX_RK_
{
	uint32 rk[(N_BRANCHES*N_STEPS + 1) * ROUNDS_PER_STEPS];
} SPARX_RK;

#define T_ROTR7(X) ((((X) >> 7) & 0x01FF01FF) ^ (((X) << 9) & 0xFE00FE00))
#define T_ROTL2(X) ((((X) << 2) & 0xFFFCFFFC) ^ (((X) >> 14) & 0x00030003))
#define T_ROTL8(X) ((((X) << 8) & 0xFF00FF00) ^ (((X) >> 8) & 0x00FF00FF))
#define ROTL(X, n) (((X) << (n)) ^ ((X) >> (16 - (n))))

uint16* SPECKEY(uint16 *x, uint16 *y);
void K_4(uint16 *in_k, uint16 r);
void SPARX_KeySchedule(SPARX_RK *sparx_rk, uint16 *mk);
void SPARX_Encrypt(uint32 *pt, SPARX_RK *sparx_rk);

#endif // !_SPARX_H_