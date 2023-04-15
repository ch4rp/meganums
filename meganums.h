#ifndef MEGA_H_
#define MEGA_H_ 1

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
#define SET_NYBBLE(number, index, mask) number = ((number) | (((unsigned long long)mask) << ((unsigned long long)index*4)))

typedef struct TagMEGA {
	/*limit (0, 170141183460469231731687303715884105727)*/
	/*1bit sign_1_bit; *//*most significant digit is sign bit*/
	unsigned long long MS_64_bit; /*most significant 63 bit*/
	unsigned long long LS_64_bit; /*least significant 64 bit*/
} MEGA;

typedef struct TagUMEGA {
	/*limit (0, 340282366920938463463374607431768211455)(39 digit)*/
	unsigned long long MS_64_bit; /*most significant 64 bit (0, 18446744073709551615)(20 digit)*/
	unsigned long long LS_64_bit; /*least significant 64 bit (0, 18446744073709551615)(20 digit)*/
} UMEGA;

int get_hex_int(char );
void umega_printx(UMEGA *);
void umega_assign(UMEGA *, const char *);
void umega_add(UMEGA *, UMEGA *);


#endif
