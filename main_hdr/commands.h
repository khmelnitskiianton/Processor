DEF_CMD(push, 0, 0b000'00001, 
{
    ArgCMD_t myArgCMD = {};
    myArgCMD.value = POISON_ELEMENT; 

    GetArg (myCpu, command, &myArgCMD);

    if (command & ARG_FORMAT_MEMORY) 
    {
        push (&(myCpu -> myStack), myCpu -> myMemory[myArgCMD.result]);
    }
    else
    {
        push (&(myCpu -> myStack), myArgCMD.result);
    }
ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(pop, 1, 0b000'00010,
{
    ArgCMD_t myArgCMD = {};

    myArgCMD.value = POISON_ELEMENT; 

    GetArg (myCpu, command, &myArgCMD);

    if (command & ARG_FORMAT_MEMORY) 
    {
        pop (&(myCpu -> myStack), &(myCpu -> myMemory[myArgCMD.result]));
    }
    else
    {
        if (command & ARG_FORMAT_IMMED) 
        {
            printf("\n>>>>>POP WITH NUMBER!!! WTF?!<<<<<\n"); 
        }
        else  
        {
           if ((myArgCMD.reg >= 0) && (myArgCMD.reg <= AMOUNT_OF_REGISTERS)) pop(&(myCpu -> myStack), &(myCpu -> myRegs[myArgCMD.reg]));
           else printf(">>>>>UNKNOWN REGISTER<<<<<");
        }
    }
ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(in, 2, 0b000'00011, 
{
    double num = POISON_ELEMENT;
    printf("Enter value please to put in stack: ");
    while(scanf ("%lf", &num) != 1)
    {   
        clean_buffer ();
        printf ("\nWtf? Its not normal double number. Maybe it is infinite/NAN number or letters. Another attempt you piece of shit, hey you, MAAAAN!\n");
    }
    if (((num * N_DIGIT) < ((double) INT_MIN)) || ((num * N_DIGIT) > (double) INT_MAX))
    {
        printf("\n>>>>>THE SIZE OF THIS NUMBER SO BIG THAT OVERFLOW ME !!! GOODBYE <<<<<\n");
        assert(0);
    }
    push (&(myCpu -> myStack), (int) (num * N_DIGIT));
}
)

DEF_CMD(div, 3, 0b000'00100, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &y);
    pop(&(myCpu -> myStack), &x);
    push(&(myCpu -> myStack), (x * N_DIGIT) / y);
ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(add, 4, 0b000'00101, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &y);
    pop(&(myCpu -> myStack), &x);
    push(&(myCpu -> myStack), x + y);
ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(mul, 5, 0b000'00110,
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &y);
    pop(&(myCpu -> myStack), &x);
    push(&(myCpu -> myStack), x * y / N_DIGIT);
ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(sqrt, 6, 0b000'00111, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &x);
    double z =  sqrt(((double) x) / N_DIGIT);
    if (x >= 0) push(&(myCpu -> myStack), (int) (z * N_DIGIT));
    else printf(">>>>>SQRT(X) < 0 !!!<<<<<");

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(sub, 7, 0b000'01000, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &y);
    pop(&(myCpu -> myStack), &x);
    push(&(myCpu -> myStack), x - y);

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(cos, 8, 0b000'01001, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &x);
    double z =  cos(((double) x) / N_DIGIT);
    push(&(myCpu -> myStack), (int) (z * N_DIGIT));

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(sin, 9, 0b000'01010, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(myCpu -> myStack), &x);
    double z =  sin(((double) x) / N_DIGIT);
    push(&(myCpu -> myStack), (int) (z * N_DIGIT));

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(out, 10, 0b000'01011, 
{
    Elem_t result = POISON_ELEMENT;
    pop (&(myCpu -> myStack), &result);
 
    fprintf (stdout, "%lf\n", ((double) result) / N_DIGIT);

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)
}
)

DEF_CMD(jmp, 11, 0b000'01100,
{
    (myCpu -> actual_command)++;
    Elem_t jump = *((myCpu -> actual_command));
    (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    return IF_LABEL;
}
)

DEF_CMD(ja, 12, 0b000'01101,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);

    (myCpu -> actual_command)++;
    if (last > sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;

}
)

DEF_CMD(jae, 13, 0b000'01110,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);
    
    (myCpu -> actual_command)++;
    if (last >= sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;
}
)

DEF_CMD(jb, 14, 0b000'01111,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);
    
    (myCpu -> actual_command)++;
    if (last < sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;
}
)

DEF_CMD(jbe, 15, 0b000'10000,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);
    
    (myCpu -> actual_command)++;
    if (last <= sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;
}
)

DEF_CMD(je, 16, 0b000'10001,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);
    (myCpu -> actual_command)++;
    if (last == sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;
}
)

DEF_CMD(jne, 17, 0b000'10011,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(myCpu -> myStack), &last);
    pop(&(myCpu -> myStack), &sec_last);

    (myCpu -> actual_command)++;
    if (last != sec_last)
    {
        Elem_t jump = *((myCpu -> actual_command));
        (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    }
    else (myCpu -> actual_command)++;
    return IF_LABEL;
}
)

DEF_CMD(call, 18, 0b000'10100,
{
    (myCpu -> actual_command)++;

    push(&(myCpu -> myStackReturns), (Elem_t) ((myCpu -> actual_command) - (myCpu -> myBuffer.text_buffer)));

    Elem_t jump = *((myCpu -> actual_command));
    (myCpu -> actual_command) = (myCpu -> myBuffer.text_buffer + jump);
    return IF_LABEL;
}
)

DEF_CMD(ret, 19, 0b000'10101,
{
    int shift = 0;
    pop(&(myCpu -> myStackReturns), &shift);
    myCpu -> actual_command = myCpu -> myBuffer.text_buffer + shift;
}
)

DEF_CMD(outc, 20, 0b000'10110,
{
    Elem_t result = POISON_ELEMENT;
    pop (&(myCpu -> myStack), &result);
    fprintf (stdout, "%c", result / N_DIGIT);

ON_LISTING_MEMORY(
    PrintMemoryListing(myCpu);
)   
}
)

DEF_CMD(draw, 21, 0b000'10111,
{
    static int isInit = 1;
    if (isInit) 
    {
        SDL_Init(SDL_INIT_VIDEO);
        SDL_CreateWindowAndRenderer(LENGTH_OF_SCREEN, WIDTH_OF_SCREEN, 0, &(myCpu -> window), &(myCpu -> renderer));
        SDL_SetRenderDrawColor(myCpu -> renderer, 0, 0, 0, 0);
        SDL_RenderClear(myCpu -> renderer);
        isInit = 0;
    }

    SDL_SetRenderDrawColor(myCpu -> renderer, 255, 255, 255, 255);

    for (size_t i = 0; i < WIDTH_OF_WINDOW; i++)
    {
        for (size_t j = 0; j < LENGTH_OF_WINDOW; j++)
        {
            if (myCpu -> myMemory[j + i * LENGTH_OF_WINDOW])
            {
                SDL_Rect rect1 = {(int) j * SIZE_OF_SQUARE, (int) i * SIZE_OF_SQUARE, SIZE_OF_SQUARE, SIZE_OF_SQUARE};
                SDL_RenderFillRect(myCpu -> renderer, &rect1);
            }
        }
    }
    static SDL_Event e;
    while(SDL_PollEvent(&e)) 
    {
        if(e.type == SDL_QUIT)
        {
            CpuDtor (myCpu);
            SDL_DestroyRenderer(myCpu -> renderer);
            SDL_DestroyWindow(myCpu -> window);
            SDL_Quit();
            exit(0);
        }
    }


    SDL_RenderPresent(myCpu -> renderer);

    SDL_SetRenderDrawColor(myCpu -> renderer, 0, 0, 0, 0);
    usleep(75e3);

    SDL_RenderClear(myCpu -> renderer);
}
)
 
DEF_CMD(drawf, 22, 0b000'11000,
{
    for (size_t i = 0; i < SIZE_IN_CONSOLE; i++)
    {
        for (size_t j = 0; j < SIZE_IN_CONSOLE; j++)
        {
            if ((i * SIZE_IN_CONSOLE + j) % SIZE_IN_CONSOLE == 0) fprintf(stdout, "\n");
            if (myCpu -> myMemory[i * SIZE_IN_CONSOLE + j] == 0) fprintf (stdout, " . ");
            if (myCpu -> myMemory[i * SIZE_IN_CONSOLE + j] == 1*N_DIGIT) fprintf (stdout, " 0 ");
        }
    }
}
)

DEF_CMD(hlt, 23, 0b000'11111, 
{
    SDL_DestroyRenderer(myCpu -> renderer);
    SDL_DestroyWindow(myCpu -> window);
    SDL_Quit();    
    return IF_HLT;
}
)