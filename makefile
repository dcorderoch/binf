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
CFLAGS := -O2 -W -Wall -g

all : $(EXE)

$(EXE) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(EXE)
$(ODIR)/%.o : $(SDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY : clean
clean:
	rm -f $(OBJ) $(EXE)
