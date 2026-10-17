PROGRAM := marshc
BUILD ?= debug

SOURCE_DIRS := src
SOURCES := $(foreach dir,$(SOURCE_DIRS),$(wildcard $(dir)/*.c))

ifeq ($(OS),Windows_NT)
  EXE_EXT := .exe
  MKDIR = if not exist "$(subst /,\,$(@D))" mkdir "$(subst /,\,$(@D))"
  CLEAN = if exist "build" rmdir /S /Q "build"
else
  EXE_EXT :=
  MKDIR = mkdir -p "$(@D)"
  CLEAN = rm -rf build
endif

ifeq ($(BUILD),debug)
  MODE_FLAGS := -O0 -g
else ifeq ($(BUILD),release)
  MODE_FLAGS := -O2 -DNDEBUG
else
  $(error Unknown BUILD=$(BUILD); use debug or release)
endif

CFLAGS ?= -std=c11 -Wall -Wextra -Wpedantic
CPPFLAGS ?=
LDFLAGS ?=
LDLIBS ?=

BUILD_DIR := build/$(BUILD)
OBJ_DIR := $(BUILD_DIR)/obj
TARGET := $(BUILD_DIR)/$(PROGRAM)$(EXE_EXT)
OBJECTS := $(patsubst %.c,$(OBJ_DIR)/%.o,$(SOURCES))
DEPS := $(OBJECTS:.o=.d)

.DEFAULT_GOAL := all
.PHONY: all clean help

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(MKDIR)
	$(CC) $(LDFLAGS) -o "$@" $(OBJECTS) $(LDLIBS)

$(OBJ_DIR)/%.o: %.c
	$(MKDIR)
	$(CC) $(CPPFLAGS) -Iinclude $(CFLAGS) $(MODE_FLAGS) -MMD -MP -c "$<" -o "$@"

clean:
	$(CLEAN)

help:
	@echo "make                  Build debug version"
	@echo "make BUILD=release    Build release version"
	@echo "make clean            Remove build files"

-include $(DEPS)
