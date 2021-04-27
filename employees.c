#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "employees.h"
#include "colors.h"
#include "strs.h"
#include "irs.h"
#include "util.h"

int buffer_first_name = BUFFER_SIZE;
int buffer_last_name = BUFFER_SIZE;

s_arr_employees* h_employees_alloc(int initial_capacity)
{
	s_arr_employees* array;
	int i;

	if (!initial_capacity)
	{
		return NULL;
	}

	array = malloc(sizeof(s_arr_employees));
	if (array == NULL)
	{
		return NULL;
	}

	array->employees = malloc(initial_capacity * sizeof(s_employee));
	if (array->employees == NULL)
	{
		return NULL;
	}

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->employees[i].first_name = malloc(buffer_first_name * sizeof(char));
		if (array->employees[i].first_name == NULL)
		{
			return NULL;
		}

		array->employees[i].last_name = malloc(buffer_last_name * sizeof(char));
		if (array->employees[i].last_name == NULL)
		{
			return NULL;
		}

		array->employees[i].birthday = malloc(sizeof(s_date));
		if (array->employees[i].birthday == NULL)
		{
			return NULL;
		}

		array->employees[i].entry_date = malloc(sizeof(s_date));
		if (array->employees[i].entry_date == NULL)
		{
			return NULL;
		}

		array->employees[i].leaving_date = malloc(sizeof(s_date));
		if (array->employees[i].leaving_date == NULL)
		{
			return NULL;
		}
	}

	return array;
}

int h_employees_randomize()
{
	srand(1);

	return rand() % MAX_VALUE;
}

int h_employees_get_marital_status()
{

	switch (h_util_get_int(0, 3, "Estado Civil: (0-3)\n0 - Solteiro\n1 - Casado\n2 - Divorciado\n3 - Viuvo\n? "))
	{
		case 0:
			return SINGLE;
		case 1:
			return MARRIED;
		case 2:
			return DIVORCED;
		case 3:
			return WIDOWED;
	}

	return SINGLE;
}

int h_employees_get_phone_number()
{
	char* str;
	int phone_number;

	do
	{
		str = h_util_get_string(PHONE_NUMBER_SIZE + 1, "TLF:");
	} while (h_employees_verify_phone(str) == -1);

	phone_number = atoi(str);
	free(str);

	return phone_number;
}

