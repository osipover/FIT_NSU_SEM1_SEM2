#include <stdio.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

void GenerateMultByConst(unsigned int multiplier) {
	static int position = 0;

	if (position == 0)
		printf("int MultBy%u(unsigned int x){\n\treturn ", multiplier);

	if ((multiplier == 0) && (position == 0)) {
		printf("0;\n}");
		return;
	}

	if ((multiplier & (1 << position)) != 0) {
		printf("(x << %d)", position);

		unsigned char mask = ~(1 << position);

		if ((multiplier & mask) != 0) {
			printf(" + ");
			multiplier &= mask;
		}
		else {
			printf(";\n}");
			return;
		}
	}

	++position;
	GenerateMultByConst(multiplier);
}

int main() {
	unsigned int multiplier;
	assert(scanf("%u", &multiplier) == 1);
	GenerateMultByConst(multiplier);
	return SUCCESS;
}
