/**
 * @file irs.h
 * @author Micael Dias
 * @date 10/12/20
 * @brief Functions to handle IRS
 */

#ifndef IRS_H
#define IRS_H

#define CSV_COLUMN_DELIMITER ','
#define CSV_NEW_LINE_DELIMITER '\n'
#define CSV_BUFFER 50
#define MAX_DEPENDENT_NUMBER 5
#define MAX_REMUNERATION 30000.0f
#define MAX_PERCENTAGE 100.0f

/** @enum e_type Specification of monthly remuneration */
typedef enum
{
	H_IRS_UP_TO, /**< Up to a value */
	H_IRS_BEYOND /**< Beyond a value */
} e_type;

/** @struct s_element Represents an element of a IRS array */
typedef struct
{
	e_type monthly_pay_type; /**< Represents the specification of the remunreation */
	float monthly_pay_value; /**< Represents the monthy pay value in € */
	float* percentage_per_dependent; /**< Represents an array of dependents */
} s_element;

/** @struct s_arr_irs Represents an array of IRS */
typedef struct
{
	s_element* elements; /**< Handles elements from the array */
	int used; /**< Tracks the used capacity of the array */
	int max_capacity; /**< Tracks the max capacity of the array */
} s_arr_irs;

/**
 * @typedef Defines a new type named h_irs_pair_func to
 * a function who takes as arguments an s_irs*, a char*,
 * an int* and returns nothing
 *
 * @brief Used to a complex situation, such as parsing
 * where there are functions as arguments
 */
typedef void (* h_irs_pair_func)(s_element*, char*, int*);

/**
 * Alloc an array of IRS
 * @param initial_capacity The initial capacity of the array
 * @return s_arr_irs* Returns a ptr to the malloced struct or NULL if an error occurred
 */
s_arr_irs* h_irs_alloc(int initial_capacity);

/**
 * Free an IRS array
 * @param array The array to be freed
 */
void h_irs_free(s_arr_irs* array);

/**
 * Parse a delimited string to an IRS array
 * @param array The IRS array to fill
 * @param str The delimited string
 * @param pair_func A recursive function to pair which value
 */
void h_irs_parse(s_arr_irs* array, const char* str, h_irs_pair_func pair_func);

/**
 * Write an IRS array to a CSV (comma separated) file
 * @param array The IRS array
 * @param path The path to write
 */
void h_irs_write(s_arr_irs* array, const char* path);

/**
 * Add an element to an IRS array
 * @param array The IRS array
 */
void h_irs_add(s_arr_irs* array);

/**
 * Wrapper function to delete an element
 * @param array The IRS array
 */
void h_irs_delete(s_arr_irs* array);

/**
 * Delete an element of an IRS array
 * @param array The IRS array
 * @param index The position to delete
 */
void h_irs_delete_element(s_arr_irs* array, int index);

/**
 * Print a single line
 * @param element The struct to print
 */
void h_irs_print_line(s_element element);

/**
 * Print all elements of an IRS array
 * @param array The IRS array
 */
void h_irs_print(s_arr_irs* array);

/**
 * Edit an element of an IRS array
 * @param array The IRS array
 */
void h_irs_edit(s_arr_irs* array);

/**
 * Pair values from str to corresponding elements field
 * @param element The struct fo fill
 * @param str The value to pair
 * @param dependent Updates the dependent number from a ptr
 */
void h_irs_pair(s_element* element, char* str, int* dependent);

/**
 * Loads an IRS table from a given path
 * @param s_arr_irs The IRS array to fill
 * @param path The path to load
 */
void h_irs_load(s_arr_irs* irs_array, char* path);

#endif //IRS_H