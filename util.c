#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#include "util.h"
#include "colors.h"
#include "strs.h"

char* h_util_file_read(const char* path, int* size)
{
	FILE* fptr;
	size_t buffer_size;
	char* buffer;
	int counter;
	int ch;

	if (path == NULL)
	{
		return NULL;
	}

	fptr = fopen(path, "r");
	if (fptr == NULL)
	{
		return NULL;
	}

	buffer_size = 256;
	buffer = malloc(buffer_size * sizeof(char));
	if (buffer == NULL)
	{
		free(fptr);
		return NULL;
	}

	counter = 0;
	/* Read a character at a time, resizing the buffer as necessary */
	while ((ch = fgetc(fptr)) && ch != EOF && !feof(fptr))
	{
		buffer[counter++] = (char)ch;

		if (ch == '\n')
		{
			(*size)++;
		}

		if (counter == buffer_size)
		{
			/* Resize twice the value of the buffer */
			buffer_size *= 2;
			buffer = realloc(buffer, buffer_size * sizeof(char));
			if (buffer == NULL)
			{
				free(fptr);
				free(buffer);
				return NULL;
			}
		}
	}

	buffer[counter] = '\0';
	return buffer;
}

void h_util_clean_buffer()
{
	int ch;
	while ((ch = getchar()) != '\n' && ch != EOF);
}

char* h_util_get_string(int length, const char* msg)
{
	char* str = malloc((length + 1) * sizeof(char));
	if (str == NULL)
	{
		return NULL;
	}

	fprintf(stdout, YELLOW("%s "), msg);

	fgets(str, length + 1, stdin);

	str[strlen(str) - 1] = '\0';
	return str;
}

char h_util_get_alphabetical_char(const char* msg)
{
	char c;

	fprintf(stdout, YELLOW("%s "), msg);

	while (scanf("%c", &c) != 1 || !isalpha(c))
	{
		puts(H_STRS_INVALID_INPUT);
		h_util_clean_buffer();
		fprintf(stdout, RED("%s "), msg);
	}

	return c;
}

int h_util_get_int(int min, int max, const char* msg)
{
	int num;

	fprintf(stdout, YELLOW("%s "), msg);

	while (scanf("%d", &num) != 1 || num < min || num > max)
	{
		puts(H_STRS_INVALID_INPUT);
		h_util_clean_buffer();
		fprintf(stdout, RED("%s "), msg);
	}
	h_util_clean_buffer();
	return num;
}

float h_util_get_float(float min, float max, const char* msg)
{
	float num;

	fprintf(stdout, YELLOW("%s"), msg);
	h_util_clean_buffer();

	while (scanf("%f", &num) != 1 || num < min || num > max)
	{
		puts(H_STRS_INVALID_INPUT);
		h_util_clean_buffer();
		fprintf(stdout, RED("%s"), msg);
	}

	return num;
}