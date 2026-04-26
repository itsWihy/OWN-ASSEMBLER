TARGET    := assembler
CC        := gcc
CFLAGS    := -MMD -MP -I./include # -Wall -ansi -pedantic

BUILD_DIR := ./build
SRC_DIR   := ./src

SRCS      := $(shell find $(SRC_DIR) -type f -name *.c)
HEADS     := $(shell find ./include  -type f -name *.h)

OBJS = $(SRCS:$(SRC_DIR)/%.c=$(BUILD_DIR)/%.o)
DEPS = $(OBJS:.o=.d)

.PHONY: all clean run

all: $(TARGET)

run: all
	./$(TARGET) inputs/test1.as

clean:
	rm -rf $(TARGET) $(BUILD_DIR)

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^
	echo "Linked $^"

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@
	echo "Compiled $^"

-include $(DEPS)