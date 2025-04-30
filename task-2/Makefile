# Конфигурация
CC := gcc
BUILD_DIR ?= build

# Флаги
CFLAGS := -Wall -Wextra -pedantic -O2 -g

all: always $(BUILD_DIR)/server.bin $(BUILD_DIR)/client.bin

$(BUILD_DIR)/server.bin:
	$(CC) $(CFLAGS) server.c -o $@
	
$(BUILD_DIR)/client.bin:
	$(CC) $(CFLAGS) client.c -o $@

# Всегда создавать директорию build/
always:
	mkdir -p $(BUILD_DIR)

# Очистка всех файлов сборки
clean:
	rm -rf $(BUILD_DIR)
	rm -f *.o

# Не считать all, clean и always за имена файлов при вызове make
.PHONY: all clean always
