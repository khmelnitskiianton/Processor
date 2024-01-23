#include <stdio.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <SDL2/SDL.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "stack_base.h"
#include "stack_support.h"
#include "main_cpu.h"
#include "myassert.h"
#include "buffer.h"

int BufferCtor (Cpu_t *myCpu, const char* data_read)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)

    myCpu -> myBuffer.file_in  = file_open_read (data_read);
    MYASSERT(myCpu -> myBuffer.file_in, NULL_POINTER_IN_OPEN_FILE, return 0)

    myCpu -> myBuffer.size_text = text_size (myCpu -> myBuffer.file_in); 
    myCpu -> myBuffer.text_buffer = (Elem_t*) calloc (myCpu -> myBuffer.size_text, sizeof (char));
    MYASSERT(myCpu -> myBuffer.text_buffer, BAD_CALLOC, return 0)
	
	size_t result = fread (myCpu -> myBuffer.text_buffer, 1, myCpu -> myBuffer.size_text, myCpu -> myBuffer.file_in);
    MYASSERT(result == (myCpu -> myBuffer.size_text), BAD_FREAD, return 0)

    myCpu -> actual_command = myCpu -> myBuffer.text_buffer;
    return 1;
}

int BufferDtor (Cpu_t *myCpu)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)

    free (myCpu -> myBuffer.text_buffer);

	file_close (myCpu -> myBuffer.file_in);
	return 1;
}

int MemoryCtor (Cpu_t *myCpu)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)
    for (size_t i = 0; i < MEMORY_LENGTH; i++)
    {
        myCpu -> myMemory[i] = POISON_ELEMENT;
    }
    return 1;
}

int MemoryDtor (Cpu_t *myCpu)
{
    MYASSERT(myCpu, BAD_POINTER_PASSED_IN_FUNC, return 0)
    for (size_t i = 0; i < MEMORY_LENGTH; i++)
    {
        myCpu -> myMemory[i] = POISON_ELEMENT;
    }
    return 1;
}

size_t text_size (FILE *file_text)
{
	MYASSERT(file_text, BAD_POINTER_PASSED_IN_FUNC, return 0)

	struct stat st = {};
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = (size_t) st.st_size;

    USER_ERROR(size_text, EMPTY_FILE, exit(0))
	return size_text;
}

FILE* file_open_read (const char* data_read)
{
    FILE *file_read = fopen (data_read, "rb");
    MYASSERT(data_read, NULL_POINTER_IN_OPEN_FILE, return NULL)
    return file_read;
}