CC := gcc
CFLAGS := -c -I../lib/include/
LDFLAGS := 

SRC := $(wildcard src/*.c)
OBJ := $(patsubst src/%.c, obj/%.o, $(SRC))

all: makedir build

makedir:
	mkdir -p obj

build: $(OBJ)

$(OBJ): $(SRC)
	$(CC) $(CFLAGS) -o $@ $(patsubst obj/%.o, src/%.c, $@)

clean:
	rm -f $(OBJ)

refresh: clean all

.PHONY: clean all
