# \
-l -l'library' Search the library named library when linking. put always at the end \
-Ldir Add directory dir to the list of directories to be searched for -l. \
-I dir Add the directory dir to the list of directories to be searched for header files

SDIR := src
SOURCES := main.c
SOURCE := $(patsubst %,$(SDIR)/%,$(SOURCES))
ODIR := obj
_OBJ := $(SOURCES:.c=.o)
OBJ := $(patsubst %,$(ODIR)/%,$(_OBJ))
EXE := binf

CC := gcc
CFLAGS := -O3 -W -Wall -g -lpthread

all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(OBJ) -o $(EXE) $(CFLAGS)
$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) -c -o $@ $< $(CFLAGS)
.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE)
.PHONY : run
run : all
	./$(EXE)
