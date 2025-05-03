# Конфигурация
CC := gcc
BUILD_DIR ?= build

# Флаги
CFLAGS := -Wall -Wextra -pedantic -O2 -g

# Исходные файлы
C_SRC := $(wildcard *.c)

all: always $(BUILD_DIR)/short.bin $(BUILD_DIR)/long.bin

$(BUILD_DIR)/short.bin:
	$(CC) $(CFLAGS) short.c -o $@

$(BUILD_DIR)/long.bin:
	$(CC) $(CFLAGS) short.c -o $@

# Всегда создавать директорию build/
always:
	mkdir -p $(BUILD_DIR)

# Очистка всех файлов сборки
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.o

# Не считать all, clean и always за имена файлов при вызове make
.PHONY: all clean always
