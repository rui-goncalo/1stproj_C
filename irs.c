#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "irs.h"
#include "colors.h"
#include "strs.h"
#include "util.h"

s_arr_irs* h_irs_alloc(int initial_capacity)
{
	s_arr_irs* array;
	int i;

	if (!initial_capacity)
	{
		printf("IRS - %s\n", H_STRS_MISSING_CAPACITY);
		return NULL;
	}

	array = malloc(sizeof(s_arr_irs));
	if (array == NULL)
	{
		printf("IRS - %s\n", H_STRS_MALLOC_FAILED);
		return NULL;
	}

	array->elements = malloc(initial_capacity * sizeof(s_element));
	if (array->elements == NULL)
	{
		printf("IRS - %s\n", H_STRS_MALLOC_FAILED);
		return NULL;
	}

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->elements[i].percentage_per_dependent = malloc((MAX_DEPENDENT_NUMBER + 1) * sizeof(float));
		if (array->elements[i].percentage_per_dependent == NULL)
		{
			printf("IRS - %s\n", H_STRS_MALLOC_FAILED);
			return NULL;
		}
	}

	return array;
}

void h_irs_free(s_arr_irs* array)
{
	if (array == NULL)
	{
		return;
	}

	free(array->elements);
	free(array);
}

void h_irs_pair(s_element* element, char* str, int* dependent)
{
	size_t length = strlen(str);

	if (strcmp(str, "Até") == 0)
	{
		element->monthly_pay_type = H_IRS_UP_TO;
	}
	else if (strcmp(str, "Superior a") == 0)
	{
		element->monthly_pay_type = H_IRS_BEYOND;
	}

	if (str[length - 1] == '%')
	{
		element->percentage_per_dependent[*dependent] = strtof(str, NULL) / 100.0f;
		(*dependent)++;
	}
	else
	{
		element->monthly_pay_value = strtof(str, NULL);
	}
}

void h_irs_parse(s_arr_irs* array, const char* str, h_irs_pair_func pair_func)
{
	if (array == NULL || str == NULL)
	{
		puts(H_STRS_PARSE_ERROR);
		return;
	}

	int i;
	int j;
	int k; // buffer counter
	int delimiter = -1;
	int dependents = 0;
	char buffer[CSV_BUFFER];
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == CSV_COLUMN_DELIMITER || str[i] == CSV_NEW_LINE_DELIMITER)
		{
			for (j = delimiter + 1, k = 0; j < i; j++, k++)
			{
				buffer[k] = str[j];
			}

			pair_func(&array->elements[array->used], buffer, &dependents);
			memset(buffer, 0, CSV_BUFFER);

			delimiter = i;
		}

		if (str[i] == CSV_NEW_LINE_DELIMITER)
		{
			array->used++;
			dependents = 0;
		}
	}
}

void h_irs_print_line(s_element element)
{
	int j;

	printf(
			YELLOW("%s %.2f€"),
			element.monthly_pay_type == H_IRS_UP_TO ? "Até" : "Superior a",
			element.monthly_pay_value);

	for (j = 0; j < MAX_DEPENDENT_NUMBER + 1; j++)
	{
		printf(CYAN(" | %.1f%%"), element.percentage_per_dependent[j] * 100.0f);
	}

	printf("\n");
}

void h_irs_print(s_arr_irs* array)
{
	int i;

	if (array->used == 0)
	{
		printf("IRS - %s", H_STRS_EMPTY_TABLE);
		return;
	}

	printf("%s", H_STRS_IRS_TABLE_HEADER);
	for (i = 0; i < array->used; i++)
	{
		printf(RED("[%d] "), i);
		h_irs_print_line(array->elements[i]);
	}
}

void h_irs_add(s_arr_irs* array)
{
	int i;
	int j;
	int k;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;

		array->elements = realloc(array->elements, array->max_capacity * sizeof(s_element));
		if (array->elements == NULL)
		{
			return;
		}

		for (i = array->used + 1; i <= array->max_capacity; i++)
		{
			array->elements[i].percentage_per_dependent = malloc(MAX_DEPENDENT_NUMBER * sizeof(float));
			if (array->elements[i].percentage_per_dependent == NULL)
			{
				return;
			}

			for (j = 0; j < MAX_DEPENDENT_NUMBER; j++)
			{
				array->elements[i].percentage_per_dependent[j] = 0.0f;
			}
		}
	}

	array->used++;

	char op = h_util_get_alphabetical_char("[A]té [S]uperior a: ");
	if (op == 'A' || op == 'a')
	{
		array->elements[array->used - 1].monthly_pay_type = H_IRS_UP_TO;
	}
	else if (op == 'S' || op == 's')
	{
		array->elements[array->used - 1].monthly_pay_type = H_IRS_BEYOND;
	}

	array->elements[array->used - 1].monthly_pay_value = h_util_get_float(0.0f, 10000.0f, "Remuneração Mensal: ");

	printf(YELLOW("[!] Inserir percentagem para os dependentes de 0 a 5 ou mais\n"));
	for (k = 0; k < MAX_DEPENDENT_NUMBER; k++)
	{
		array->elements[array->used - 1].percentage_per_dependent[k] = h_util_get_float(0.0f, 100.0f, "Percentagem: ");
	}
}

