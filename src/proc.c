#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#include "proc.h"

#define INITIAL_CAPACITY 50

s_spreadsheet* h_proc_alloc(int initial_capacity)
{
	s_spreadsheet* spreadsheet;

	spreadsheet = malloc(sizeof(s_details));
	if (spreadsheet == NULL)
	{
		return NULL;
	}

	spreadsheet->details = malloc(initial_capacity * sizeof(s_details));
	if (spreadsheet->details == NULL)
	{
		return NULL;
	}

	spreadsheet->month_is_set = 0;
	spreadsheet->is_processed = 0;
	spreadsheet->used = 0;
	spreadsheet->max_capacity = initial_capacity;

	return spreadsheet;
}

void h_proc_free(s_spreadsheet* spreadsheet)
{
	if (spreadsheet == NULL)
	{
		return;
	}

	free(spreadsheet->details);
	free(spreadsheet);
}

s_spreadsheet* h_proc_import(e_month month)
{
	char* path;
	s_spreadsheet* spreadsheet;

	path = h_proc_generate_filename(month, ".bin");
	if (path == NULL)
	{
		return NULL;
	}

	if (access(path, F_OK) == -1)
	{
		printf("%s: %s\n", H_STRS_FILE_NOT_FOUND, path);
		free(path);
		return NULL;
	}

	spreadsheet = h_proc_read(path, month);
	if (spreadsheet == NULL)
	{
		free(path);
		return NULL;
	}

	free(path);
	return spreadsheet;
}

s_spreadsheet* h_proc_read(const char* filename, e_month month)
{
	FILE* fp;
	s_spreadsheet* spreadsheet;
	int i;

	fprintf(stdout, YELLOW("[!] Importing: %s\n"), filename);

	fp = fopen(filename, "rb");
	if (fp == NULL)
	{
		return NULL;
	}

	spreadsheet = h_proc_alloc(INITIAL_CAPACITY);
	if (spreadsheet == NULL)
	{
		return NULL;
	}

	fread(&spreadsheet->used, sizeof(spreadsheet->used), 1, fp);
	fread(&spreadsheet->month, sizeof(spreadsheet->month), 1, fp);
	fread(&spreadsheet->month_is_set, sizeof(spreadsheet->month_is_set), 1, fp);
	fread(&spreadsheet->is_processed, sizeof(spreadsheet->is_processed), 1, fp);
	fread(&spreadsheet->max_capacity, sizeof(spreadsheet->max_capacity), 1, fp);

	for (i = 0; i < spreadsheet->used; i++)
	{
		fread(&spreadsheet->details[i].cod_employee, sizeof(spreadsheet->details[i].cod_employee), 1, fp);
		fread(&spreadsheet->details[i].full_days, sizeof(spreadsheet->details[i].full_days), 1, fp);
		fread(&spreadsheet->details[i].half_days, sizeof(spreadsheet->details[i].half_days), 1, fp);
		fread(&spreadsheet->details[i].weekend_days, sizeof(spreadsheet->details[i].weekend_days), 1, fp);
		fread(&spreadsheet->details[i].absent_days, sizeof(spreadsheet->details[i].absent_days), 1, fp);
		fread(&spreadsheet->details[i].employer_charge, sizeof(spreadsheet->details[i].employer_charge), 1, fp);
		fread(&spreadsheet->details[i].iss_retention_employer, sizeof(spreadsheet->details[i].iss_retention_employer), 1, fp);
		fread(&spreadsheet->details[i].iss_retention_employee, sizeof(spreadsheet->details[i].iss_retention_employee), 1, fp);
		fread(&spreadsheet->details[i].irs_retention, sizeof(spreadsheet->details[i].irs_retention), 1, fp);
		fread(&spreadsheet->details[i].food_allowance, sizeof(spreadsheet->details[i].food_allowance), 1, fp);
		fread(&spreadsheet->details[i].bonus, sizeof(spreadsheet->details[i].bonus), 1, fp);
		fread(&spreadsheet->details[i].net_pay, sizeof(spreadsheet->details[i].net_pay), 1, fp);
		fread(&spreadsheet->details[i].gross_pay, sizeof(spreadsheet->details[i].gross_pay), 1, fp);
	}

	return spreadsheet;
}

