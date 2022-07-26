#include <stdio.h>

int SumNum(int n) {
	int sum = 0;
	if (n < 0)
		n *= -1;
	while (n > 0) {
		sum += n % 10;
		n /= 10;
	}
	return sum;
}

int main() {
	int n;
	if (scanf("%d", &n) != 1)
		return 1;
	printf("%d", SumNum(n));
	return 0;
}
