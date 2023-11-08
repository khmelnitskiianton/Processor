#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "arrays.h"
#include "type.h"
#include "main_asm.h"
#include "buffer.h"

int BufferTextCtor (Asm_t *myAsm)
{
    (myAsm -> asmCode).file_in  = file_open_read  ();
    (myAsm -> asmCode).file_out = file_open_write ();

	assert ((myAsm -> asmCode).file_in);
	assert ((myAsm -> asmCode).file_out);

    size_t size_text_rubbish = text_size ((myAsm -> asmCode).file_in) + 1;
    char* text_buffer_rubbish = nullptr;
    
	assert (text_buffer_rubbish = (char*) calloc (size_text_rubbish, sizeof (char)));

	fread (text_buffer_rubbish, 1, size_text_rubbish, (myAsm -> asmCode).file_in);
    *(text_buffer_rubbish + size_text_rubbish - 1) = '\0';

    char *symbol = text_buffer_rubbish;
	size_t p = 0;
    (myAsm -> asmCode).size_text = 0;
    while (*(symbol + p) != '\0')
    {
        if (*(symbol + p) == '\r') 
		{
			p++;
			continue;
		}
		if ((*(symbol + p) == '\n') && (*(symbol + p + 1) == '\n')) 
		{ 
			p++; 		
			continue;
		}
        ((myAsm -> asmCode).size_text)++;
		p++;
    }
    ((myAsm -> asmCode).size_text)++;
	(myAsm -> asmCode).text_buffer = nullptr;
	
	assert ((myAsm -> asmCode).text_buffer = (char*) calloc ((myAsm -> asmCode).size_text, sizeof (char)));
    
	size_t ptr_orig = 0;
    size_t ptr_rubb = 0;
	while (ptr_rubb < size_text_rubbish)
    {
        if (*(text_buffer_rubbish + ptr_rubb) == '\r') 
        {
            ptr_rubb++;
			continue;
        }
		if ((*(text_buffer_rubbish + ptr_rubb) == '\n') && (*(text_buffer_rubbish + ptr_rubb + 1) == '\n'))
		{
			ptr_rubb++;
			continue;
		}
		*((myAsm -> asmCode).text_buffer + ptr_orig) = *(text_buffer_rubbish + ptr_rubb);
        ptr_orig++;
		ptr_rubb++;
    }

	(myAsm -> asmCode).n_strings = 0;
	for (size_t i = 0; i < ((myAsm -> asmCode).size_text); i++)
    {
        if ((*(((myAsm -> asmCode).text_buffer) + i) == '\n') || (*(((myAsm -> asmCode).text_buffer) + i) == '\0'))
        {
            (myAsm -> asmCode).n_strings += 1;
        }
        if (*(((myAsm -> asmCode).text_buffer) + i) == '\n')
        {
            *(((myAsm -> asmCode).text_buffer) + i) = '\0';
        }
    }

    free (text_buffer_rubbish);
    return 1;
}

int BufferTextDtor (Asm_t *myAsm)
{
    free ((myAsm -> asmCode).text_buffer);
	free ((myAsm -> asmCode).string_buffer);

	file_close ((myAsm -> asmCode).file_in);
	file_close ((myAsm -> asmCode).file_out);
	return 1;
}

int arrOfptr (Asm_t *myAsm)
{
	(myAsm -> asmCode).string_buffer = nullptr;

	assert ((myAsm -> asmCode).string_buffer = (Line*) calloc ((myAsm -> asmCode).n_strings+1, sizeof (Line)));
	
	char *symbol = (myAsm -> asmCode).text_buffer;
	size_t p = 0;
	size_t amount = 0;
	size_t length = 0;
	(*((myAsm -> asmCode).string_buffer)).start_line = (myAsm -> asmCode).text_buffer;
	while (amount < ((myAsm -> asmCode).n_strings))
	{
		length++;
		if ((*(symbol + p) == '\0'))
		{
			(*((myAsm -> asmCode).string_buffer + amount)).len = length-2;
			amount++;
			length = 0;
			(*((myAsm -> asmCode).string_buffer + amount)).start_line = symbol + p + 1;
		}
		p++;
	}
	(*((myAsm -> asmCode).string_buffer + amount)).len = length;                                        

    return 1;
}

size_t text_size (FILE *file_text)
{
	assert (file_text);

	struct stat st = {};
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = (size_t) st.st_size;
	return size_text;
}

FILE* file_open_read (void)
{
    FILE *file_read = fopen (FILE_TEXT, "rb");
	assert (file_read);
    return file_read;
}

FILE* file_open_write (void)
{
    FILE *file_out = fopen (FILE_BIN, "wb");
	assert (file_out);
    return file_out;
}

FILE* file_open_listing(void)
{
	FILE *file_out = fopen (FILE_LIST, "wb");
    assert (file_out);
    return file_out;
}

int file_close (FILE *file_text)
{
	assert (file_text);
	assert ((fclose (file_text) == 0));
	return 1;
}
int BufferBinCtor (Asm_t *myAsm)
{
	assert ((myAsm -> binCode).bin_buffer = (Elem_t*) calloc ((myAsm -> asmCode).n_strings * 4, sizeof (Elem_t)));
	
	(myAsm -> binCode).n_elements = 0;
	return 1;
}

int BufferBinDtor (Asm_t *myAsm)
{	
	free ((myAsm -> binCode).bin_buffer);
	return 1;
}

int AsmCtor(Asm_t *myAsm)
{
	myAsm -> file_listing = file_open_listing ();
	BufferTextCtor (myAsm);
	BufferBinCtor  (myAsm);
	return 1;
}

int AsmDtor(Asm_t *myAsm)
{
	file_close (myAsm -> file_listing);
	BufferTextDtor (myAsm);
	BufferBinDtor  (myAsm);
	return 1;
}