void h_proc_add(s_spreadsheet* spreadsheet, s_arr_employees* arr_employees)
{
	int i;
	int flag;
	int count;
	int max_days;
	int employee_index;

	if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}
	else if (spreadsheet->is_processed)
	{
		puts(H_STRS_ALREADY_PROCESSED);
		return;
	}


	if (arr_employees == NULL || arr_employees->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}

	if (spreadsheet->used == spreadsheet->max_capacity)
	{
		spreadsheet->details = realloc(spreadsheet->details, (spreadsheet->max_capacity * 2) * sizeof(s_details));
		if (spreadsheet->details == NULL)
		{
			puts(H_STRS_MALLOC_FAILED);
			return;
		}

		spreadsheet->max_capacity *= 2;
	}

	max_days = h_calendar_days_in_month(spreadsheet->month);

	count = 0;
	for (i = 0; i < arr_employees->used; i++)
	{
		flag = 0;
		for (int j = 0; j < spreadsheet->used; j++)
		{
			if (arr_employees->employees[i].cod_employee == spreadsheet->details[j].cod_employee)
			{
				flag = 1;
				count++;
			}
		}

		if (flag == 0)
		{
			printf(YELLOW("[%d] "), i);
		    printf(
					GREEN("%d | %s %s\n"),
					arr_employees->employees[i].cod_employee,
					arr_employees->employees[i].first_name,
					arr_employees->employees[i].last_name);
		}
	}

	employee_index = h_util_get_int(0, arr_employees->used - 1, "Adicionar funcionário: ");

	for (i = 0; i < spreadsheet->used; i++)
	{
		if (arr_employees->employees[employee_index].cod_employee == spreadsheet->details[i].cod_employee)
		{
			printf(RED("O funcionário já foi adicionado.\n"));
			return;
		}
	}

	spreadsheet->details[spreadsheet->used].cod_employee = arr_employees->employees[employee_index].cod_employee;
	spreadsheet->details[spreadsheet->used].full_days = h_util_get_int(0, max_days, "Dias completos: ");
	spreadsheet->details[spreadsheet->used].half_days = h_util_get_int(0, max_days, "Meios dias: ");
	spreadsheet->details[spreadsheet->used].weekend_days = h_util_get_int(0, 5, "Fins de semana: ");
	spreadsheet->details[spreadsheet->used].absent_days = h_util_get_int(0, max_days, "Faltas: ");
	spreadsheet->used++;

}

void h_proc_print(s_spreadsheet* spreadsheet, s_arr_employees* employees_array)
{
	int i;
	int j;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}

	printf(YELLOW("N Registos encontrados: %d\n"), spreadsheet->used);

	if (spreadsheet->is_processed)
	{
		printf(H_STRS_PROCESSED_TABLE_HEADER);
	}
	else
	{
		printf(H_STRS_PROC_TABLE_HEADER);
	}

	for (i = 0; i < spreadsheet->used; i++)
	{
		for (j = 0; j < employees_array->used; j++)
		{
			if (spreadsheet->details[i].cod_employee == employees_array->employees[j].cod_employee)
			{
				printf(YELLOW("[%d] "), i);
				printf(
						GREEN("[%d] %s %s | %d | %d | %d | %d"),
						spreadsheet->details[i].cod_employee,
						employees_array->employees[j].first_name,
						employees_array->employees[j].last_name,
						spreadsheet->details[i].full_days,
						spreadsheet->details[i].half_days,
						spreadsheet->details[i].weekend_days,
						spreadsheet->details[i].absent_days
				);
			}
		}

		if (spreadsheet->is_processed)
		{
			printf(GREEN(" | "));
			printf(
					BLUE("%.2f€ | %.2f€ | %.2f€ | %.2f€ | %.2f€ | %.2f€ "),
					spreadsheet->details[i].gross_pay,
					spreadsheet->details[i].net_pay,
					spreadsheet->details[i].food_allowance,
					spreadsheet->details[i].irs_retention,
					spreadsheet->details[i].iss_retention_employee,
					spreadsheet->details[i].iss_retention_employer);

			if (spreadsheet->details[i].bonus == BASE_BONUS)
			{
				printf(GREEN("[Base]"));
			}
			else if (spreadsheet->details[i].bonus == BONUS_17_DAYS)
			{
				printf(GREEN("[17 dias]"));
			}
			else if (spreadsheet->details[i].bonus == BONUS_20_DAYS)
			{
				printf(GREEN("[20 dias]"));
			}

			printf(BLUE(" %.2f€ | %.2f€"), spreadsheet->details[i].net_pay, spreadsheet->details[i].employer_charge);
		}

		printf("\n");
	}
}

