#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <ctype.h>

#include "commands.h"
#include "main.h"
#include "asm.h"

int bufferCtor (Buffer_t *asmCode)
{
    asmCode -> file_in  = file_open_read  ();
    asmCode -> file_out = file_open_write ();

    if (!(asmCode -> file_in))
	{
		assert(0);
	}
	if (!(asmCode -> file_out))
	{
		assert(0);
	}
    ssize_t size_text_rubbish = text_size (asmCode -> file_in) + 1;
    char* text_buffer_rubbish = nullptr;
    text_buffer_rubbish = (char*) calloc (size_text_rubbish, sizeof (char));
	fread (text_buffer_rubbish, 1, size_text_rubbish, asmCode -> file_in);
    *(text_buffer_rubbish + size_text_rubbish - 1) = '\0';

    char *symbol = text_buffer_rubbish;
	size_t p = 0;
    asmCode -> size_text = 0;
    while (*(symbol + p) != '\0')
    {
        if (*(symbol + p) != '\r') (asmCode -> size_text)++;
        p++;
    }
    (asmCode -> size_text)++;
	asmCode -> text_buffer = nullptr;
	if ((asmCode -> text_buffer = (char*) calloc (asmCode -> size_text, sizeof (char))) == nullptr)
	{
		assert(0);
	}
    int ptr_orig = 0;
    int ptr_rubb = 0;
	while (ptr_rubb <  size_text_rubbish)
    {
        if (*(text_buffer_rubbish + ptr_rubb) != '\r') 
        {
            *(asmCode -> text_buffer + ptr_orig) = *(text_buffer_rubbish + ptr_rubb);
            ptr_orig++;
        }
        ptr_rubb++;
    }
    return 1;
}

int bufferDtor (Buffer_t *asmCode)
{
    free(asmCode -> text_buffer);
	free(asmCode -> string_buffer);

	file_close(asmCode -> file_in);
	file_close(asmCode -> file_out);
	return 1;
}
int arrOfptr (Buffer_t *asmCode)
{
    asmCode -> n_strings = 0;
	for (size_t i = 0; i < (asmCode -> size_text); i++)
    {
        if ((*((asmCode -> text_buffer) + i) == '\n') || (*((asmCode -> text_buffer) + i) == '\0'))
        {
            asmCode -> n_strings += 1;
        }
        if (*((asmCode -> text_buffer) + i) == '\n')
        {
            *((asmCode -> text_buffer) + i) = '\0';
        }
    }

	asmCode -> string_buffer = nullptr;
	if ((asmCode -> string_buffer  = (Line*) calloc (asmCode -> n_strings+1, sizeof (Line))) == nullptr)
	{
		assert(0);
	}
	char *symbol = asmCode -> text_buffer;
	size_t p = 0;
	size_t amount = 0;
	size_t length = 0;
	(*(asmCode -> string_buffer)).start_line = asmCode -> text_buffer;
	while (amount < (asmCode -> n_strings))
	{
		length++;
		if ((*(symbol + p) == '\0'))
		{
			(*(asmCode -> string_buffer + amount)).len = length-2;
			amount++;
			length = 0;
			(*(asmCode -> string_buffer + amount)).start_line = symbol + p + 1;
		}
		p++;
	}
	(*(asmCode -> string_buffer + amount)).len = length;                                        

    return 1;
}

int txt_to_asm (Buffer_t *asmCode)
{
    for (size_t i = 0; i < asmCode -> n_strings; i++)
    {
        char* str = (*((asmCode -> string_buffer) + i)).start_line;
        Elem_t value   = POISON_ELEMENT;
        char*  reg     = NULL;
        char*  command = NULL;
        
        size_t amount_args = 0;

        char* arg = strtok(str, " ");
        while (arg) 
        {
            switch (amount_args)
            {
                case 0:
                    if      (isalpha(arg[0])) 
                    {
                        command = arg;
                    }
                    else
                    {
                        //make dump print
                    }
                break;
                case 1:
                    if      (isalpha(arg[0])) reg   = arg;
                    else if (isdigit(arg[0])) value = atoi(arg); 
                    else
                    {
                        //make dump print
                    }
                break;

                default:
                        //make dump print
                break;
            }
            arg = strtok(NULL, " ");
            amount_args++;
        }
        write_command (command, reg, value, asmCode);
    }
    return 1;
}

int write_command (char* command, char* reg, Elem_t value, Buffer_t* asmCode)
{
    for (size_t i = 0; i < AMOUNT_OF_COMMANDS; i++)
    {
        if (!strcmp (command, COMMANDS[i].command))
        {
            int bin_command = (int) COMMANDS[i].bin_code & ARG_FORMAT_COMMAND;
            
            if (reg != NULL) bin_command |= ARG_FORMAT_REGISTER;

            if (value != POISON_ELEMENT) bin_command |= ARG_FORMAT_IMMED;

            fwrite  (&bin_command, sizeof(int), 1, asmCode -> file_out);

            if (reg != NULL) 
            {
                int reg_id = get_reg_id (reg);
                fwrite(&reg_id, sizeof(int), 1, asmCode -> file_out);
            }

            if (value != POISON_ELEMENT)
            {
                fwrite(&value, sizeof(Elem_t), 1, asmCode -> file_out);
            }
            return 1;
        }
    }
    return 0;
}


int get_reg_id (char* reg_str)
{
    for (size_t i = 0; i < AMOUNT_OF_REGISTERS; i++)
    {
        if (!strcmp(reg_str, REGISTERS[i].name)) return REGISTERS[i].id;
    }
    return 0;
}

size_t text_size (FILE *file_text)
{
	if (!file_text)
	{
		assert(0);
	}
	struct stat st = {};
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}

FILE* file_open_read (void)
{
    FILE *file_read = nullptr;
    if ((file_read = fopen (FILE_IN, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_read;
}

FILE* file_open_write (void)
{
    FILE *file_out = nullptr;
    if ((file_out = fopen (FILE_OUT, "wb")) == nullptr) 
    {
        assert(0);
    }
    return file_out;
}

int file_close (FILE *file_text)
{
	if (!file_text)
	{
		assert(0);
	}
	if (fclose (file_text) != 0)
	{
		assert(0);
	}
	return 1;
}

int clean_str(char* command)
{
    int i = 0;
    while (*(command + i) != '\0')
    {
        *(command + i) = '\0';
        i++;
    }
    return 1;
}

int compare (double x, double y)
{
    if (((isnan (x) == 1) && (isnan (y) == 1)) || (fabs (x - y) < EPSILONE))
        return 1;
    else
        return 0;
}