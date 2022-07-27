#include <stdio.h>
#include <stdbool.h>

#define BIT_MAX 7

unsigned char CreateMask(char bit, int digit) {
	return (bit == 1) ? 1 << digit : ~(1 << digit);
}

void SwapBits(char bit1, char bit2, unsigned char* a, unsigned char* b, int digit) {
	unsigned char mask1 = CreateMask(bit2, digit);
	unsigned char mask2 = CreateMask(bit1, BIT_MAX - digit);

	*a = (bit2 == 1) ? *a | mask1 : *a & mask1;
	*b = (bit1 == 1) ? *b | mask2 : *b & mask2;
}

bool IsElementSame(int index1, int index2) {
	if (index1 == index2)
		return true;
	else
		return false;
}

char GetBit(unsigned char a, int digit) {
	return (a & (1 << digit)) > 0 ? 1 : 0;
}

void ReverseBits(unsigned char* array, int size) {
	for (int i = 0; i < (float)size / 2.0; ++i) {
		for (int digit = BIT_MAX; digit >= 0; --digit) {
			char bit1 = GetBit(array[i], digit);
			char bit2 = GetBit(array[size - i - 1], BIT_MAX - digit);

			if (IsElementSame(i, size - 1 - i) && (digit < 4))
				break;
			
			SwapBits(bit1, bit2, &array[i], &array[size - 1 - i], digit);
		}
	}
}

void PrintArray(unsigned char* array, int size) {
	for (int i = 0; i < size; ++i)
		printf("%d ", array[i]);
}

int main() {
	unsigned char array[] = {1, 2, 3};
	int size = sizeof(array) / sizeof(unsigned char);

	ReverseBits(array, size);
//f
	PrintArray(array, size);
	
	return 0;
}
