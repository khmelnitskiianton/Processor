DEF_CMD(push, PUSH_NUM, 0, 0b001'00001, 
{
    Elem_t value = *(++(mySpu -> actual_command));
    if (!COMPARE_TYPE(value, POISON_ELEMENT)) push (&(mySpu -> myStack), value);
    else printf("\n\n>>>WARNING<<<\nVALUE == NULL!!!\n\n");
}
)

DEF_CMD(push, PUSH_REG, 1, 0b010'00001, 
{
    int n_reg = (int) *(++(mySpu -> actual_command));
    if (n_reg != NULL) 
    {
        switch (n_reg)
        {
            case 1:         push(&(mySpu -> myStack), mySpu -> rax);            break; 
            case 2:         push(&(mySpu -> myStack), mySpu -> rbx);            break;
            case 3:         push(&(mySpu -> myStack), mySpu -> rcx);            break;
            case 4:         push(&(mySpu -> myStack), mySpu -> rdx);            break;
        }
    }
    else printf("\n\n>>>WARNING<<<\nREG NUMBER == NULL!!!\n\n");
}
)

DEF_CMD(pop,  POP_REG , 2, 0b010'00010,
{
    int n_reg = (int) *(++(mySpu -> actual_command));
    if (n_reg != NULL) 
    {
        switch (n_reg)
        {
            case 1:         pop(&(mySpu -> myStack), &(mySpu -> rax));          break;
            case 2:         pop(&(mySpu -> myStack), &(mySpu -> rbx));          break;
            case 3:         pop(&(mySpu -> myStack), &(mySpu -> rcx));          break;
            case 4:         pop(&(mySpu -> myStack), &(mySpu -> rdx));          break;
            default:        printf(">>>>>UNKNOWN REGISTER<<<<<")                break;
        }
    }
    else printf("\n\n>>>WARNING<<<\nREG NUMBER == NULL!!!\n\n");
}
)

DEF_CMD(in,   IN,       3, 0b000'00011, 
{
    double num = POISON_ELEMENT;
    printf("Enter value please to put in stack: ");
    while(scanf ("%lf", &num) != 1)
    {   
        clean_buffer ();
        printf ("\nWtf? Its not normal double number. Maybe it is infinite/NAN number or letters. Another attempt you piece of shit, hey you, MAAAAN!\n");
    }
    push (&(mySpu -> myStack), (int) (num * N_DIGIT));
}
)

DEF_CMD(div,  DIV,      4, 0b000'00100, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), (x * N_DIGIT) / y);
}
)

DEF_CMD(add,  ADD,      5, 0b000'00101, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), x + y);
}
)

DEF_CMD(mul,  MUL,      6, 0b000'00110,
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), x * y / N_DIGIT);
}
)

DEF_CMD(sqrt, SQRT,     7, 0b000'00111, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
    double z =  sqrt(((double) x) / N_DIGIT);
    if (x >= 0) push(&(mySpu -> myStack), (int) (z * N_DIGIT));
}
)

DEF_CMD(sub,  SUB,      8, 0b000'01000, 
{
    Elem_t x = POISON_ELEMENT;
    Elem_t y = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &y);
    pop(&(mySpu -> myStack), &x);
    push(&(mySpu -> myStack), x - y);
}
)

DEF_CMD(cos,  COS,      9, 0b000'01001, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
    double z =  cos(((double) x) / N_DIGIT);
    push(&(mySpu -> myStack), (int) (z * N_DIGIT));
}
)

DEF_CMD(sin,  SIN,     10, 0b000'01010, 
{
    Elem_t x = POISON_ELEMENT;
    pop(&(mySpu -> myStack), &x);
    double z =  sin(((double) x) / N_DIGIT);
    push(&(mySpu -> myStack), (int) (z * N_DIGIT));
}
)

DEF_CMD(out,  OUT,     11, 0b000'01011, 
{
    Elem_t result = POISON_ELEMENT;
    pop (&(mySpu -> myStack), &result);

    if ((mySpu -> myStack.size) > 0) printf("\n\n>>>WARNING<<<\nYour Stack is not empty now!!!\n\n"); 
    fprintf (mySpu -> myBuffer.file_out, "%lf", ((double) result) / N_DIGIT);
}
)

DEF_CMD(jmp, JMP,      12, 0b000'01100,
{
    (mySpu -> actual_command)++;
    Elem_t jump = *((mySpu -> actual_command));
    (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    return IF_LABEL;
}
)

DEF_CMD(ja,  JA,       13, 0b000'01101,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);

    if (last > sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;

}
)

DEF_CMD(jae,  JAE,       14, 0b000'01110,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);
    
    if (last >= sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;
}
)

DEF_CMD(jb,  JB,       15, 0b000'01111,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);
    
    if (last < sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;
}
)

DEF_CMD(jbe,  JBE,       16, 0b000'10000,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);
    
    if (last <= sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;
}
)

DEF_CMD(je,  JE,       17, 0b000'10001,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);

    if (last == sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;
}
)

DEF_CMD(jne,  JNE,       18, 0b000'10011,
{
    Elem_t last     = POISON_ELEMENT;
    Elem_t sec_last = POISON_ELEMENT;
    
    pop(&(mySpu -> myStack), &last);
    pop(&(mySpu -> myStack), &sec_last);

    if (last != sec_last)
    {
        (mySpu -> actual_command)++;
        Elem_t jump = *((mySpu -> actual_command));
        (mySpu -> actual_command) = (mySpu -> myBuffer.text_buffer + jump);
    }
    return IF_LABEL;
}
)

DEF_CMD(hlt,  HLT,     19, 0b000'11111, {return IF_HLT;})