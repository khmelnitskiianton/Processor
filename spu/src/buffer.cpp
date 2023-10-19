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
#include "main.h"
#include "calc.h"
#include "buffer.h"
#include "stack.h"
#include "support.h"

int BufferCtor (Spu_t *mySpu)
{
    mySpu -> myBuffer.file_in  = file_open_read  ();
    mySpu -> myBuffer.file_out = file_open_write ();

    if (!(mySpu -> myBuffer.file_in))
	{
		assert(0);
	}
	if (!(mySpu -> myBuffer.file_out))
	{
		assert(0);
	}
    mySpu -> myBuffer.size_text = text_size (mySpu -> myBuffer.file_in) + 1; 
	mySpu -> myBuffer.text_buffer = nullptr;
	if ((mySpu -> myBuffer.text_buffer = (Elem_t*) calloc (mySpu -> myBuffer.size_text, sizeof (char))) == nullptr)
	{
		assert(0);
	}
	size_t result = fread (mySpu -> myBuffer.text_buffer, 1, mySpu -> myBuffer.size_text, mySpu -> myBuffer.file_in);
	if (result != (mySpu -> myBuffer.size_text - 1))
	{
		assert(0);
	}
	mySpu -> actual_command = mySpu -> myBuffer.text_buffer;
    return 1;
}

int BufferDtor (Spu_t *mySpu)
{
    free(mySpu -> myBuffer.text_buffer);

	file_close(mySpu -> myBuffer.file_in);
	file_close(mySpu -> myBuffer.file_out);
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
    if ((file_read = fopen (FILE_BIN, "rb")) == nullptr) 
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
