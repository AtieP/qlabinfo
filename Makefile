SRC := $(shell find -type f -name '*.c')
OBJ := $(SRC:.c=.o)

CC = gcc
CCFLAGS := -Wall -Werror -Wextra --std=c11

LDFLAGS := -lSDL2 $(shell curl-config --libs) -lSDL2_image

TARGET = qlabinfo

.PHONY: clean

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) $^ -o $@

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@

run:
	./$(TARGET)

clean:
	rm -f $(OBJ) $(TARGET)
