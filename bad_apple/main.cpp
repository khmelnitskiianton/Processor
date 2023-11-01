#include "main.h"

int main(int argc, char* argv[])
{
    BadApple_t BadA = {};
    BufferCtor(&BadA);
    char c = 0;
    int flag = 0;
    while (!flag)    //пока не конец файла
    {
        for (int i = 0; i < WIDTH; i++) //строки
        {
            for (int j = 0; j < LENGTH; j++)   //символы в строке
            {
                c = fgetc(BadA.file_in);
                if ((c == '\n') || (c == '\r'))           //если дошли до конца раньше чем 100 
                {
                    for (int m = j; m < LENGTH; m++)       //заполняем остаток строки в оперативке 
                    {
                        fprintf(BadA.file_out, "\tpush %d\n\tpop [%d]\n", WHITE, m + i * LENGTH);
                    }
                    break;
                }
                
                if (c == EOF)   //проверка на конец и считывание
                {
                    flag = 1;
                    break;
                }

                if (c == '.' || isspace(c))
                {
                    fprintf(BadA.file_out, "\tpush %d\n\tpop [%d]\n", WHITE, j + i * LENGTH);
                }
                else
                {
                    fprintf(BadA.file_out, "\tpush %d\n\tpop [%d]\n", BLACK, j + i * LENGTH);   
                }
            }
            while ((c != '\n') && (c != EOF)) 
            {
                c = fgetc(BadA.file_in);
            }
            if (flag) {break;}
        }
        if (!flag)
        {
            fprintf(BadA.file_out, "\tdraw\n");   
        }
    }
    fprintf(BadA.file_out, "hlt\n");   
    return 0;
}

FILE* file_open_read (void)
{
    FILE *file_read = fopen ("bad_apple_clean.txt", "r");
    assert(file_read);
    return file_read;
}

FILE* file_open_write (void)
{
    FILE *file_write = fopen ("bad_apple_asm.txt", "w");
    assert(file_write);
    return file_write;
}

int BufferCtor (BadApple_t *myBadApple)
{
    myBadApple -> file_in  = file_open_read ();

    assert(myBadApple -> file_in);

    myBadApple -> file_out  = file_open_write ();

    assert(myBadApple -> file_out);

    return 1;
}

