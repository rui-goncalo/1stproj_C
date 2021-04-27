/**
 * @file iss.h
 * @author Hugo Carvalho, Micael Dias
 * @date 24/12/2020
 * @brief Functions to handle ISS
 */

#ifndef ISS_H
#define ISS_H

#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "strs.h"
#include "util.h"
#include "paths.h"

#define BUFFER_SIZE 64

typedef struct
{
	char* criteria;
	float employer_retention;
	float employee_retention;
} s_iss;

typedef struct
{
	s_iss* data;
	int used;
	int max_capacity;
} s_arr_iss;

/**
 * Alloc an array of ISS
 * @param initial_capacity The initial capacity of the array
 * @return s_arr_iss Returns a ptr to the malloced struct or NULL if an error occurred
 */
s_arr_iss* h_iss_alloc(int initial_capacity);

/**
 * Free an ISS array
 * @param array The array to be freed
 */
void h_iss_free(s_arr_iss* array);

/**
 * Parse a delimited string to an ISS array
 * @param array The ISS array
 * @param str The string to parse
 */
void h_iss_parse(s_arr_iss* array, char* str);

/**
 * Print all elements of an ISS array
 * @param array The ISS array
 */
void h_iss_print(s_arr_iss* array);

/**
 * Add an element to an ISS array
 * @param array The ISS array
 */
void h_iss_add(s_arr_iss* array);

/**
 * Wrapper function to delete an element
 * @param array The ISS array
 */
void h_iss_delete(s_arr_iss* array);

/**
 * Edit an element of an ISS array
 * @param array The ISS array
 */
void h_iss_edit(s_arr_iss* array);

/**
 * Write an ISS array to a CSV (comma separated) file
 * @param array The ISS array
 * @param path The file path to write
 */
void h_iss_write(s_arr_iss* array, const char* path);

/**
 * Loads an ISS table from a given path
 * @param array The ISS array to fill
 * @param path The file path to read
 */
void h_iss_load(s_arr_iss* array, const char* path);

#endif //ISS_H