#include <stdio.h>
#include "include\define.h"
#include "include\ver1_cham_64_128.h"

int main(void)
{
	printf("Lightweight block cipher - CHAM\n");

	test_ver1_cham64();

	return 0;
}
int test_ver1_cham64(void)
{
	// CHAM-64/128 testvector
	// secret key : 0x0100 0x0302 0x0504 0x0706 0x0908 0x0b0a 0x0d0c 0x0f0e
	// plaintext  : 0x1100 0x3322 0x5544 0x7766
	// ciphertext : 0x453c 0x63bc 0xdcfa 0xbf4e

	uint16 k[8] = { 0x0100, 0x0302, 0x0504, 0x0706, 0x0908, 0x0b0a, 0x0d0c, 0x0f0e },
		pt[4] = { 0x1100, 0x3322, 0x5544, 0x7766 };
	CHAM_64 cham;

	key_schedule(&cham, k);
	cham_enc(pt, &cham);


	return 0;
}