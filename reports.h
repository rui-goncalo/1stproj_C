/**
 * @file reports.h
 * @author Micael Dias, Rui Gonçalves, Hugo Carvalho
 * @date 7/1/2021
 * @brief Functions for company reports
 */

#ifndef REPORTS_H
#define REPORTS_H

#include "employees.h"
#include "proc.h"

/** Represents the time in years an employee_retention is considered senior */
#define EMPLOYEE_SENIORITY 5
/** Represents the highest food allowance */
#define HIGHER_FOOD_ALLOWANCE 2.00

/**
 * Shows all the senior employees according to EMPLOYEE_SENIORITY
 * @param employees_array The array of employees
 */
void h_reports_senior_employees(s_arr_employees* employees_array);

/**
 * Gets the percentage of married, single, widowed and divorced employees
 * @param employees_array The array of employees
 */
void h_reports_marital_status(s_arr_employees* employees_array);

/**
 * Gets the percentage of employees who have earned a bonus
 * @param spreadsheet The spreadsheet referring to a month
 */
void h_reports_bonus(s_spreadsheet* spreadsheet, s_arr_employees* employees_array);

/**
 * Gets the percentage of employees with the higher food allowance
 * @param spreadsheet The spreadsheet referring to a month
 * @param employees_array The array of employees
 */
void h_reports_food_allowance(s_spreadsheet* spreadsheet, s_arr_employees* employees_array);

/**
 * Gets the percentage occupied by each number of dependents
 * @param array The array of employees
 */
void h_reports_percentage_per_dependent(s_arr_employees* array);

/**
 * Prints the names of the employees in each category
 * @param array The array of employees
 * @param integer The number of dependents so search for
 */
void h_reports_percentage_per_dependent_print(s_arr_employees* array, int dependents);

#endif //REPORTS_H
