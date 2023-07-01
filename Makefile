CC = gcc
CFLAGS = -Wall -Wextra -Wno-unused-variable -Wno-unused-parameter -Wno-unused-value
# source: https://stackoverflow.com/questions/2483182/recursive-wildcards-in-gnu-make/18258352#18258352
rwildcard = $(foreach d,$(wildcard $(1:=/*)),$(call rwildcard,$d,$2) $(filter $(subst *,%,$2),$d))
SRC_FILES := $(call rwildcard,.,*.c)
OBJ_DIR := obj
O_FILES := $(patsubst %.c, $(OBJ_DIR)/%.o, $(SRC_FILES))

all: test

test: $(O_FILES)
	$(CC) $(CFLAGS) -o test.exe $^

$(OBJ_DIR)/%.o: %.c
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf $(OBJ_DIR) test.exe
