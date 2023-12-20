# Processor

Its my simple processor!

It consists of my assembler and my spu and can process many interesting codes!

You can see 3 example programs on my asm: 
1. `qudratka.txt` - code of quadratic solver
2. `circle.txt` - code that draw circle in console
3. `factorial.txt` - code of recursive factorial
4. `bad_apple.txt` - code that draws BadApple movie in window with SDL(you need to switch branch)

## Table of Contents

- [Installation](#installation)
- [Extra programs](#extra-programs)
- [Using](#using)
- [Options of compiling](#options-of-compiling)
- [Logs](#logs)

## Installation

To start program you need to use CMake and run program

1.  Clone repository
2.  Compile CMake, write command in main directory in repo
3.  Run CMake (compile program), write command in main directory in repo
4.  Run program(before you need to create this file) 
```c
git clone https://github.com/khmelnitskiianton/Processor.git
cd ./Processor
cmake .
make
./processor.bat
```

## Extra programs

If you want to see BadApple movie, you need to install graphic lib - SDL/SDL2

```c
sudo apt install libsdl2-dev -y
```

## Using

My program took code on my asm from `input_text.txt`.

In processor I have stack, registers(`rax` - `rex`), RAM 

> After no argument functions, dont write any spaces/comments! (it is feature)\
> In another cases, you can write comments after `;` with any spaces

**Functions:** (in `main_hdr/commands.h`)

*push/pop*

+ `push <number>` - push number in stack
+ `push <reg>` - push value from register to stack
+ `push <reg> + number` - push value from register to stack
+ `push [number]` - push number from RAM with index = number to stack 
+ `push [<reg>]` - push number from RAM with index = value in register to stack 
+ `push [<reg> + number]` - push number from RAM with index = (value in register + number) to stack 

==============================================

+ `pop <reg>` - push number from stack(last ofc) to register
+ `pop [number]` - push number from stack to RAM with index = number
+ `pop [<reg>]` - push number from stack to RAM with index = value in register 
+ `pop [<reg> + number]` - push number from stack to RAM with index = (value in register + number)

*arifmethic operations*

+ `div` - take 2 numbers from stack and push there division to stack
+ `add` - take 2 numbers from stack and push there sum to stack
+ `mul` - take 2 numbers from stack and push there multipling to stack
+ `sub` - take 2 numbers from stack and push there subtract to stack
+ `sqrt` - take number from stack and push its square to stack
+ `cos` - take number from stack and push its cosinus to stack
+ `sin` - take number from stack and push its sinus to stack

*base operations*
+ `in` - ask to enter from console number 
+ `out` - take number from stack and print it to console
+ `outc` - take number from stack and print it char equivalent to console
+ `draw` - printing with SDL
+ `drawf` - printing RAM(actually for drawing circle)
+ `hlt` - end of code!

*labels,jumps and functions*

+ `<name_of_label>:` - put label to jump

==============================================

+ `jmp <name_of_label>` - command that jump your position to indicated label
+ `ja <name_of_label>` - takes 2 numbers from stack, compares it, and if (last above last_sec)  jump your position to indicated label
+ `jae <name_of_label>` - takes 2 numbers from stack, compares it, and if (last above or equal last_sec)  jump your position to indicated label
+ `jb <name_of_label>` - takes 2 numbers from stack, compares it, and if (last below last_sec)  jump your position to indicated label
+ `jbe <name_of_label>` - takes 2 numbers from stack, compares it, and if (last below or equal last_sec)  jump your position to indicated label
+ `jne <name_of_label>` - takes 2 numbers from stack, compares it, and if (last not equal last_sec)  jump your position to indicated label

==============================================
+ `call <name_of_label>` - go to label and do code before `ret` (like function!)
+ `ret` - stopper for call in label use in pair!

## Options of compiling

LISTING_MEMORY

LISTING_ASM

DEBUG_PRINTING

## Logs

For debugging I use `listing.txt` - printing asm

For debugging I use `log.txt` - printing cpu