void h_employees_get_fields(s_employee* employee, s_arr_iss* iss_array)
{
	char* first_name;
	char* last_name;

	if (!employee->cod_employee)
	{
		employee->cod_employee = h_employees_randomize();
	}

	if (employee->first_name)
	{
		printf("Primeiro nome: %s\n", employee->first_name);
	}

	first_name = h_util_get_string(BUFFER_SIZE, "Primeiro Nome:");
	if (first_name == NULL)
	{
		puts(RED("[!] Não foi possivel ler o primeiro nome"));
		return;
	}

	if (employee->first_name == NULL)
	{
		employee->first_name = malloc(strlen(first_name) * sizeof(char));
		if (employee->first_name == NULL)
		{
			puts(RED("[!] Não foi possivel alocar memória para o primeiro nome"));
			return;
		}
	}

	strcpy(employee->first_name, first_name);
	free(first_name);

	if (employee->last_name)
	{
		printf("Último nome: %s\n", employee->last_name);
	}

	last_name = h_util_get_string(BUFFER_SIZE, "Último Nome:");
	if (first_name == NULL)
	{
		puts(RED("[!] Não foi possivel ler o último nome"));
		return;
	}

	if (employee->last_name == NULL)
	{
		employee->last_name = malloc(strlen(last_name) * sizeof(char));
		if (employee->last_name == NULL)
		{
			puts(RED("[!] Não foi possivel alocar memória para o primeiro nome"));
			return;
		}
	}

	strcpy(employee->last_name, last_name);
	free(last_name);

	if (employee->phone_number)
	{
		printf("TLF atual: %d\n", employee->phone_number);

	}
	employee->phone_number = h_employees_get_phone_number();

	if (employee->marital_status)
	{
		printf("Estado Civil atual: %s\n", h_employees_str_from_marital_status(employee->marital_status, 1));
	}
	employee->marital_status = h_employees_get_marital_status();

	if (employee->marital_status == SINGLE ||
		employee->marital_status == DIVORCED ||
		employee->marital_status == WIDOWED)
	{
		employee->holders = NONE;
	}
	else
	{
		employee->holders = h_util_get_int(1, 2, "Unico ou Dois Titulares (1 - 2): ");
	}

	if (employee->role)
	{
		printf("Cargo atual: %d\n", employee->role);
	}

	printf(YELLOW("Cargos Disponiveis\n"));
	for (int i = 0; i < iss_array->used; i++)
	{
		printf(YELLOW("%d - %s\n"), i, iss_array->data[i].criteria);
	}
	employee->role = h_util_get_int(0, iss_array->used, "Cargo:");

	if (employee->dependents)
	{
		printf("Nº de dependentes atual: %d\n", employee->dependents);
	}
	employee->dependents = h_util_get_int(0, MAX_DEPENDENT_NUMBER, "Nº de dependentes:");

	if (employee->birthday == NULL)
	{
		employee->birthday = malloc(sizeof(s_date));
		if (employee->birthday == NULL)
		{
			puts(RED("[!] Não foi possivel alocar memória para a data de nascimento"));
			return;
		}
	}
	else
	{
		printf(
				"Data de nascimento atual: %d/%d/%d\n",
				employee->birthday->day,
				employee->birthday->month,
				employee->birthday->year);
	}

	h_calendar_get_date(employee->birthday, "Data de nascimento: ");

	if (employee->entry_date == NULL)
	{
		employee->entry_date = malloc(sizeof(s_date));
		if (employee->entry_date == NULL)
		{
			puts(RED("[!] Não foi possivel alocar memória para a data de entrada"));
			return;
		}
	}
	else
	{
		printf(
				"Data de entrada atual: %d/%d/%d\n",
				employee->entry_date->day,
				employee->entry_date->month,
				employee->entry_date->year);
	}

	h_calendar_get_date(employee->entry_date, "Data de entrada: ");

	if (employee->leaving_date == NULL)
	{
		employee->leaving_date = malloc(sizeof(s_date));
		if (employee->leaving_date == NULL)
		{
			puts(RED("[!] Não foi possivel alocar memória para a data de nascimento"));
			return;
		}
	}
	else
	{
		printf(
				"Data de saida atual: %d/%d/%d\n",
				employee->leaving_date->day,
				employee->leaving_date->month,
				employee->leaving_date->year);
	}

	h_calendar_get_date(employee->leaving_date, "Data de saida: ");

	if (employee->hourly_rate)
	{
		printf("Valor por hora atual %.2f\n", employee->hourly_rate);
	}
	employee->hourly_rate = h_util_get_float(0.0f, MAX_HOURLY_RATE, "Valor por hora: ");

	if (employee->base_food_allowance)
	{
		printf("Valor base subsídio de alimentação anterior %.2f\n", employee->base_food_allowance);
	}
	employee->base_food_allowance = h_util_get_float(0.0f, MAX_FOOD_ALLOWANCE, "Valor base subsídio de alimentação: ");
}

void h_employees_add(s_arr_employees* array, s_arr_iss* iss_array)
{
	if (array == NULL)
	{
		puts(RED("[!] Employees não alocado"));
		return;
	}

	if (iss_array == NULL && iss_array->used == 0)
	{
		puts(RED("[!] ISS não alocada ou vazia"));
		puts(YELLOW("[!] Não é possivel adicionar funcionários sem a ISS inicializada"));
		return;
	}

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->employees = realloc(array->employees, array->max_capacity * sizeof(s_employee));
		if (array->employees == NULL)
		{
			return;
		}
	}

	h_employees_get_fields(&array->employees[array->used], iss_array);
	array->used++;
}

void h_employees_edit(s_arr_employees* array, s_arr_iss* iss_array)
{
	int num;

	if (array == NULL || array->used == 0)
	{
		puts(RED("[!] Employees não alocado ou vazio"));
		return;
	}

	if (iss_array == NULL && iss_array->used == 0)
	{
		puts(RED("[!] ISS não alocada ou vazia"));
		puts(YELLOW("[!] Não é possivel editar funcionários sem a ISS inicializada"));
		return;
	}

	printf("Nº de registos do ficheiro: %d\n", array->used);

	/****************************************************
	 * Na função abaixo, peço um inteiro que representa
	 * linha que o utilizador quer fazer a alteração e
	 * igualo o valor a uma variável int(num).
	 * **************************************************/
	num = h_util_get_int(0, array->used, H_STRS_EDIT);
	h_employees_get_fields(&array->employees[num], iss_array);
}

