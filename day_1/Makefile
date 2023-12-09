CC 		:= gcc
CFLAGS  :=
LDFLAGS := -lm

OBJ_DIR := obj

SRC 	:= $(wildcard *.c)
OBJ 	:= $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
EXE 	:= $(patsubst %.c, %, $(SRC))

all: makedir build

makedir:
	mkdir -p $(OBJ_DIR)

build: $(OBJ) $(EXE)

$(OBJ): $(SRC)
	$(CC) -c -o $@ $(patsubst obj/%.o, %.c, $@)

$(EXE): $(OBJ)
	$(CC) obj/$@.o -o $@ $(LDFLAGS)

clean:
	rm -f $(OBJ) $(EXE)

refresh: clean all

.PHONY: clean all
