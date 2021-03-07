TARGET = pda-1
TEST_TARGET = $(TARGET)-test
CC = gcc
RM = rm -f
CFLAGS = -Wall -std=c99

TEST_LIBS = -lcheck -lrt -lm -lpthread -lsubunit
BUILD_DIR = ./build
SRC_DIR = ./
TEST_DIR = ./tests/
TEST_BUILD_DIR = ./tests/build/
MAIN_OBJECT_FILE = main.c.o
# $(shell ls $(SRC_DIR) | grep .c$)
# export LC_ALL=ru_RU

SRCS = $(shell find $(SRC_DIR) -maxdepth 1 -type f -name "*.c" -printf "%f\n" | sort)
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

TEST_SRCS = $(shell find $(TEST_DIR) -type f  -and -name "*.c" -printf "%f\n" | sort)
TEST_OBJS = $(TEST_SRCS:%=$(TEST_BUILD_DIR)/%.o)

#INC_DIRS := $(shell find $(SRC_DIR) -type h)
#INC_FLAGS := $(addprefix -I,$(INC_DIRS))

build: $(OBJS)
	$(CC) $(OBJS) -o $(TARGET)
	@echo "exe-file:" $(TARGET)

$(BUILD_DIR)/%.c.o: %.c
	$(MKDIR_P) $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


# ТЕСТЫ

test : $(TEST_TARGET)
	$(TEST_DIR)$<

$(TEST_TARGET): $(TEST_OBJS)
	$(CC) $(TEST_OBJS) $(shell find $(OBJS) -not -name $(MAIN_OBJECT_FILE)) -o $(TEST_DIR)$@ $(TEST_LIBS)

$(TEST_BUILD_DIR)%.c.o: $(TEST_DIR)%.c
	$(MKDIR_P) $(TEST_BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean

clean:
	$(RM) -r $(BUILD_DIR) $(TARGET)
	$(RM) -r $(TEST_BUILD_DIR) $(TEST_DIR)$(TEST_TARGET)
MKDIR_P ?= mkdir -p