.PHONY: asm disasm spu

all: asm spu
	
asm: 
	"./asm/asm.exe"
disasm: 
	"./disasm/disasm.exe"
spu: 
	"./spu/spu.exe"