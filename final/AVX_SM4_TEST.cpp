#include "AVX_SM4.h"
#include <time.h>
#include <malloc.h>
int main(int argc,char **argv)
{
	// plain: 01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
	// key:   01 23 45 67 89 ab cd ef fe dc ba 98 76 54 32 10
	// cipher: 68 1e df 34 d2 06 96 5e 86 b3 e9 4f 53 6e 42 46

	/*
		to achieve avx2 best performance, encrypt 8 blocks at the same time, the data can be devided into 16 blocks each, each block contains 128bit
		gmssl has not fully developed the application of the avx2-encryption process, some of the functions may not work properly.
	*/
	u1* key = (u1*)malloc(SM4_KEY_SIZE);
	u1* plain = (u1*)malloc(SM4_BLOCK_SIZE*(1<<20));

	u1 *c = plain;
	u4 i;								// loop var
	int *pp=(int*)c;
	u4 rk[SM4_RND_KEY_SIZE/sizeof(u4)];
	SM4_key_schedule(key, rk);		// since the key only has 128bit, there is no need of SIMD
	sms4_avx2_encrypt_init(rk);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 4);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 4);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 8);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 8);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 10);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 10);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 12);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 12);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 16);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 16);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 18);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 18);
	benchmark_sm4_encrypt(plain, c, rk, 1 << 20);
	benchmark_sm4_decrypt(plain, c, rk, 1 << 20);

	
}
	
