#include "meganums.h"

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
	printf("%016llX", umega_num->MS_64_bit);
	printf("%016llX\n", umega_num->LS_64_bit);
}


void umega_assign(UMEGA *umega_num, const char *hex_num)
{
	size_t leng_hex_num = strlen(hex_num);
	int i;

	umega_num->MS_64_bit = 0;
	umega_num->LS_64_bit = 0;

	if (leng_hex_num > MEGA_NYBBLE_SIZE) {
		return;
	
        }
	else if (leng_hex_num <= MEGA_BYTE_SIZE) {
		/*assign least significant 64 bit */
		for (i = 0; i < leng_hex_num; ++i) {
			SET_NYBBLE(umega_num->LS_64_bit, i, get_hex_int(hex_num[leng_hex_num -i -1]));
			/*PRINTBIN(umega_num->LS_64_bit);*/
		}
	}
	else if (leng_hex_num > MEGA_BYTE_SIZE) {
		/*assign least significant 64 bit */
		for (i = 0; i < MEGA_BYTE_SIZE; ++i) {
			SET_NYBBLE(umega_num->LS_64_bit, i, get_hex_int(hex_num[leng_hex_num -i -1]));
		}
		/*assign most significant 64 bit */
		for (; i < leng_hex_num; ++i) {
			SET_NYBBLE(umega_num->MS_64_bit, i, get_hex_int(hex_num[leng_hex_num -i -1]));
		}
	}
}

void umega_add(UMEGA *x, UMEGA *y)
{
	unsigned long long c, s, a, b, sum_LS, sum_MS;
	unsigned long long mask = 0x1;
	int i;
	sum_LS = sum_MS = 0x0;

	for (s = 0, i = 63; i >= 0; --i) {
		a = (x->LS_64_bit & mask) >> (63 - i); // a0, a1, ... a63 dizisindeki i numaralı basamak
		b = (y->LS_64_bit & mask) >> (63 - i); // b0, b1, ... b63 dizisindeki i numaralı basamak
		c = a ^ b; 
		sum_LS |= (c ^ s) << (63 - i);
		s = a & b; // elde var
		mask <<= 1;
	}

	mask = 0x1;

	for (i = 63; i >= 0; --i) {
		a = (x->MS_64_bit & mask) >> (63 - i); // a0, a1, ... a63 dizisindeki i numaralı basamak
		b = (y->MS_64_bit & mask) >> (63 - i); // b0, b1, ... b63 dizisindeki i numaralı basamak
		c = a ^ b; 
		sum_MS |= (c ^ s) << (63 - i);
		s = a & b; // elde var
		mask <<= 1;
	}
	x->LS_64_bit = sum_LS;
	x->MS_64_bit = sum_MS;
}

