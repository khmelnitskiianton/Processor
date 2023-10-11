.PHONY: asm disasm spu
#ASM    = ./asm/asm.exe
#DISASM = ./disasm/disasm.exe
#SPU    = ./spu/spu.exe

all: asm disasm spu
	
asm: 
	"./asm/asm.exe"
disasm: 
	"./disasm/disasm.exe"
spu: 
	"./spu/spu.exe"