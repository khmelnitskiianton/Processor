CC = g++

SHELL = C:/Windows/System64/cmd.exe

EXECUTABLE_SPU = spu.exe
EXECUTABLE_ASM = asm.exe
EXECUTABLE_DISASM = disasm.exe

CFLAGS = -c -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE

all: start_spu start_asm start_disasm run_asm run_disasm run_spu clean 

start_spu: main_spu.o spu_stack.o spu_math.o spu_support.o
	$(CC) main_spu.o spu_stack.o spu_math.o spu_support.o -o $(EXECUTABLE_SPU)
start_asm: main_asm.o asm.o
	$(CC) main_asm.o asm.o -o $(EXECUTABLE_ASM)
start_disasm: main_disasm.o
	$(CC) main_disasm.o -o $(EXECUTABLE_DISASM)

main_asm.o:
	$(CC) main_asm.cpp $(CFLAGS)
asm.o:
	$(CC) asm.cpp $(CFLAGS)
main_disasm.o:
	$(CC) main_disasm.cpp $(CFLAGS)
main_spu.o:
	$(CC) main_spu.cpp $(CFLAGS)
spu_stack.o:
	$(CC) spu_stack.cpp $(CFLAGS)
spu_math.o:
	$(CC) spu_math.cpp $(CFLAGS)
spu_support.o:
	$(CC) spu_support.cpp $(CFLAGS)

run_spu: 
	"./$(EXECUTABLE_SPU)"
run_asm: 
	"./$(EXECUTABLE_ASM)"
run_disasm: 
	"./$(EXECUTABLE_DISASM)"

clean:
	del ".\*.o" 