#ifndef DATE_H
#define DATE_H

#include <stdbool.h>

struct Date {
	int month;
	int day;
	int year;
};

bool dates_are_equal(struct Date, struct Date);

struct Date create_date(int, int, int);
#endif //DATE_H
