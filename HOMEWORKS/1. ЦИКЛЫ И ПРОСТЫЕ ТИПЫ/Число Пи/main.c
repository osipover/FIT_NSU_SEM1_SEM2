#include <stdio.h>
#include <math.h>

double Pi(double n) {
	double pi = 0;
	for (double i = 1; i <= n; ++i)
		pi = pi + 6 * (1 / (i * i));
	pi = sqrt(pi);
	return pi;
}

int main() {
	double n;
	if (scanf("%lf", &n) != 1)
		return 1;
	printf("%f", Pi(n));
	return 0;
}
