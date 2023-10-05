#include "head.h"

FILE* file_read_asm (void)
{
    FILE *file_read = nullptr;
    if ((file_read = fopen (FILE_IN_TEXT, "rb")) == nullptr) 
    {
        assert(0);
    }
    return file_read;
}

FILE* file_write_asm (void)
{
    FILE *file_out = nullptr;
    if ((file_out = fopen (FILE_IN_NUM, "wb")) == nullptr) 
    {
        assert(0);
    }
    return file_out;
}

int file_close_asm (FILE *file_text)
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

int compare_command (char command[], FILE* file_write)
{
    int i = 0;
    while (command[i])
    {
        command[i] = (int)(command[i]) - 32;
        i++;
    }

    if (!strcmp(command, "PUSH")) 
    {
        fprintf(file_write,"%d", PUSH);
        return 1;
    }

    if (!strcmp(command, "IN"))    fprintf(file_write,"%d", IN);
    if (!strcmp(command, "HLT"))   fprintf(file_write,"%d", HLT);
    if (!strcmp(command, "OUT"))   fprintf(file_write,"%d", OUT);
    if (!strcmp(command, "SUB"))   fprintf(file_write,"%d", SUB);
    if (!strcmp(command, "ADD"))   fprintf(file_write,"%d", ADD);
    if (!strcmp(command, "MUL"))   fprintf(file_write,"%d", MUL);
    if (!strcmp(command, "DIV"))   fprintf(file_write,"%d", DIV);
    if (!strcmp(command, "SQRT"))  fprintf(file_write,"%d", SQRT);
    if (!strcmp(command, "SIN"))   fprintf(file_write,"%d", SIN);
    if (!strcmp(command, "COS"))   fprintf(file_write,"%d", COS);

    return 0;
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