void h_proc_edit(s_spreadsheet* spreadsheet)
{
	int index;
	int max_days;
	int op;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}
	else if (spreadsheet->is_processed)
	{
		puts(H_STRS_ALREADY_PROCESSED);
		return;
	}

	index = h_util_get_int(0, spreadsheet->used, H_STRS_EDIT);

	fprintf(stdout, H_STRS_PROC_TABLE_HEADER);
	fprintf(stdout, "Mês: %s\n", h_calendar_str_from_month(spreadsheet->month));
	fprintf(
			stdout, "%d | %d | %d | %d | %d | %d\n",
			index,
			spreadsheet->details[index].cod_employee,
			spreadsheet->details[index].full_days,
			spreadsheet->details[index].half_days,
			spreadsheet->details[index].weekend_days,
			spreadsheet->details[index].absent_days
	);

	op = h_util_get_int(0, 1, "Quer editar o mês correpondente?\n 1. Sim\n 0. Não");
	if (op == 1)
	{
		spreadsheet->month = h_util_get_int(1, 12, "Novo mês: ") - 1;
	}

	max_days = h_calendar_days_in_month(spreadsheet->month);
	spreadsheet->details[index].full_days = h_util_get_int(0, max_days, "Dias completos");
	spreadsheet->details[index].half_days = h_util_get_int(0, max_days, "Meios dias");
	spreadsheet->details[index].weekend_days = h_util_get_int(0, 5, "Fins de semana");
	spreadsheet->details[index].absent_days = h_util_get_int(0, max_days, "Faltas");
}

void h_proc_delete(s_spreadsheet* spreadsheet)
{
	int index;
	int i;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}
	else if (spreadsheet->is_processed)
	{
		puts(H_STRS_ALREADY_PROCESSED);
		return;
	}

	fprintf(stdout, "Registos: %d\n", spreadsheet->used);
	index = h_util_get_int(0, spreadsheet->used, H_STRS_DELETE);

	for (i = index; i < spreadsheet->used - 1; i++)
	{
		spreadsheet->details[i] = spreadsheet->details[i + 1];
	}

	spreadsheet->used--;
}

char* h_proc_generate_filename(e_month month, const char* extension)
{
	const char* month_str;
	char* filename;

	month_str = h_calendar_str_from_month(month);
	if (month_str == NULL)
	{
		return NULL;
	}

	filename = malloc(MAX_FILENAME * sizeof(char));
	if (filename == NULL)
	{
		return NULL;
	}

	if (memset(filename, '\0', MAX_FILENAME) == NULL)
	{
		return NULL;
	}

	if (strcat(filename, "../data/spreadsheet_") == NULL)
	{
		return NULL;
	}

	if (strcat(filename, month_str) == NULL)
	{
		return NULL;
	}

	if (strcat(filename, extension) == NULL)
	{
		return NULL;
	}

	return filename;
}

void h_proc_export_csv(s_spreadsheet* spreadsheet, s_arr_employees* employees_array)
{
	int i;
	int j;
	FILE* fp;
	char* filename;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}

	filename = h_proc_generate_filename(spreadsheet->month, ".csv");
	if (filename == NULL)
	{
		return;
	}

	fp = fopen(filename, "w");
	if (fp == NULL)
	{
		puts(RED("[!] Impossivel exportar"));
		return;
	}

	free(filename);

	for (i = 0; i < spreadsheet->used; i++)
	{
		for (j = 0; j < employees_array->used; j++)
		{
			if (spreadsheet->details[i].cod_employee == employees_array->employees[j].cod_employee)
			{
				fprintf(
						fp, "%d,%s,%s,%d,%d,%d,%d,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f,%.2f\n",
						spreadsheet->details[i].cod_employee,
						employees_array->employees[j].first_name,
						employees_array->employees[j].last_name,
						spreadsheet->details[i].full_days,
						spreadsheet->details[i].half_days,
						spreadsheet->details[i].weekend_days,
						spreadsheet->details[i].absent_days,
						spreadsheet->details[i].gross_pay,
						spreadsheet->details[i].food_allowance,
						spreadsheet->details[i].irs_retention,
						spreadsheet->details[i].iss_retention_employee,
						spreadsheet->details[i].iss_retention_employer,
                        spreadsheet->details[i].net_pay,
                        spreadsheet->details[i].employer_charge);
			}
		}
	}

	fclose(fp);

	fprintf(stdout, YELLOW("[!] Ficheiro exportado com sucesso\n"));
}

