#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

typedef struct TPoint2D {
	float x;
	float y;
}TPoint2D;

void FillArrayOfTops(TPoint2D* tops, int N) {
	for (int i = 0; i < N; ++i)
		assert(scanf("%f %f", &tops[i].x, &tops[i].y) == 2);
}

TPoint2D* CreateArrayOfTops(int N) {
	TPoint2D* tops = malloc(sizeof(TPoint2D) * N);
	assert(tops != NULL);
	FillArrayOfTops(tops, N);
	return tops;
}

float abs(float a) {
	return (a >= 0) ? a : a * (-1);
}

float CalcAreaByGauss(TPoint2D* tops, int N) {
	float area = 0;
	for (int i = 0; i < N - 1; ++i) {
		area += (tops[i].x) * (tops[i + 1].y);
		area -= (tops[i+1].x) * (tops[i].y);
	}
	area += (tops[N - 1].x) * (tops[0].y);
	area -= (tops[0].x) * (tops[N - 1].y);
	area = 0.5 * abs(area);

	return area;
}

int main() {
	int N;
	assert((scanf("%d", &N) == 1) && (N > 0));

	TPoint2D* tops = CreateArrayOfTops(N);
	
	float area = CalcAreaByGauss(tops, N);
	printf("%f", area);

	return SUCCESS;
}
