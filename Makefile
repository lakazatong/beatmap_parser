CC=gcc
CFLAGS=-g3 -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-unused-value
SRC_FILES:=$(wildcard *.c)
SRC_FILES+=$(wildcard libs/c_utils/utils/*.c)
OFILES:=$(SRC_FILES:.c=.o)

all: test

test: $(OFILES)
	$(CC) $(CFLAGS) -o bm_parser $^

clean:
	rm -rf $(OFILES) bm_parser bm_parser.exe
