/**
 * @file calendar.h
 * @author Rui Gonçalves, Micael Dias
 * @date 27/12/2020
 * @brief Helper functions to handle Dates
 */

#ifndef CALENDAR_H
#define CALENDAR_H

#include <time.h>

/**
 * @struct s_date
 * A structure to represent dates
 */
typedef struct
{
	int day;
	int month;
	int year;
} s_date;

/**
 * @enum e_month Represents the Months from 1 to 12
 */
typedef enum
{
	JAN = 1,
	FEB = 2,
	MAR = 3,
	APR = 4,
	MAY = 5,
	JUN = 6,
	JUL = 7,
	AUG = 8,
	SEP = 9,
	OCT = 10,
	NOV = 11,
	DEC = 12
} e_month;

/**
 * Gets a date from stdin
 * @param date The struct to fill
 * @param msg The message to display
 */
void h_calendar_get_date(s_date* date, const char* msg);

/**
 * Gets the number of days in a month
 * @param month The month to calculate
 * @return int Returns the nummber of days
 */
int h_calendar_days_in_month(e_month month);

/**
 * Checks if a date is valid
 * @param day The day to validate depends on the onth
 * @param month The month to validate from 1 to 12
 * @param year The year to validate, from 1000 to 9999
 * @return int Return 0 if fail, otherwise returns 1
 */
int h_calendar_check_date(int day, int month, int year);

/**
 * Checks if it is a leap year
 * @param year The year to validate
 * @return int Returns 1 if is a leap year, otherwise returns 0
 */
int h_calendar_leap_year(int year);

/**
 * Converts e_month enumeration to string
 * @param month The month to convert
 * @return char* Returns the month into a string
 */
char* h_calendar_str_from_month(e_month month);

/**
 * Initializes system time
 * @return Returns a broken-down time struct (ISO C)
 */
struct tm* h_calendar_init_local_time();

/**
 * Gets the current year
 * @param local_time The system time struct
 * @return int Returns the current year
 */
int h_calendar_get_year(struct tm* local_time);

#endif //CALENDAR_H
