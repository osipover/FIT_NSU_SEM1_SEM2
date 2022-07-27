#include <stdio.h>
#include <stdbool.h>

#define ROW 3
#define COLUMN 4

int CountNullRows(int matrix[ROW][COLUMN]) {
	int countNullRows = 0;
	for (int i = 0; i < ROW; ++i) {
		bool isNullRow = true;

		for (int j = 0; j < COLUMN; ++j) {
			if (matrix[i][j] != 0) {
				isNullRow = false;
				break;
			}
		}

		if (isNullRow == true)
			++countNullRows;
	}
	return countNullRows;
}

int main() {
	int matrix[ROW][COLUMN] = {
		{1, 0, 0, 0},
		{0, 0, 0, 0},
		{1, 0, 0, 0} 
	};
	int countNullRows = CountNullRows(matrix);
	printf("%d", countNullRows);
	return 0;
}
