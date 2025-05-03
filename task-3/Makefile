# Конфигурация
CC := gcc
BUILD_DIR ?= build

# Флаги
CFLAGS := -Wall -Wextra -pedantic -O2 -g

# Исходные файлы
C_SRC := $(wildcard *.c)

# Компиляция всех .c файлов в build/main.bin
all: always $(BUILD_DIR)/main.bin

$(BUILD_DIR)/main.bin:
	$(CC) $(CFLAGS) $(C_SRC) -o $@

# Всегда создавать директорию build/
always:
	mkdir -p $(BUILD_DIR)

# Очистка всех файлов сборки
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.o
	rm output.txt

# Не считать all, clean и always за имена файлов при вызове make
.PHONY: all clean always
