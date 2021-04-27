/**
 * @file proc.h
 * @author Micael Dias, Hugo Carvalho
 * @date 26/12/20
 * @brief Salary Processing
 */

#ifndef PROC_H
#define PROC_H

#include "irs.h"
#include "iss.h"
#include "calendar.h"
#include "employees.h"

#define MAX_FILENAME 256
/** Base bonuses awarded */
#define BASE_BONUS 1.0f
/** Bonuses awarded for 20 working days */
#define BONUS_20_DAYS 1.05f
/** Bonuses awarded for 17 working days */
#define BONUS_17_DAYS 1.02f

/**
 * @struct s_details
 * A struct that represents working days per worker
 */
typedef struct
{
	int cod_employee; /**< Reprents the employee_retention code */
	int full_days; /**< Represents the number of full days worked */
	int half_days; /**< Represents the number of half days worked */
	int weekend_days; /**< Represents number of the weekends worked */
	int absent_days; /**< Represents the number of days missed */
	float gross_pay; /**< Salary before taxes */
	float net_pay; /**< Salary afeter taxes */
	float bonus; /**< Bonus awarded */
	float food_allowance; /**< Food allowance calculated */
	float irs_retention; /**< IRS retention */
	float iss_retention_employer; /**< ISS retention for employer_retention */
	float iss_retention_employee; /**< ISS retention for employee_retention */
	float employer_charge; /**< Total employer_retention charge */
} s_details;

/**
 * @struct s_spreadsheet
 * A struct that represents a spreadsheet for a given month
 */
typedef struct
{
	s_details* details; /**< Array of details **/
	e_month month; /**< Represent the month of the spreadsheet **/
	int month_is_set; /** Determine if a month is set */
	int is_processed; /** Determine if a month was processed */
	int used; /**< Tracks used capacity of the array **/
	int max_capacity; /**< Tracks max capacity of the array **/
} s_spreadsheet;

/**
 * Allocs an array of structs (s_arr_spreadsheet),
 * containing the month (enum) and details (s_details) for the month
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_alloc(int initial_capacity);

/**
 * Opens a binary file in read mode onto a spreadsheet
 * @param filename Path of the file
 * @param month Month to import
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_read(const char* filename, e_month month);

/**
 * Loads a spreadsheet into memory by asking a month to import
 * @param month The month to import
 * @return s_spreadsheet Returns a ptr to a malloced struct of s_spreadsheet returns NULL if failure
 */
s_spreadsheet* h_proc_import(e_month month);

/**
 * Writes into a binary file a spreadsheet
 * @param spreadsheet The spreadsheet referring to a month
 */
void h_proc_write(s_spreadsheet* spreadsheet, const char* path);

/**
 * Add details to an existing month
 * @param spreadsheet Ptr to a spreadsheet
 * @param arr_employees An array of employees
 */
void h_proc_add(s_spreadsheet* spreadsheet, s_arr_employees* arr_employees);

/**
 * Edit details from an existing month
 * @param spreadsheet Ptr to a spreadsheet
 */
void h_proc_edit(s_spreadsheet* spreadsheet);

/**
 * Prints a spreadsheet
 * @param spreadsheet Ptr to spreadsheet
 * @param employees_array Array of employees
 */
void h_proc_print(s_spreadsheet* spreadsheet, s_arr_employees* employees_array);

/**
 * Deletes details in a spreadsheet
 * @param spreadsheet Ptr to spreadsheet
 */
void h_proc_delete(s_spreadsheet* spreadsheet);

/**
 * Deletes month and its date
 * @param spreadsheet Ptr to spreadsheet
 */
void h_proc_delete_month(s_spreadsheet* spreadsheet);

/**
 * Free a spreadsheet
 * @param spreadsheet Ptr to spreadsheet
 */
void h_proc_free(s_spreadsheet* spreadsheet);

/**
 * Exports a spreadsheet to CSV
 * @param spreadsheet Ptr to spreadsheet
 * @param employees_array Array of employees
 */
void h_proc_export_csv(s_spreadsheet* spreadsheet, s_arr_employees* employees_array);

/**
 * Generate a filename from a given month and an extension
 * @param month Month to generate
 * @param extension The file extension
 * @return char* Return the generated filename
 */
char* h_proc_generate_filename(e_month month, const char* extension);

/**
 * Perform the salary calculations
 * @param spreadsheet A Spreadsheet referring a month
 * @param single_array The single IRS table
 * @param unique_holder_array The unique holder IRS table
 * @param two_holders_array The two holders IRS table
 * @param iss_array An ISS table
 * @param employees_array The employees array
 */
void h_proc_perform(
		s_spreadsheet* spreadsheet,
		s_arr_irs* single_array,
		s_arr_irs* unique_holder_array,
		s_arr_irs* two_holders_array,
		s_arr_iss* iss_array,
		s_arr_employees* employees_array
);

/**
 * Checks if the code is one of the employees
 * @param employees_array The employees array to search
 * @param code The code to check
 * @return Returns the code of the employee_retention, 0 if not found
 */
int h_proc_get_employee_index(s_arr_employees* employees_array, int code);

/**
 * Gets the retention percentage for IRS based on the salary and number of dependents
 * @param irs_array An IRS table
 * @param dependents The number of dependents
 * @param raw_salary The salary before retentions
 * @return Returns the retention percentage
 */
float h_proc_get_retention_percentage(s_arr_irs* irs_array, int dependents, float raw_salary);

/**
 * Creates a spreadsheet with a given month
 * @param spreadsheet The struct to fill
 */
void h_proc_create(s_spreadsheet* spreadsheet);

#endif //PROC_H
