#include <stdio.h>
#include <stdlib.h>
#include <assert.h>

#define DAYS_IN_YEAR 365

enum WORK_RESULT {
	SUCCESS = 0,
	FAILURE = 1
};

enum MONTHS {
	january = 31,
	february = 28,
	march = 31,
	april = 30, 
	may = 31,
	june = 30,
	july = 31,
	august = 31, 
	september = 30,
	october = 31,
	november = 30,
	december = 31
};

int calendar[] = {
	0,
	january,
	february,
	march,
	april,
	may,
	june,
	july,
	august,
	september,
	october,
	november,
	december
};

typedef struct TDate {
	int day;
	int month;
	int year;
}TDate;

int CalcDateInDay(TDate* date, int n) {
	int dateInDay = date->day;
	for (int i = 1; i < date->month; ++i) {
		dateInDay += calendar[i];
	}
	dateInDay += (date->year) * DAYS_IN_YEAR;
	dateInDay += n;

	return dateInDay;
}

int CalcNewYear(TDate* date, int dateInDay) {
	if (dateInDay % DAYS_IN_YEAR == 0)
		return dateInDay / DAYS_IN_YEAR - 1;
	else
		return dateInDay / DAYS_IN_YEAR ;
}

int CalcNewMonth(TDate* date, int dateInDay) {
	dateInDay %= DAYS_IN_YEAR;
	if (dateInDay == 0)
		return 12;

	int newMonth = 1;
	while (dateInDay > calendar[newMonth]) {
		dateInDay -= calendar[newMonth];
		++newMonth;
	}
	return newMonth;
}

int CalcNewDay(TDate* date, int dateInDay) {
	int newDay = dateInDay %= DAYS_IN_YEAR;

	if (newDay == 0)
		return december;

	for (int i = 1; newDay > calendar[i]; ++i)
		newDay -= calendar[i];

	return newDay;
}

void AdvanceDate(TDate* date, int n) {
	int dateInDay = CalcDateInDay(date, n);

	date->year = CalcNewYear(date, dateInDay);
	date->month = CalcNewMonth(date, dateInDay);
	date->day = CalcNewDay(date, dateInDay);
}

void PrintDate(TDate* date) {
	printf("%d.%d.%d", date->day, date->month, date->year);
}

int main() {
	TDate date = { 13, 04, 2003 };
	int n;
	assert(scanf("%d", &n) == 1);
	AdvanceDate(&date, n);
	PrintDate(&date);
	return SUCCESS;
}
