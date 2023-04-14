#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MEGA_BIT_SIZE 128
#define MEGA_BIT2_SIZE 64
#define MEGA_NYBBLE_SIZE 32
#define MEGA_BYTE_SIZE 16
#define MEGA_WORD_SIZE 8
#define MEGA_DWORD_SIZE 4

/*index:
	number: 1111 0100 0010 1100
	        \  / \  / \  / \  /
	         \/   \/   \/   \/
	index:   3    2    1    0
	shift: index * nybbles
	       3*4
	       2*4
	       1*4
	       0*4
*/
#define SET_NYBBLE(number, index, mask) number = ((number) | ((mask) << (index*4)))

typedef struct TagMEGA {
	/*limit (0, 170141183460469231731687303715884105727)*/
	/*1bit sign_1_bit; *//*most significant digit is sign bit*/
	unsigned long long MS_63_bit; /*most significant 63 bit*/
	unsigned long long LS_64_bit; /*least significant 64 bit*/
} MEGA;

typedef struct TagUMEGA {
	/*limit (0, 340282366920938463463374607431768211455)(39 digit)*/
	unsigned long long MS_64_bit; /*most significant 64 bit (0, 18446744073709551615)(20 digit)*/
	unsigned long long LS_64_bit; /*least significant 64 bit (0, 18446744073709551615)(20 digit)*/
} UMEGA;

int get_hex_int(char );
void _PrintBinary(unsigned long long *, int);
#define bits(y) (sizeof(y)*8)
#define PRINTBIN(i) _PrintBinary(((unsigned long long *)(&(i))), bits(i))
unsigned long long ptrplus(void *);
void umega_printx(UMEGA *);
void umega_assign(UMEGA *, const char *);

unsigned long long ptrplus(void *address)
{
	unsigned long long int_address = (unsigned long long) address;
	return int_address + 1;
}

void _PrintBinary(unsigned long long *numb, int bitleng)
{
	for (int i = bitleng - 1; i >= 0; --i)
		printf("%llu", (*numb) >> i & 0x1);
	printf("\n");
}



int get_hex_int(char ch)
{
	ch = tolower(ch);

	if (ch >= 'a' && ch <= 'f')
		return ch - 'a' + 10;
	if (ch >= '0' && ch <= '9')
		return ch - '0';
	return 0;
}

/* Umega functions */
void umega_printx(UMEGA *umega_num)
{
	printf("%032llX", umega_num->MS_64_bit);
	printf("%032llX\n", umega_num->LS_64_bit);
}


void umega_assign(UMEGA *umega_num, const char *hex_num)
{
	size_t leng_hex_num = strlen(hex_num);
	int i, mask_buff;

	umega_num->MS_64_bit = 0;
	umega_num->LS_64_bit = 0;

	if (leng_hex_num > MEGA_NYBBLE_SIZE) {
		return;
	
        }
	else if (leng_hex_num <= 16) {
		for (i = 0; i < leng_hex_num; ++i) {
			SET_NYBBLE(umega_num->LS_64_bit, i, get_hex_int(hex_num[leng_hex_num -i -1]));
		}
	}
	else if (leng_hex_num > 16) {
		return;
	}
}

int main(void)
{
	/*
	char *hex_nibles = "0123546789ABCDEF";
	int i;
	for (i = 0; i < 16; ++i) {
		printf("%d\n", get_hex_int(hex_nibles[i]));
	}
	*/
	/*
	unsigned short x = 0xf402;
	PRINTBIN(x);
	SET_NYBBLE(x, 1, 0xa);
	PRINTBIN(x);
	SET_NYBBLE(x, 1, 0xd);
	PRINTBIN(x);
	*/
	UMEGA devbirsayi;
	umega_assign(&devbirsayi, "f402");
	umega_printx(&devbirsayi);

	return 0;
}


