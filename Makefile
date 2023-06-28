CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter
SRC_FILES = $(wildcard *.c)
O_FILES = $(patsubst %.c, %.o, $(SRC_FILES))

all: test

test: $(O_FILES)
	$(CC) $(CFLAGS) -o test.exe $^

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o test
