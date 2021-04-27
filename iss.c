#include "iss.h"

s_arr_iss* h_iss_alloc(int initial_capacity)
{
	int i;
	s_arr_iss* array;

	if (!initial_capacity)
	{
		puts(H_STRS_MISSING_CAPACITY);
		return NULL;
	}

	array = malloc(sizeof(s_arr_iss));
	if (array == NULL)
	{
		printf("ISS - %s\n", H_STRS_MALLOC_FAILED);
		return NULL;
	}

	array->data = malloc(initial_capacity * sizeof(s_iss));
	if (array->data == NULL)
	{
		printf("ISS - %s\n", H_STRS_MALLOC_FAILED);
		return NULL;
	}

	array->used = 0;
	array->max_capacity = initial_capacity;

	for (i = 0; i <= array->max_capacity; i++)
	{
		array->data[i].criteria = malloc(BUFFER_SIZE * sizeof(char));
		if (array->data[i].criteria == NULL)
		{
			printf("ISS - %s\n", H_STRS_MALLOC_FAILED);
			return NULL;
		}
	}
	return array;
}

void h_iss_free(s_arr_iss* array)
{
	if (array == NULL)
	{
		return;
	}

	free(array->data);
	free(array);
}

void h_iss_parse(s_arr_iss* array, char* str)
{
	int i;
	int offset = -1;

	if (array == NULL || str == NULL)
	{
		puts(H_STRS_PARSE_ERROR);
		return;
	}

	for (i = 0; str[i] != '\0'; i++)
	{
		if (offset == -1 && isalnum(str[i]))
		{
			offset = i;
		}

		if (offset != -1)
		{
			if (str[i] == ',')
			{
				str[i] = '\0';

				if (str[i - 1] == '%')
				{
					str[i - 1] = '\0';
					array->data[array->used].employer_retention = strtof(str + offset, NULL);
				}
				else
				{
					str[i] = '\0';

					if (strlen(str + offset) > BUFFER_SIZE)
					{
						array->data[array->used].criteria = realloc(
								array->data[array->used].criteria,
								(BUFFER_SIZE * 2) * sizeof(char));

						if (array->data[array->used].criteria == NULL)
						{
							puts(H_STRS_MALLOC_FAILED);
							return;
						}
					}
					strcpy(array->data[array->used].criteria, str + offset);
				}
				offset = -1;
			}
			else if (str[i] == '\n')
			{
				str[i - 1] = '\0';
				array->data[array->used].employee_retention = strtof(str + offset, NULL);
				array->used++;
				offset = -1;
			}
		}
	}
}

void h_iss_print(s_arr_iss* array)
{
	int i;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	printf("%s", H_STRS_SS_TABLE_HEADER);
	for (i = 0; i < array->used; i++)
	{
		printf(RED("[%d] "), i);
		printf(YELLOW("%s "), array->data[i].criteria);
		printf(BLUE("| %.2f%% | %.2f%%\n"), array->data[i].employer_retention, array->data[i].employee_retention);
	}
}

void h_iss_add(s_arr_iss* array)
{
	int i;
	char* new_criteria;

	if (array->used == array->max_capacity)
	{
		array->max_capacity *= 2;
		array->data = realloc(array->data, array->max_capacity * sizeof(s_iss));
		if (array->data == NULL)
		{
			printf("ISS - %s\n", H_STRS_MALLOC_FAILED);
			return;
		}
	}

	new_criteria = malloc(sizeof(char) * 64);
	if (new_criteria == NULL)
	{
		puts(H_STRS_MALLOC_FAILED);
		return;
	}

	printf("\n%s", H_STRS_NEW_CRITERIA);
	scanf("%s", new_criteria);

	for (i = 0; i < array->used; i++)
	{
		if (strcmp(new_criteria, array->data[i].criteria) == 0)
		{
			puts(H_STRS_CRITERIA_DUPLICATE);
			return;
		}
	}

	array->data[array->used].criteria = new_criteria;
	array->data[array->used].employer_retention = h_util_get_float(0.0f, 100.0f, "Empregador: ");
	array->data[array->used].employee_retention = h_util_get_float(0.0f, 100.0f, "Empregado: ");
	array->used++;
}

void h_iss_delete(s_arr_iss* array)
{
	int i;
	int num;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	num = h_util_get_int(0, (array->used) - 1, H_STRS_DELETE);

	for (i = num; i < array->used; i++)
	{
		array->data[i] = array->data[i + 1];
	}

	array->used--;
}

void h_iss_edit(s_arr_iss* array)
{
	int i;
	int num;
	char* new_criteria;

	if (array->used == 0)
	{
		printf(H_STRS_EMPTY_TABLE);
		return;
	}

	printf(YELLOW("Número de Registos: %d\n"), array->used);
	num = h_util_get_int(0, array->used - 1, H_STRS_EDIT);

	new_criteria = malloc(sizeof(char) * 64);
	if (new_criteria == NULL)
	{
		puts(H_STRS_MALLOC_FAILED);
		return;
	}

	printf("Critério - Valor atual: %s | ", array->data[num].criteria);
	printf("Novo valor: ");
	scanf("%s", new_criteria);

	for (i = 0; i <= array->used; i++)
	{
		if (strcmp(new_criteria, array->data[i].criteria) == 0 && i != num)
		{
			printf(H_STRS_CRITERIA_DUPLICATE);
			return;
		}
	}

	array->data[num].criteria = new_criteria;
	printf("Empregador - Valor atual: %.2f | ", array->data[num].employer_retention);
	array->data[num].employer_retention = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
	printf("Empregado - Valor atual: %.2f | ", array->data[num].employee_retention);
	array->data[num].employee_retention = h_util_get_float(0.0f, 100.0f, "Novo valor: ");
}

void h_iss_write(s_arr_iss* array, const char* path)
{
	int i;
	FILE* fp;

	if (array->used == 0)
	{
		printf("ISS - %s", H_STRS_EMPTY_TABLE);
		return;
	}

	fp = fopen(path, "w");
	if (fp == NULL)
	{
		printf("ISS - %s \"%s\"\n", H_STRS_SAVE_FILE_ERROR, path);
		return;
	}

	for (i = 0; i < array->used; i++)
	{
		fprintf(
				fp, "%s,%.2f%%,%.2f%%\n",
				array->data[i].criteria,
				array->data[i].employer_retention,
				array->data[i].employee_retention);
	}

	fclose(fp);

	printf("%s -> %s\n", H_STRS_SAVE_SUCCESS, path);
}

void h_iss_load(s_arr_iss* array, const char* path)
{
	int size = 0;
	char* str;

	str = h_util_file_read(path, &size);
	if (str == NULL)
	{
		printf("%s \"%s\"\n", H_STRS_LOAD_FAILED, H_PATH_ISS);
		return;
	}

	if (array->used > 0)
	{
		printf("ISS - %s\n", H_STRS_LOAD_REPLACE);
		array->used = 0;
	}

	h_iss_parse(array, str);
	free(str);

	printf("%s -> %s\n", H_STRS_LOAD_SUCCESS, path);
}