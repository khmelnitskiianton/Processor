#include "head.h"

int main(void)
{
    FILE* file_read  = file_read_asm  ();
    FILE* file_write = file_write_asm ();
    int ch = NULL;
    char command[10] = {};
    Elem_t argument = POISON_ELEMENT;
    int i = 0;
    int sec_argu = NULL;
    while ((ch = fgetc(file_read)) != EOF)
    {
        while ((ch != ' ')&&(ch != '\n')&&(ch != EOF))
        {
            if (ch != '\r')
            {
                command[i] = ch;
            }
            i++;
            ch = fgetc(file_read);
        }
        sec_argu = compare_command(command, file_write);
        if ((sec_argu)&&(fscanf(file_read,"%lf", &argument) == 1))
        {
            fprintf(file_write, " " SPECIFIER, argument);
        }
        if (ch == EOF) break;
        fprintf(file_write, "\n");
        clean_str(command);
        if (ch == ' ') 
        {
            ch = fgetc(file_read);
            ch = fgetc(file_read);
        }
        i = 0;
    }
    file_close_asm(file_read);
    file_close_asm(file_write);
    return 0;
}