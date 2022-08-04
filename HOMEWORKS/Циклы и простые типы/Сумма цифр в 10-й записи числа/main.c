#include <stdio.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

int abs(int n) {
	return (n < 0) ? n * (-1) : n;
}

int SumNum(int n) {
	int sum = 0;
	n = abs(n);
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main() {
	int n;
	assert(scanf("%d", &n) != 1);
	printf("%d", SumNum(n));

	return SUCCESS;
}
