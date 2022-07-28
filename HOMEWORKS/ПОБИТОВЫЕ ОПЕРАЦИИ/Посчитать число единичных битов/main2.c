#include <stdio.h>
#include <assert.h>

#define UINT_SIZE 32

int PopulationCount(unsigned int num, unsigned int mask, int size) {
	if (num == 0)
		return 0;
	
	if ((num & (num - 1)) == 0)
		return 1;

	size /= 2;

	unsigned int mask1 = mask << size & mask;
	unsigned int mask2 = mask >> size & mask;

	unsigned int num1 = num & mask1;
	unsigned int num2 = num & mask2;

	return PopulationCount(num1, mask1, size) + PopulationCount(num2, mask2, size);
}

int main() {
	unsigned int num;
	assert(scanf("%u", &num) == 1);
	int countBit = PopulationCount(num, ~0U, UINT_SIZE);
	printf("%d", countBit);
}
