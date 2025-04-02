#include <stdio.h>
#include <stdbool.h>

#include "Date.h"

bool dates_are_equal(struct Date d1, struct Date d2)
{
	if (d1.month != d2.month)
	{
		return false;
	}
	if (d1.day != d2.day)
	{
		return false;
	}
	if (d1.year != d2.year)
	{
		return false;
	}
	return true;
}

bool is_leap_year(int year)
{
	if (year % 4 == 0)
	{
		if (year % 100 != 0)
		{
			return true;
		}
	}
	return false;
}

//currently doesn't handle out of range entries very well.
struct Date create_date(int month, int day, int year)
{
	if (month <= 0 || month > 12)
	{
		printf("Invalid entry, month out of range. Enter between 1 and 12.\n");
	}
	if (month == 2)
	{
		if (is_leap_year(year))
		{
			if (day <= 0 || day > 29)
			{
				printf("Invalid entry, day out of range. Enter between 1 and 29.\n");
			}
		} else {
			if (day <= 0 || day > 28)
			{
				printf("Invalid entry, day out of range. Enter between 1 and 28.\n");
			}
		}
	} else if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 || month == 10 || month == 12)
	{
		if (day <= 0 || day > 31)
		{
			printf("Invalid entry, day out of range. Enter between 1 and 31.\n");
		}
	} else if (month == 4 || month == 6 || month == 9 || month == 11)
	{
		if (day <= 0 || day > 30)
		{
			printf("Invalid entry, day out of range. Enter between 1 and 30.\n");
		}
	}

	struct Date return_date;
	return_date.month = month;
	return_date.day = day;
	return_date.year = year;
	
	return return_date;
}
