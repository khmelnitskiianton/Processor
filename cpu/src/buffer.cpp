#include <stdio.h>
#include <assert.h>
#include <string.h>
#include <limits.h>
#include <math.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>

#include "arrays.h"
#include "type.h"
#include "stack_main.h"
#include "stack_base.h"
#include "stack_support.h"
#include "main_cpu.h"
#include "buffer.h"

int BufferCtor (Cpu_t *myCpu)
{
    myCpu -> myBuffer.file_in  = file_open_read  ();

    assert(myCpu -> myBuffer.file_in);

    myCpu -> myBuffer.size_text = text_size (myCpu -> myBuffer.file_in) + 1; 
	myCpu -> myBuffer.text_buffer = (Elem_t*) calloc (myCpu -> myBuffer.size_text, sizeof (char));

	assert(myCpu -> myBuffer.text_buffer);
	
	size_t result = fread (myCpu -> myBuffer.text_buffer, 1, myCpu -> myBuffer.size_text, myCpu -> myBuffer.file_in);

	assert(result == (myCpu -> myBuffer.size_text - 1));

	myCpu -> actual_command = myCpu -> myBuffer.text_buffer;
    return 1;
}

int BufferDtor (Cpu_t *myCpu)
{
    free(myCpu -> myBuffer.text_buffer);

	file_close(myCpu -> myBuffer.file_in);
	return 1;
}

int MemoryCtor (Cpu_t *myCpu)
{
    for (size_t i = 0; i < MEMORY_LENGTH; i++)
    {
        myCpu -> myMemory[i] = POISON_ELEMENT;
    }
    return 1;
}

int MemoryDtor (Cpu_t *myCpu)
{
    for (size_t i = 0; i < MEMORY_LENGTH; i++)
    {
        myCpu -> myMemory[i] = POISON_ELEMENT;
    }
    return 1;
}

size_t text_size (FILE *file_text)
{
	assert(file_text);

	struct stat st = {};
    int fd = fileno (file_text); 
    fstat (fd, &st);
    size_t size_text = st.st_size;
	return size_text;
}

FILE* file_open_read (void)
{
    FILE *file_read = fopen (FILE_BIN, "rb");
    assert(file_read);
    return file_read;
}