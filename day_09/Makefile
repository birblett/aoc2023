CC := gcc
CFLAGS := -c -I../lib/include/
LDFLAGS := 
CUSTOM_LIBS := strutils

OBJ_DIR := obj
LIB_DIR := ../lib/obj
LIBOBJ := $(patsubst %, $(LIB_DIR)/%.o, $(CUSTOM_LIBS))
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
EXE := $(patsubst %.c, %, $(SRC))

all: makedir build

makedir:
	mkdir -p $(OBJ_DIR)

build: $(OBJ) $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(patsubst obj/%.o, %.c, $@)

$(EXE): $(OBJ)
	$(CC) obj/$@.o $(LIBOBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXE)

refresh: clean all

.PHONY: clean all
