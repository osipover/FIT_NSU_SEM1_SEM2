#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

enum SEC_IN {
	SEC_IN_DAY = 86400,
	SEC_IN_HOUR = 3600,
	SEC_IN_MIN = 60
};

typedef struct TTime {
	int hours;
	int min;
	int sec;
}TTime;

void AdvanceTime(TTime* time, int n) {
	int timeInSec = time->hours * SEC_IN_HOUR + time->min * SEC_IN_MIN + time->sec;
	timeInSec += (n % SEC_IN_DAY);
	timeInSec = (timeInSec >= 0) ? timeInSec : SEC_IN_DAY + timeInSec;

	time->hours = (timeInSec / SEC_IN_HOUR);
	time->min = ((timeInSec - time->hours * SEC_IN_HOUR) / SEC_IN_MIN);
	time->sec = timeInSec - time->hours * SEC_IN_HOUR - time->min * SEC_IN_MIN;

	time->hours %= 24;
	time->min %= 60;
}

void PrintTime(TTime* time) {
	printf("%02d:%02d:%02d", time->hours, time->min, time->sec);
}

int main() {
	TTime time = { 13, 58, 32 };
	int n;
	assert(scanf("%d", &n) == 1);
	AdvanceTime(&time, n);
	PrintTime(&time);
	return SUCCESS;
}