void h_proc_perform(
		s_spreadsheet* spreadsheet,
		s_arr_irs* single_array,
		s_arr_irs* unique_holder_array,
		s_arr_irs* two_holders_array,
		s_arr_iss* iss_array,
		s_arr_employees* employees_array)
{
	int i;
	int emp_index;
	float days_worked;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}
	else if (spreadsheet->month_is_set == 0)
	{
		puts(H_STRS_MONTH_NOT_CREATED);
		return;
	}
	else if (spreadsheet->is_processed)
	{
		puts(H_STRS_ALREADY_PROCESSED);
		return;
	}

	if (single_array->used == 0)
	{
		printf("%s: %s\n", H_STRS_IRS_ERROR_INIT, "Não casado");
		return;
	}
	else if (unique_holder_array->used == 0)
	{
		printf("%s: %s\n", H_STRS_IRS_ERROR_INIT, "Único titular");
		return;
	}
	else if (two_holders_array->used == 0)
	{
		printf("%s: %s\n", H_STRS_IRS_ERROR_INIT, "Dois titutales");
		return;
	}

	if (iss_array->used == 0)
	{
		puts(H_STRS_ISS_ERROR_INIT);
		return;
	}

	if (employees_array->used == 0)
	{
		puts(H_STRS_EMPLOYEES_ERROR_INIT);
		return;
	}

	for (i = 0; i < spreadsheet->used; i++)
	{
		emp_index = h_proc_get_employee_index(employees_array, spreadsheet->details[i].cod_employee);

		// Calculo dos Dias Trabalhados e o Bonus Correspondente
		days_worked = (float)spreadsheet->details[i].full_days +
					  (float)spreadsheet->details[i].half_days * 0.5f +
					  (float)spreadsheet->details[i].weekend_days;

		// Calculo do Salário Bruto
		spreadsheet->details[i].gross_pay =
				(float)spreadsheet->details[i].full_days * employees_array->employees[emp_index].hourly_rate +
				(float)spreadsheet->details[i].half_days * employees_array->employees[emp_index].hourly_rate * 0.5f +
				(float)spreadsheet->details[i].weekend_days * employees_array->employees[emp_index].hourly_rate * 1.5f;

		if (days_worked > 20)
		{
			spreadsheet->details[i].bonus = BONUS_20_DAYS;
		}
		else if (days_worked > 17)
		{
			spreadsheet->details[i].bonus = BONUS_17_DAYS;
		}
		else
		{
			spreadsheet->details[i].bonus = BASE_BONUS;
		}

		spreadsheet->details[i].gross_pay *= spreadsheet->details[i].bonus;

		spreadsheet->details[i].food_allowance =
				(float)spreadsheet->details[i].full_days * employees_array->employees[emp_index].base_food_allowance +
				(float)spreadsheet->details[i].weekend_days * employees_array->employees[emp_index].base_food_allowance;

		spreadsheet->details[i].gross_pay += spreadsheet->details[i].food_allowance;

		// Calculo da retenção pelo IRS
		switch (employees_array->employees[emp_index].holders)
		{
			case NONE:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage(
						single_array, employees_array->employees[emp_index].dependents,
						spreadsheet->details[i].gross_pay);
				break;
			case UNIQUE_HOLDER:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage(
						unique_holder_array, employees_array->employees[emp_index].dependents,
						spreadsheet->details[i].gross_pay);
				break;
			case TWO_HOLDERS:
				spreadsheet->details[i].irs_retention = h_proc_get_retention_percentage(
						two_holders_array, employees_array->employees[emp_index].dependents,
						spreadsheet->details[i].gross_pay);
				break;
		}

		spreadsheet->details[i].irs_retention *= spreadsheet->details[i].gross_pay;

		// Calculo da retenção pela Segurança social
		spreadsheet->details[i].iss_retention_employer = spreadsheet->details[i].gross_pay *
														 iss_array->data[employees_array->employees[emp_index].role].employer_retention /
														 100.0f;

		spreadsheet->details[i].iss_retention_employee = spreadsheet->details[i].gross_pay *
														 iss_array->data[employees_array->employees[emp_index].role].employee_retention /
														 100.0f;

		// Calculo do Salário Liquido
		spreadsheet->details[i].net_pay = spreadsheet->details[i].gross_pay -
										  spreadsheet->details[i].iss_retention_employee -
										  spreadsheet->details[i].irs_retention;

		// Encargo Total do Empregador
		spreadsheet->details[i].employer_charge =
				spreadsheet->details[i].gross_pay + spreadsheet->details[i].iss_retention_employer;
	}

	spreadsheet->is_processed = 1;
	puts(H_STRS_PROCESSED_SUCCESS);
}

int h_proc_get_employee_index(s_arr_employees* employees_array, int code)
{
	int i;

	for (i = 0; i < employees_array->used; i++)
	{
		if (code == employees_array->employees[i].cod_employee)
		{
			return i;
		}
	}

	return 0;
}