int h_employees_verify_phone(char* str)
{
	if (strlen(str) != PHONE_NUMBER_SIZE)
	{
		return -1;
	}

	if (str[0] != '9')
	{
		return -1;
	}

	if (str[1] != '1' && str[1] != '2' && str[1] != '3' && str[1] != '6')
	{
		return -1;
	}

	return 0;
}

void h_employees_print(s_arr_employees* array, s_arr_iss* iss_array)
{
	if (array == NULL || array->used == 0)
	{
		puts(RED("[!] Employees não alocado ou vazio"));
		return;
	}

	if (iss_array == NULL || iss_array->used == 0)
	{
		puts(RED("[!] ISS não alocada ou vazia"));
		puts(YELLOW("[!] Impossivel mostrar os cargos sem a tabela da ISS inicializada"));
		return;
	}

	printf(H_STRS_EMPLOYEES_TABLE_HEADER);

	int i;
	for (i = 0; i < array->used; i++)
	{
		printf(YELLOW("[%d] "), i);
	    printf(GREEN(PRINT_TEMPLATE_STRING),
				array->employees[i].cod_employee,
				array->employees[i].first_name,
				array->employees[i].last_name,
				array->employees[i].phone_number,
				array->employees[i].dependents,
				iss_array->data[array->employees[i].role].criteria,
				h_employees_str_from_marital_status(array->employees[i].marital_status, 1),
				array->employees[i].birthday->day,
				array->employees[i].birthday->month,
				array->employees[i].birthday->year,
				array->employees[i].entry_date->day,
				array->employees[i].entry_date->month,
				array->employees[i].entry_date->year,
				array->employees[i].leaving_date->day,
				array->employees[i].leaving_date->month,
				array->employees[i].leaving_date->year,
				array->employees[i].hourly_rate,
				array->employees[i].base_food_allowance,
				array->employees[i].holders,
				array->employees[i].removed == 1 ? RED("[Removido]") : " "
		);
	}
}

void h_employees_pair(s_employee* employee, char* str, int column)
{
	if (column == COL_CODE_FUNC)
	{
		employee->cod_employee = atoi(str);
	}

	if (strlen(str) == 1 && column == COL_NUM_DEPENDENTS)
	{
		employee->dependents = atoi(str);
	}

	if (strlen(str) == 1 && column == COL_ROLE)
	{
		employee->role = atoi(str);
	}

	if (strlen(str) == PHONE_NUMBER_SIZE && column == COL_PHONE_NUMBER)
	{
		employee->phone_number = atoi(str);
	}

	if (column == COL_MARITAL_STATUS)
	{
		if (strcmp(str, "MARRIED") == 0)
		{
			employee->marital_status = MARRIED;
		}
		else if (strcmp(str, "SINGLE") == 0)
		{
			employee->marital_status = SINGLE;
		}
		else if (strcmp(str, "DIVORCED") == 0)
		{
			employee->marital_status = DIVORCED;
		}
	}

	if (column == COL_FIRST_NAME)
	{
		if (strlen(str) >= buffer_first_name)
		{
			employee->first_name = realloc(employee->first_name, buffer_first_name * 2);
			if (employee->first_name == NULL)
			{
				return;
			}

			buffer_first_name *= 2;
		}

		strcpy(employee->first_name, str);
	}

	if (column == COL_LAST_NAME)
	{
		if (strlen(str) >= buffer_last_name)
		{
			employee->last_name = realloc(employee->last_name, buffer_last_name * 2);
			if (employee->last_name == NULL)
			{
				return;
			}
			buffer_last_name *= 2;
		}

		strcpy(employee->last_name, str);
	}

	if (column == COL_BIRTHDAY)
	{
		sscanf(
				str, "%d/%d/%d",
				&employee->birthday->day,
				&employee->birthday->month,
				&employee->birthday->year);
	}

	if (column == COL_ENTRY_DATE)
	{
		sscanf(
				str, "%d/%d/%d",
				&employee->entry_date->day,
				&employee->entry_date->month,
				&employee->entry_date->year);
	}

	if (column == COL_LEAVING_DATE)
	{
		sscanf(
				str, "%d/%d/%d",
				&employee->leaving_date->day,
				&employee->leaving_date->month,
				&employee->leaving_date->year);
	}

	if (column == COL_HOURLY_RATE)
	{
		employee->hourly_rate = strtof(str, NULL);
	}

	if (column == COL_BASE_FOOD_ALLOWANCE)
	{
		employee->base_food_allowance = strtof(str, NULL);
	}

	if (column == COL_HOLDERS)
	{
		if (strcmp(str, "NONE") == 0)
		{
			employee->holders = NONE;
		}

		if (strcmp(str, "UNIQUE_HOLDER") == 0)
		{
			employee->holders = UNIQUE_HOLDER;
		}

		if (strcmp(str, "TWO_HOLDERS") == 0)
		{
			employee->holders = TWO_HOLDERS;
		}
	}
}

