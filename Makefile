MAKE := make
BUILD_DIR := build

# Список всех директорий с задачами
TASK_DIRS := $(wildcard task-*)

# Сборка всех задач
all: 
	@for dir in $(TASK_DIRS); do \
		$(MAKE) -C $$dir || true; \
	done

# Удаление результата сборки
clean:
	@for dir in $(TASK_DIRS); do \
		$(MAKE) -C $$dir clean || true; \
	done

gen_docs:
	doxygen Doxyfile

clean_docs:
	rm -rf docs/*

.PHONY: all clean gen_docs clean_docs
