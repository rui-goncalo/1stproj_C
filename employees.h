/**
 * @file employees.h
 * @author Rui Gonçalves, Micael Dias
 * @date 11/12/2020
 * @brief Functions to handle employees
 */

#ifndef EMPLOYEES_H
#define EMPLOYEES_H

#include "calendar.h"
#include "iss.h"
#include "colors.h"

#define BUFFER_SIZE 64
#define MAX_VALUE 9999
#define CSV_COLUMN_DELIMITER ','
#define CSV_NEW_LINE_DELIMITER '\n'
#define CSV_BUFFER 50
#define PHONE_NUMBER_SIZE 9
#define MAX_HOURLY_RATE 200
#define MAX_FOOD_ALLOWANCE 20

#define PRINT_TEMPLATE_STRING \
"%d | %s | %s | %d | %d Dependentes | %s | %s | " \
"%d/%d/%d | %d/%d/%d | %d/%d/%d | %.2f€ | %.2f€ | %d Titular(es) %s\n"

/** @enum e_columns Enumeration w/ the number of columns in the csv file */
typedef enum
{
	COL_CODE_FUNC = 1,
	COL_FIRST_NAME = 2,
	COL_LAST_NAME = 3,
	COL_PHONE_NUMBER = 4,
	COL_MARITAL_STATUS = 5,
	COL_ROLE = 6,
	COL_NUM_DEPENDENTS = 7,
	COL_BIRTHDAY = 8,
	COL_ENTRY_DATE = 9,
	COL_LEAVING_DATE = 10,
	COL_HOURLY_RATE = 11,
	COL_BASE_FOOD_ALLOWANCE = 12,
	COL_HOLDERS = 13
} e_columns;

/** @enum e_holders ?? */
typedef enum
{
	NONE = 0,
	UNIQUE_HOLDER = 1,
	TWO_HOLDERS = 2
} e_holders;

/** @enum e_marital_status Represents the marital status of an employee */
typedef enum
{
	SINGLE = 0,
	MARRIED = 1,
	DIVORCED = 2,
	WIDOWED = 3
} e_marital_status;

/** @struct s_employee Represents a single employee */
typedef struct
{
	int cod_employee;
	int role;
	int dependents;
	int phone_number;
	float hourly_rate;
	float base_food_allowance;
	char* first_name;
	char* last_name;
	e_holders holders;
	e_marital_status marital_status;
	s_date* birthday, * entry_date, * leaving_date;
	int removed;
} s_employee;

/** @struct s_arr_employees Represents an array of employees */
typedef struct
{
	s_employee* employees;
	int used;
	int max_capacity;
} s_arr_employees;

/**
 * Alloc an array of employees
 * @param initial_capacity The initial capacity of the array
 * @return Returns a ptr to the malloced struct or NULL if an error occurred
 */
s_arr_employees* h_employees_alloc(int initial_capacity);

/**
 * Randomizes a employee code
 * @return Return the generated code
 */
int h_employees_randomize();

/**
 * Get marital status from stdin
 * @return Returns the read status
 */
int h_employees_get_marital_status();

/**
 * Get a phone number from stdin
 * @return Returns the read phone number
 */
int h_employees_get_phone_number();

/**
 * Get employee struct field from stdin
 * @param employee The struct to fill
 * @param iss_array The ISS table to add or edit the role
 */
void h_employees_get_fields(s_employee* employee, s_arr_iss* iss_array);

/**
 * Add an employee to the array
 * @param array The array of employees
 */
void h_employees_add(s_arr_employees* array, s_arr_iss* iss_array);

/**
 * Pair values from str to corresponding elements field
 * @param employee The struct to fill
 * @param str The value to pair
 * @param column Updates the column to pick
 */
void h_employees_pair(s_employee* employee, char* str, int column);

/**
 * Parse a delimited string to an array of employees
 * @param array The array to fill
 * @param str The string to parse
 */
void h_employees_parse(s_arr_employees* array, const char* str);

/**
 * Print all records of employees
 * @param array The array of employees
 * @param iss_array The ISS table to show the role as a string
 */
void h_employees_print(s_arr_employees* array, s_arr_iss* iss_array);

/**
 * Edit an employee
 * @param array The array of employees
 * @param iss_array The ISS table to edit the role
 */
void h_employees_edit(s_arr_employees* array, s_arr_iss* iss_array);

/**
 * Check if a phone number is valid
 * @param str The phone number as a string
 * @return Returns 0 if success or -1 if fail
 */
int h_employees_verify_phone(char* str);

/**
 * Converts marital status enum to str for write on file or display
 * @param status The enum item to convert
 * @param display Set to 1 to get a string for display purposes
 * @return char* Returns a string corresponding to the specified status
 */
char* h_employees_str_from_marital_status(e_marital_status status, int display);

/**
 * Marks an employee as removed, not deleting his record
 * @param array The array of employees
 */
void h_employees_delete(s_arr_employees* array);

/**
 * Write an array of employees to a CSV (comma separated) file
 * @param array The array of employees
 * @param path The file path to write
 */
void h_employees_write(s_arr_employees* array, const char* path);

/**
 * Converts holder enum to str
 * @param holder The enum item to convert
 * @return char* Returns a string corresponding to the specified holder
 */
char* h_employees_str_from_holders(e_holders holder);

/**
 * Loads an Employees table from a given path
 * @param array The Employees array to fill
 * @param path The file path to read
 */
void h_employees_load(s_arr_employees* array, const char* path);

/**
 * Free an array of employees
 * @param array The array to be freed
 */
void h_employees_free(s_arr_employees* array);

#endif //EMPLOYEES_H