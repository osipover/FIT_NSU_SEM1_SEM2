#include <stdio.h>
#include <assert.h>

int PopulationCount(int* countBit, unsigned int num) {
	if (num == 0)
		return 0;
	num = num & (num - 1);
	(*countBit)++;
	PopulationCount(countBit, num);
}

int main() {
	unsigned int num;
	assert(scanf("%u", &num) == 1);
	int countBit = 0;
	PopulationCount(&countBit, num);
	printf("%d", countBit);
}
