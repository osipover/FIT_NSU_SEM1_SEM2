#include <stdio.h>
#include <math.h>

int SumNumInFloatPart(double a, int n) {
	int sum = 0;
	while (n > 0) {
		a -= (int)a;
		a *= 10;
		sum += (int)a;
		--n;
	}
	return sum;
}

int main() {
	double a;
	int n;
	if (scanf("%lf %d", &a, &n) != 2)
		return 1;
	printf("%d", SumNumInFloatPart(a, n));
	return 0;
}