float h_proc_get_retention_percentage(s_arr_irs* irs_array, int dependents, float raw_salary)
{
	int i;

	for (i = 0; i < irs_array->used; i++)
	{
		if (raw_salary < irs_array->elements[i].monthly_pay_value
			&& irs_array->elements[i].monthly_pay_type == H_IRS_UP_TO)
		{
			return irs_array->elements[i].percentage_per_dependent[dependents];
		}
	}

	if (raw_salary > irs_array->elements[irs_array->used - 1].monthly_pay_value &&
		irs_array->elements[irs_array->used - 1].monthly_pay_type == H_IRS_BEYOND)
	{
		return irs_array->elements[irs_array->used - 1].percentage_per_dependent[dependents];
	}
}

void h_proc_write(s_spreadsheet* spreadsheet, const char* path)
{
	FILE* fp;
	int i;

	if (spreadsheet->used == 0 || spreadsheet->month_is_set == 0)
	{
		printf("%s: %s\n", H_STRS_SAVE_FILE_ERROR, path);
		return;
	}

	fp = fopen(path, "wb");
	if (fp == NULL)
	{
		return;
	}

	fwrite(&spreadsheet->used, sizeof(spreadsheet->used), 1, fp);
	fwrite(&spreadsheet->month, sizeof(spreadsheet->month), 1, fp);
	fwrite(&spreadsheet->month_is_set, sizeof(spreadsheet->month_is_set), 1, fp);
	fwrite(&spreadsheet->is_processed, sizeof(spreadsheet->is_processed), 1, fp);
	fwrite(&spreadsheet->max_capacity, sizeof(spreadsheet->max_capacity), 1, fp);

	for (i = 0; i < spreadsheet->used; i++)
	{
		fwrite(&spreadsheet->details[i].cod_employee, sizeof(spreadsheet->details[i].cod_employee), 1, fp);
		fwrite(&spreadsheet->details[i].full_days, sizeof(spreadsheet->details[i].full_days), 1, fp);
		fwrite(&spreadsheet->details[i].half_days, sizeof(spreadsheet->details[i].half_days), 1, fp);
		fwrite(&spreadsheet->details[i].weekend_days, sizeof(spreadsheet->details[i].weekend_days), 1, fp);
		fwrite(&spreadsheet->details[i].absent_days, sizeof(spreadsheet->details[i].absent_days), 1, fp);
		fwrite(&spreadsheet->details[i].employer_charge, sizeof(spreadsheet->details[i].employer_charge), 1, fp);
		fwrite(&spreadsheet->details[i].iss_retention_employer, sizeof(spreadsheet->details[i].iss_retention_employer), 1, fp);
		fwrite(&spreadsheet->details[i].iss_retention_employee, sizeof(spreadsheet->details[i].iss_retention_employee), 1, fp);
		fwrite(&spreadsheet->details[i].irs_retention, sizeof(spreadsheet->details[i].irs_retention), 1, fp);
		fwrite(&spreadsheet->details[i].food_allowance, sizeof(spreadsheet->details[i].food_allowance), 1, fp);
		fwrite(&spreadsheet->details[i].bonus, sizeof(spreadsheet->details[i].bonus), 1, fp);
		fwrite(&spreadsheet->details[i].net_pay, sizeof(spreadsheet->details[i].net_pay), 1, fp);
		fwrite(&spreadsheet->details[i].gross_pay, sizeof(spreadsheet->details[i].gross_pay), 1, fp);
	}

	puts(H_STRS_SAVE_SUCCESS);
	fclose(fp);
}

void h_proc_create(s_spreadsheet* spreadsheet)
{
	if (spreadsheet->month_is_set == 1)
	{
		puts(H_STRS_ALREADY_CREATED);
		return;
	}

	spreadsheet->month = h_util_get_int(1, 12, "Mês: (1-12)") - 1;
	spreadsheet->month_is_set = 1;

	fprintf(stdout, GREEN("[!] Mês de %s criado com sucesso\n"), h_calendar_str_from_month(spreadsheet->month));
}

void h_proc_delete_month(s_spreadsheet* spreadsheet)
{
	int i;

	if (spreadsheet->used == 0)
	{
		puts(H_STRS_EMPLOYEES_NOT_FOUND);
		return;
	}

	spreadsheet->used = 0;
	spreadsheet->month_is_set = 0;
	spreadsheet->is_processed = 0;

	for (i = 0; i < spreadsheet->used - 1; i++)
	{
		spreadsheet->details[i] = spreadsheet->details[i + 1];
	}

	printf(GREEN("[!] Mês apagado com sucesso\n"));
}
