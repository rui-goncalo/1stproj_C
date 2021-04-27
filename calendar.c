#include <stdio.h>

#include "calendar.h"
#include "colors.h"

void h_calendar_get_date(s_date* date, const char* msg)
{
	int day, month, year, error;

	do
	{
		error = 0;
		printf("%s (DD/MM/YYYY)\n", msg);
		scanf("%d/%d/%d", &day, &month, &year);

		if (h_calendar_check_date(day, month, year) == 0)
		{
			error = 1;
		}

		if (error == 1)
		{
			puts(RED("[!] Data incorreta"));
		}

	} while (error == 1);

	date->year = year;
	date->month = month;
	date->day = day;
}

int h_calendar_leap_year(int year)
{
	return (year % 400 == 0) || (year % 4 == 0 && year % 100 != 0);
}

int h_calendar_days_in_month(e_month month)
{
	if (month == FEB || month == APR || month == JUN || month == SEP || month == NOV)
	{
		return 30;
	}

	return 31;
}

int h_calendar_check_date(int day, int month, int year)
{
	if (year < 1000 || year > 9999)
	{
		return 0;
	}

	if (month < JAN || month > DEC)
	{
		return 0;
	}

	if (month == FEB && h_calendar_leap_year(year) == 1)
	{ // days 29
		if (day < 1 || day > 29)
		{
			return 0;
		}
	}

	if (month == FEB && h_calendar_leap_year(year) == 0)
	{ // days 28
		if (day < 1 || day > 28)
		{
			return 0;
		}
	}

	if (day < 1 || day > h_calendar_days_in_month(month))
	{
		return 0;
	}

	return 1;
}

char* h_calendar_str_from_month(e_month month)
{
	char* strings[] = {"jan", "feb", "mar", "apr", "may", "jun", "jul", "aug", "sep", "oct", "nov", "dec"};

	return strings[month];
}

struct tm* h_calendar_init_local_time()
{
	time_t time_now;
	struct tm* local_time;

	time_now = time(&time_now);
	local_time = localtime(&time_now);

	return local_time;
}

int h_calendar_get_year(struct tm* local_time)
{
	return local_time->tm_year + 1900; // get year_now after 1900
}