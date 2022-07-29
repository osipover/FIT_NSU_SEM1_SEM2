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

void PrintTime(TTime time) {
	if (time.hours < 10)
		printf("0%d:", time.hours);
	else
		printf("%d:", time.hours);

	if (time.min < 10)
		printf("0%d:", time.min);
	else
		printf("%d:", time.min);

	if (time.sec < 10)
		printf("0%d", time.sec);
	else
		printf("%d", time.sec);
}

int main() {
	TTime time = { 0, 0, 1 };
	int n;
	assert(scanf("%d", &n) == 1);
	AdvanceTime(&time, n);
	PrintTime(time);
	return SUCCESS;
}
