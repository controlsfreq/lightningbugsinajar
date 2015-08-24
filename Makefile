

### Build Commands ###
CC = gcc
AR = avr-ar

### Shell Commands ###
MKDIR = mkdir -p
RM    = rm -f
RMDIR = rm -fr

### Build Flags ###
CC_FLAGS = -Wall -Werror -D LBJ_MAJOR_VERSION=$(MAJOR_VERSION) -D LBJ_MINOR_VERSION=$(MINOR_VERSION) -D LBJ_PATCH_VERSION=$(PATCH_VERSION)
AR_FLAGS = rcs

### Directories ###
BUILD_DIR = ./build
OUTPUT_DIR = ./output
SOURCE_DIR = ./source
HEADER_DIR = ./include

### Output Files ###
TARGET = lbj.hex

### Source Files ###
APP_SOURCES = $(SOURCE_DIR)/main.c \
              $(SOURCE_DIR)/controller.c \
              $(SOURCE_DIR)/bsp.c

APP_HEADERS = $(HEADER_DIR)/controller.h \
              $(HEADER_DIR)/bsp.h

APP_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(APP_SOURCES:.c=.o)))

### Build Dependencies ###
-include $((APP_OBJECTS):.c,.d)
include version.mk

### Build Targets ###
all: build install

build: $(APP_OBJECTS)
	@$(MKDIR) $(OUTPUT_DIR)
	$(CC) $(CC_FLAGS) -o $(OUTPUT_DIR)/$(TARGET) $^

install: $(OUTPUT_DIR)/$(TARGET)

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c
	@$(MKDIR) $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -I$(HEADER_DIR) -c $< -o $@
	$(CC) $(CC_FLAGS) -I$(HEADER_DIR) -MM $< | sed "1 s|^|$(BUILD_DIR)/|" > $(BUILD_DIR)/$*.d

clean:
	$(RMDIR) $(BUILD_DIR)
	$(RMDIR) $(OUTPUT_DIR)

.PHONY: all build install clean