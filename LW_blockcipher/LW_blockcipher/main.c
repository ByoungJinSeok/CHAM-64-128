#include <stdio.h>
#include <time.h>
#include "include\define.h"
#include "include\ver1_cham_64_128.h"
#include "include\ver2_cham_64_128.h"

int test_ver1_cham64(void);
int test_ver2_cham64(void);

int main(void)
{
	int i;
	clock_t start, end;
	printf("Lightweight block cipher - CHAM64/128\n");

	printf("----------------------VER 1---------------------\n");
	start = clock();
	for (i = 0; i < 1000000; i++)
	{
		test_ver1_cham64();
	}
	end = clock();
	printf("elapse clock : %d\n", (end - start));

	printf("----------------------VER 2---------------------\n");
	start = clock();
	for (i = 0; i < 1000000; i++)
	{
		test_ver2_cham64();
	}
	end = clock();
	printf("elapse clock : %d\n", (end - start));

	return 0;
}
int test_ver1_cham64(void)
{
	// CHAM-64/128 testvector
	// secret key : 0x0100 0x0302 0x0504 0x0706 0x0908 0x0b0a 0x0d0c 0x0f0e
	// plaintext  : 0x1100 0x3322 0x5544 0x7766
	// ciphertext : 0x453c 0x63bc 0xdcfa 0xbf4e
	int i;
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
	int i;
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