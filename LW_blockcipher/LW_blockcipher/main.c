#include <stdio.h>
#include <time.h>
#include "include\define.h"
#include "include\ver1_cham_64_128.h"
#include "include\ver2_cham_64_128.h"
#include "include\sparx.h"
#include "include\gift.h"

int test_ver1_cham64(void);
int test_ver2_cham64(void);
int test_sparx(void);

int main(void)
{
	//int i;
	//clock_t start, end;
	//printf("Lightweight block cipher - CHAM64/128\n");

	//printf("----------------------VER 1---------------------\n");
	//start = clock();
	//for (i = 0; i < 1000000; i++)
	//{
	//	test_ver1_cham64();
	//}
	//end = clock();
	//printf("elapse clock : %d\n", (end - start));

	//printf("----------------------VER 2---------------------\n");
	//start = clock();
	//for (i = 0; i < 1000000; i++)
	//{
	//	test_ver2_cham64();
	//}
	//end = clock();
	//printf("elapse clock : %d\n", (end - start));

	//printf("----------------------SPARX---------------------\n");
	//start = clock();
	//for (i = 0; i < 1; i++)
	//{
		//test_sparx();
	//}
	//end = clock();
	//printf("elapse clock : %d\n", (end - start));

	printf("----------------------GIFT---------------------\n");
	Make_T_GS();

	return 0;
}
int test_ver1_cham64(void)
{
	// CHAM-64/128 testvector
	// secret key : 0x0100 0x0302 0x0504 0x0706 0x0908 0x0b0a 0x0d0c 0x0f0e
	// plaintext  : 0x1100 0x3322 0x5544 0x7766
	// ciphertext : 0x453c 0x63bc 0xdcfa 0xbf4e
	//int i;
	uint16 k[8] = { 0x0100, 0x0302, 0x0504, 0x0706, 0x0908, 0x0b0a, 0x0d0c, 0x0f0e },
		pt[4] = { 0x1100, 0x3322, 0x5544, 0x7766 };
	VER1_CHAM_64 cham;

	//printf("INPUT = %04X %04X %04X %04X\n", pt[0], pt[1], pt[2], pt[3]);
	//printf("key = ");
	//for (i = 0; i < 8; i++)
	//{
	//	printf("%04X ", k[i]);
	//}
	//printf("\n");

	ver1_key_schedule(&cham, k);

	//for (i = 0; i < 16; i++)
	//{
	//	printf("RK[%d] = %04X\n", i, cham.rk[i]);
	//}

	ver1_cham_enc(pt, &cham);

	//printf("OUTPUT = %04X %04X %04X %04X\n", pt[0], pt[1], pt[2], pt[3]);


	return 0;
}
int test_ver2_cham64(void)
{
	// CHAM-64/128 testvector
	// secret key : 0x0100 0x0302 0x0504 0x0706 0x0908 0x0b0a 0x0d0c 0x0f0e
	// plaintext  : 0x1100 0x3322 0x5544 0x7766
	// ciphertext : 0x453c 0x63bc 0xdcfa 0xbf4e
	//int i;
	uint16 k[8] = { 0x0100, 0x0302, 0x0504, 0x0706, 0x0908, 0x0b0a, 0x0d0c, 0x0f0e },
		pt[4] = { 0x1100, 0x3322, 0x5544, 0x7766 };
	VER2_CHAM_64 cham;

	//printf("INPUT = %04X %04X %04X %04X\n", pt[0], pt[1], pt[2], pt[3]);
	//printf("key = ");
	//for (i = 0; i < 8; i++)
	//{
	//	printf("%04X ", k[i]);
	//}
	//printf("\n");

	ver2_key_schedule(&cham, k);

	//for (i = 0; i < 8; i++)
	//{
	//	printf("RK[%d] = %08X\n", i, cham.rk[i]);
	//}

	ver2_cham_enc(pt, &cham);

	//printf("OUTPUT = %04X %04X %04X %04X\n", pt[0], pt[1], pt[2], pt[3]);

	return 0;
}
int test_sparx(void)
{
	uint16 sparx_64_128_key[] = { 0x0011, 0x2233, 0x4455, 0x6677, 0x8899, 0xaabb, 0xccdd, 0xeeff };
	uint32 key[] = { 0x00112233, 0x44556677, 0x8899aabb, 0xccddeeff };
	uint32 out_k[4] = { 0, };
	//uint16 sparx_64_128_plaintext[] = { 0x0123, 0x4567, 0x89ab, 0xcdef };
	uint32 sparx_64_128_plaintext[] = { 0x01234567, 0x89abcdef };
	uint16 sparx_64_128_ciphertext[] = { 0x2bbe, 0xf152, 0x01f5, 0x5f98 };
	SPARX_RK sp;
	clock_t start, end;
	int i;
	
	
	SPARX_KeySchedule(&sp, sparx_64_128_key);

	start = clock();
	for (i = 0; i < 1000000; i++)
	{
		SPARX_Encrypt(sparx_64_128_plaintext, &sp);
	}
	end = clock();
	printf("elapsed clock = %d\n", (end - start));


	return 0;
}