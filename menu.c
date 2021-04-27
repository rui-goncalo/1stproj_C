#include <stdio.h>

#include "menu.h"
#include "reports.h"

void h_menu_irs(
        s_arr_irs* single_array,
        s_arr_irs* unique_holder_array,
        s_arr_irs* two_holders_array)
{
    int op;

    do
    {
        fprintf(stdout, H_STRS_IRS_MENU);
        op = h_util_get_int(0, 18, H_STRS_MENU_CHOICE);

        switch (op)
        {
            case 1:
                h_irs_load(single_array, H_PATH_SINGLE);
                break;
            case 2:
                h_irs_print(single_array);
                break;
            case 3:
                h_irs_edit(single_array);
                break;
            case 4:
                h_irs_add(single_array);
                break;
            case 5:
                h_irs_delete(single_array);
                break;
            case 6:
                h_irs_write(single_array, H_PATH_SINGLE);
                break;
            case 7:
                h_irs_load(unique_holder_array, H_PATH_UNIQUE_HOLDER);
                break;
            case 8:
                h_irs_print(unique_holder_array);
                break;
            case 9:
                h_irs_edit(unique_holder_array);
                break;
            case 10:
                h_irs_add(unique_holder_array);
                break;
            case 11:
                h_irs_delete(unique_holder_array);
                break;
            case 12:
                h_irs_write(unique_holder_array, H_PATH_UNIQUE_HOLDER);
                break;
            case 13:
                h_irs_load(two_holders_array, H_PATH_TWO_HOLDERS);
                break;
            case 14:
                h_irs_print(two_holders_array);
                break;
            case 15:
                h_irs_edit(two_holders_array);
                break;
            case 16:
                h_irs_add(two_holders_array);
                break;
            case 17:
                h_irs_delete(two_holders_array);
                break;
            case 18:
                h_irs_write(two_holders_array, H_PATH_TWO_HOLDERS);
                break;
            case 0:
                break;
            default:
                fprintf(stdout, RED("%s\n"), H_STRS_INVALID_INPUT);
                break;
        }
    } while (op != 0);
}

void h_menu_iss(s_arr_iss* iss_array)
{
    int op;

    do
    {
        fprintf(stdout, H_STRS_SEG_SOCIAL_MENU);
        op = h_util_get_int(0, 6, H_STRS_MENU_CHOICE);

        switch (op)
        {
            case 1:
                h_iss_load(iss_array, H_PATH_ISS);
                break;
            case 2:
                h_iss_print(iss_array);
                break;
            case 3:
                h_iss_add(iss_array);
                break;
            case 4:
                h_iss_delete(iss_array);
                break;
            case 5:
                h_iss_edit(iss_array);
                break;
            case 6:
                h_iss_write(iss_array, H_PATH_ISS);
                break;
            case 0:
                break;
            default:
                fprintf(stdout, RED("%s\n"), H_STRS_INVALID_INPUT);
                break;
        }
    } while (op != 0);
}

void h_menu_processing(
        s_arr_irs* single_array,
        s_arr_irs* unique_holder_array,
        s_arr_irs* two_holders_array,
        s_arr_iss* iss_array,
        s_arr_employees* employees_array,
        s_spreadsheet* spreadsheet)
{
    int op;
    int month;

    do
    {
        fprintf(stdout, H_STRS_PROC);
        op = h_util_get_int(0, 10, H_STRS_MENU_CHOICE);

        switch (op)
        {
            case 1:
                h_proc_create(spreadsheet);
                break;
            case 2:
                h_proc_print(spreadsheet, employees_array);
                break;
            case 3:
                h_proc_add(spreadsheet, employees_array);
                break;
            case 4:
                h_proc_edit(spreadsheet);
                break;
            case 5:
                h_proc_delete(spreadsheet);
                break;
            case 6:
                h_proc_perform(
                        spreadsheet,
                        single_array,
                        unique_holder_array,
                        two_holders_array,
                        iss_array,
                        employees_array);
                break;
            case 7:
                h_proc_export_csv(spreadsheet, employees_array);
                break;
            case 8:
                h_proc_write(spreadsheet, h_proc_generate_filename(spreadsheet->month, ".bin"));
                break;
            case 9:
                if (spreadsheet->used > 0)
                {
                    fprintf(
                            stdout, RED("[!] Já existia %s, este sera eliminado\n"),
                            h_calendar_str_from_month(spreadsheet->month));
                    h_proc_free(spreadsheet);
                }
                month = h_util_get_int(1, 12, "Importar Mês? (1-12)") - 1;
                spreadsheet = h_proc_import(month);
                break;
            case 10:
                h_proc_delete_month(spreadsheet);
                break;
            case 0:
                break;
            default:
                puts(H_STRS_INVALID_INPUT);
                break;
        }
    } while (op != 0);
}

void h_menu_employees(s_arr_employees* employees_array, s_arr_iss* iss_array)
{
    int op;

    do
    {
        printf(H_STRS_EMPLOYEES_MENU);
        op = h_util_get_int(0, 6, H_STRS_MENU_CHOICE);

        switch (op)
        {
            case 1:
                if (iss_array == NULL || iss_array->used == 0)
                {
                    h_iss_load(iss_array, H_PATH_ISS);
                }

                h_employees_load(employees_array, H_PATH_EMPLOYEES);
                break;
            case 2:
                h_employees_print(employees_array, iss_array);
                break;
            case 3:
                h_employees_add(employees_array, iss_array);
                break;
            case 4:
                h_employees_delete(employees_array);
                break;
            case 5:
                h_employees_edit(employees_array, iss_array);
                break;
            case 6:
                h_employees_write(employees_array, H_PATH_EMPLOYEES);
                break;
            case 0:
                break;
            default:
                puts(H_STRS_INVALID_INPUT);
                break;
        }
    } while (op != 0);
}

void h_menu_reports(s_arr_employees* employees_array, s_spreadsheet* spreadsheet)
{
    int op;

    do
    {
        fprintf(stdout, H_STRS_REPORTS_MENU);
        op = h_util_get_int(0, 5, H_STRS_MENU_CHOICE);

        switch (op)
        {
            case 1:
                h_reports_senior_employees(employees_array);
                break;
            case 2:
                h_reports_marital_status(employees_array);
                break;
            case 3:
                h_reports_bonus(spreadsheet, employees_array);
                break;
            case 4:
                h_reports_food_allowance(spreadsheet, employees_array);
                break;
            case 5:
                h_reports_percentage_per_dependent(employees_array);
                break;
            case 0:
                break;
            default:
                puts(H_STRS_INVALID_INPUT);
                break;
        }
    } while (op != 0);
}