void h_employees_parse(s_arr_employees* array, const char* str)
{
    // neste if, verificamos se o array é null porque ele ainda não está preenchido
    // mas já está alocado. O 'str' traz o a tabela do ficheiro partida por ';' e está
    // preenchido.
	if (array == NULL || str == NULL)
	{
		return;
	}

	int i;
	int j;
	int k;
	int delimiter = -1;
	int column = 1;
	char buffer[CSV_BUFFER];
	for (i = 0; str[i] != '\0'; i++)
	{
		if (str[i] == CSV_COLUMN_DELIMITER || str[i] == CSV_NEW_LINE_DELIMITER)
		{
			for (j = delimiter + 1, k = 0; j < i; j++, k++)
			{
				buffer[k] = str[j];
			}
			printf("%s", buffer);

			h_employees_pair(&array->employees[array->used], buffer, column);
			memset(buffer, 0, CSV_BUFFER);
			delimiter = i;
			column++;
		}

		if (str[i] == CSV_NEW_LINE_DELIMITER)
		{
			column = 1;
			array->used++;
		}
	}
}

char* h_employees_str_from_marital_status(e_marital_status status, int display)
{
	char* status_display[] = {"Solteiro", "Casado", "Divorciado", "Viúvo"};
	char* status_write[] = {"SINGLE", "MARRIED", "DIVORCED", "WIDOWED"};

	if (display == 1)
	{
		return status_display[status];
	}

	return status_write[status];
}

char* h_employees_str_from_holders(e_holders holder)
{
	char* str[] = {"NONE", "UNIQUE_HOLDER", "TWO_HOLDERS"};

	return str[holder];
}

void h_employees_delete(s_arr_employees* array)
{
	int num;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	num = h_util_get_int(0, array->used, H_STRS_DELETE);

    h_calendar_get_date(array->employees[num].leaving_date, "Data de saida: ");

	array->employees[num].removed = 1;

	puts(RED("Funcionário removido"));

}

void h_employees_write(s_arr_employees* array, const char* path)
{
	int i;
	FILE* fp;

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		return;
	}

	for (i = 0; i < array->used; i++)
	{
	    fprintf(
                fp, "%d,%s,%s,%d,%s,%d,%d,%d/%d/%d,%d/%d/%d,%d/%d/%d,%.2f,%.2f,%s\n",
                array->employees[i].cod_employee,
                array->employees[i].first_name,
                array->employees[i].last_name,
                array->employees[i].phone_number,
                h_employees_str_from_marital_status(array->employees[i].marital_status, 0),
                array->employees[i].role,
                array->employees[i].dependents,
                array->employees[i].birthday->day,
                array->employees[i].birthday->month,
                array->employees[i].birthday->year,
                array->employees[i].entry_date->day,
                array->employees[i].entry_date->month,
                array->employees[i].entry_date->year,
                array->employees[i].leaving_date->day,
                array->employees[i].leaving_date->month,
                array->employees[i].leaving_date->year,
                array->employees[i].hourly_rate,
                array->employees[i].base_food_allowance,
                h_employees_str_from_holders(array->employees[i].holders)
        );
	}

	fclose(fp);

	printf("%s -> %s\n", H_STRS_SAVE_SUCCESS, path);
}

void h_employees_load(s_arr_employees* array, const char* path)
{
	int size = 0;
	char* str;

	str = h_util_file_read(path, &size);
	if (str == NULL)
	{
		printf("%s \"%s\"\n", H_STRS_LOAD_FAILED, path);
		return;
	}

	if (array->used > 0)
	{
		printf("Employees - %s", path);
		array->used = 0;
	}

	h_employees_parse(array, str);
	free(str);

	printf("%s -> %s\n", H_STRS_LOAD_SUCCESS, path);
}

void h_employees_free(s_arr_employees* array)
{
	int i;
	if (array == NULL)
	{
		return;
	}

	for (i = 0; i < array->used; i++)
	{
		free(array->employees[i].birthday);
		free(array->employees[i].entry_date);
		free(array->employees[i].leaving_date);
		free(array->employees[i].first_name);
		free(array->employees[i].last_name);
	}

	free(array->employees);
	free(array);
}