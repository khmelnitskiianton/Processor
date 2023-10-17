#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <ctype.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "arrays.h"
#include "type.h"
#include "main.h"
#include "buffer.h"
#include "asm.h"

int bufferCtor (BufferAsm_t *asmCode)
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
    free(text_buffer_rubbish);
    return 1;
}

int bufferDtor (BufferAsm_t *asmCode)
{
    free(asmCode -> text_buffer);
	free(asmCode -> string_buffer);

	file_close(asmCode -> file_in);
	file_close(asmCode -> file_out);
	return 1;
}

int arrOfptr (BufferAsm_t *asmCode)
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
    if ((file_read = fopen (FILE_TEXT, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_read;
}

FILE* file_open_write (void)
{
    FILE *file_out = nullptr;
    if ((file_out = fopen (FILE_BIN, "wb")) == nullptr) 
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