void h_irs_edit(s_arr_irs* array)
{
	int index;
	int i;
	char op;

	if (array->used == 0)
	{
		printf("IRS - %s", H_STRS_EMPTY_TABLE);
		return;
	}

	index = h_util_get_int(0, array->used, H_STRS_EDIT);
	printf(H_STRS_IRS_TABLE_HEADER);
	h_irs_print_line(array->elements[index]);

	op = h_util_get_alphabetical_char("[A]té [S]uperior a: ");
	if (op == 'A' || op == 'a')
	{
		array->elements[index].monthly_pay_type = H_IRS_UP_TO;
	}
	else if (op == 'S' || op == 's')
	{
		array->elements[index].monthly_pay_type = H_IRS_BEYOND;
	}

	array->elements[index].monthly_pay_value = h_util_get_float(0.0f, MAX_REMUNERATION, "Remuneração Mensal: ");

	printf(YELLOW("[!] Inserir percentagem para os dependentes de 0 a 5 ou mais\n"));
	for (i = 0; i < MAX_DEPENDENT_NUMBER; i++)
	{
		array->elements[index].percentage_per_dependent[i] = h_util_get_float(0.0f, MAX_PERCENTAGE, "Percentagem: ");
	}
}

void h_irs_delete(s_arr_irs* array)
{
	int index;

	if (array->used == 0)
	{
		printf("IRS - %s", H_STRS_EMPTY_TABLE);
		return;
	}

	index = h_util_get_int(0, array->used, H_STRS_DELETE);

	h_irs_delete_element(array, index);
}

void h_irs_delete_element(s_arr_irs* array, int index)
{
	int i;

	if (array->used == 0)
	{
		printf("IRS - %s", H_STRS_EMPTY_TABLE);
		return;
	}

	if (!index)
	{
		puts(RED("[!] Nenhum índice especificado"));
		return;
	}

	for (i = index; i < array->used - 1; i++)
	{
		array->elements[i] = array->elements[i + 1];
	}

	array->used--;
}

void h_irs_write(s_arr_irs* array, const char* path)
{
	FILE* fp;
	int i;
	int j;

	if (array->used == 0)
	{
		printf("IRS - %s\n", H_STRS_EMPTY_TABLE);
		return;
	}

	if (path == NULL)
	{
		puts(H_STRS_PATH_MISSING);
		return;
	}

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("IRS - %s \"%s\"\n", H_STRS_SAVE_FILE_ERROR, path);
		return;
	}

	for (i = 0; i < array->used; i++)
	{
		fprintf(
				fp, "%s,%.2f",
				array->elements[i].monthly_pay_type == H_IRS_UP_TO ? "Até" : "Superior a",
				array->elements[i].monthly_pay_value);

		for (j = 0; j < MAX_DEPENDENT_NUMBER + 1; j++)
		{
			fprintf(fp, ",%.1f%%", array->elements[i].percentage_per_dependent[j] * 100);
		}

		fprintf(fp, "\n");
	}

	fclose(fp);

	printf("%s -> %s\n", H_STRS_SAVE_SUCCESS, path);
}

void h_irs_load(s_arr_irs* irs_array, char* path)
{
	int size = 0;
	char* str;

	str = h_util_file_read(path, &size);
	if (str == NULL)
	{
		printf("%s \"%s\"\n", H_STRS_LOAD_FAILED, path);
		return;
	}

	if (irs_array->used > 0)
	{
		printf("IRS - %s\n", H_STRS_LOAD_REPLACE);
		irs_array->used = 0;
	}

	h_irs_parse(irs_array, str, h_irs_pair);
	free(str);

	printf("%s -> %s\n", H_STRS_LOAD_SUCCESS, path);
}