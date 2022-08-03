#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>

#define ROW 2
#define COLUMN 2

float CalcPoly(float poly[ROW][COLUMN], float x, float y) {
	if ((x == 0.0) || (y == 0))
		return 0.0;

	float sum = 0.0;
	float powX = 1.0;
	float powY = 1.0;

	for (int i = 0; i < ROW; ++i) {

		for (int j = 0; j < COLUMN; ++j) {
			sum += poly[i][j] * powX * powY;
			powY *= y;
		}

		powY = 1.0;
		powX *= x;
	}
	return sum;
}

void FillRandValues(float poly[ROW][COLUMN]) {
	srand(time(NULL));

	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; ++j)
			poly[i][j] = (float)rand()/(float)rand();
	}
}

void PrintPoly(float poly[ROW][COLUMN]) {
	printf("Polynomial:\n");
	for (int i = 0; i < ROW; ++i) {
		for (int j = 0; j < COLUMN; ++j)
			printf("%f ", poly[i][j]);
		printf("\n");
	}
}

int main() {
	float poly[ROW][COLUMN];
	FillRandValues(poly);
	PrintPoly(poly);

	float x, y;
	assert(scanf("%f %f", &x, &y) == 2);

	float sumPoly = CalcPoly(poly, x, y);
	printf("Sum of polynomial: %f", sumPoly);
	return 0;
}
