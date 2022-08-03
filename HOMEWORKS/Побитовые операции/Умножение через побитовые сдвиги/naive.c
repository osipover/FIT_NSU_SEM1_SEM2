#include <stdio.h>
#include <assert.h>

int Multiply(unsigned int a, unsigned int b, unsigned mult) {
	if ((b == 0) || (a == 0))
		return 0;

	if (b == 1)
		return a;

	mult = mult << 1;

	return Multiply(a, b/2, mult) + Multiply(a, b - b/ 2, mult);
}

int main() {
	unsigned int a = 1, b = 7;
	printf("%d", Multiply(a, b, a));
}
