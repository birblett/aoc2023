CC := gcc
CFLAGS := -c -I../lib/include/
LDFLAGS := 

OBJ_DIR := obj

CUSTOM_LIBS := str_utils
LIBSRC := $(patsubst %, ../lib/src/%.c, $(CUSTOM_LIBS))
LIBOBJ := $(patsubst %, $(OBJ_DIR)/%.o, $(CUSTOM_LIBS))
SRC := $(wildcard *.c)
OBJ := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC))
EXE := $(patsubst %.c, %, $(SRC))

all: makedir libs build

libs: $(LIBOBJ)
	
$(LIBOBJ): $(LIBSRC)
	$(CC) $(CFLAGS) -o $@ $(patsubst obj/%.o, ../lib/src/%.c, $@)

makedir:
	mkdir -p $(OBJ_DIR)

build: $(OBJ) $(EXE)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(patsubst obj/%.o, %.c, $@)

$(EXE): $(OBJ)
	$(CC) obj/$@.o $(LIBOBJ) -o $@ $(LDFLAGS)

clean:
	rm -f $(LIBOBJ) $(OBJ) $(EXE)

refresh: clean all

.PHONY: clean all
