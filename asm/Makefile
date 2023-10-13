.PHONY: run clean
CFLAGS        = -Wshadow -Winit-self -Wredundant-decls -Wcast-align -Wundef -Wfloat-equal -Winline -Wunreachable-code -Wmissing-declarations -Wmissing-include-dirs -Wswitch-enum -Wswitch-default -Weffc++ -Wmain -Wextra -Wall -g -pipe -fexceptions -Wcast-qual -Wconversion -Wctor-dtor-privacy -Wempty-body -Wformat-security -Wformat=2 -Wignored-qualifiers -Wlogical-op -Wno-missing-field-initializers -Wnon-virtual-dtor -Woverloaded-virtual -Wpointer-arith -Wsign-promo -Wstack-usage=8192 -Wstrict-aliasing -Wstrict-null-sentinel -Wtype-limits -Wwrite-strings -Werror=vla -D_DEBUG -D_EJUDGE_CLIENT_SIDE
TARGET        = asm
CC            = g++
CHDRS         = -I ./hdrs/ -I ../main_hdrs/
PREF_SRC      = src/
PREF_OBJ      = obj/
PREF_HDRS     = hdrs/
PREF_MAINHDRS = ../main_hdrs

SRC           = $(wildcard $(PREF_SRC)*.cpp)
HDRS          = $(wildcard $(PREF_HDRS)*.h)
MHDRS         = $(wildcard $(PREF_MAINHDRS)*.h)
OBJ           = $(patsubst $(PREF_SRC)%.cpp, $(PREF_OBJ)%.o, $(SRC))

$(TARGET): $(OBJ)
	$(CC) $(CHDRS) $(CFLAGS) $^ -o $@

$(PREF_OBJ)%.o: $(PREF_SRC)%.cpp $(HDRS) $(MHDRS)
	$(CC) $(CHDRS) $(CFLAGS) -c $< -o $@ 

run: 
	"./$(TARGET)"
clean:
	del ".\obj\*.o"  
