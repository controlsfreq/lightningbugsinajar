

### Build Commands ###
CC = avr-gcc
AR = avr-ar
OBJCOPY = avr-objcopy
PROG = avrdude

### Shell Commands ###
MKDIR = mkdir -p
RM    = rm -f
RMDIR = rm -fr
TOUCH = touch

### Fuse Bits ###
LFUSE = 0xE2
HFUSE = 0xDF
EFUSE = 0xFF

### Build Flags ###
PRNG_SEED := $(shell echo $$RANDOM)
CC_FLAGS = -g -mmcu=attiny85 -Wall -Werror -Os -D LBJ_MAJOR_VERSION=$(MAJOR_VERSION) -D LBJ_MINOR_VERSION=$(MINOR_VERSION) -D LBJ_PATCH_VERSION=$(PATCH_VERSION) -D PRNG_SEED=$(PRNG_SEED)
LINK_FLAGS = -g -mmcu=attiny85 -Wl,-Map,$(OUTPUT_DIR)/$(TARGET:.hex=.map) -Wl,-T,linker/attiny85.x
AR_FLAGS = rcs
OBJCOPY_FLAGS = -j .text -j .data -O ihex
PROG_FLAGS = -p t85 -c avrispmkII -P usb -U lfuse:w:$(LFUSE):m -U hfuse:w:$(HFUSE):m -U efuse:w:$(EFUSE):m

### Rebuild Flag ###
REBUILD =

### Directories ###
BUILD_DIR = ./build
OUTPUT_DIR = ./output
SOURCE_DIR = ./source
HEADER_DIR = ./include

### Output Files ###
TARGET = lbj.hex

### Source Files ###
APP_SOURCES = $(SOURCE_DIR)/main.c \
              $(SOURCE_DIR)/pin_avr.c \
              $(SOURCE_DIR)/spi_avr.c \
              $(SOURCE_DIR)/tlc591x_avr.c \
              $(SOURCE_DIR)/ufprng_com.c \
              $(SOURCE_DIR)/avr_timer.c \
              $(SOURCE_DIR)/controller.c \
              $(SOURCE_DIR)/bsp.c

APP_HEADERS = $(HEADER_DIR)/controller.h \
              $(HEADER_DIR)/pin.h \
              $(HEADER_DIR)/spi.h \
              $(HEADER_DIR)/tlc591x.h \
              $(HEADER_DIR)/ufprng.h \
              $(HEADER_DIR)/timer.h \
              $(HEADER_DIR)/bsp.h

APP_OBJECTS = $(addprefix $(BUILD_DIR)/,$(notdir $(APP_SOURCES:.c=.o)))

### Build Dependencies ###
-include $(APP_OBJECTS:.o=.d)
include version.mk

### Build Targets ###
all: build install

build: $(OUTPUT_DIR)/$(TARGET)

rebuild:
	@make build FORCE="force"

install: $(OUTPUT_DIR)/$(TARGET)
	$(PROG) $(PROG_FLAGS) -v -U flash:w:$(OUTPUT_DIR)/$(TARGET)

reinstall:
	@make install FORCE="force"

$(BUILD_DIR)/%.o: $(SOURCE_DIR)/%.c $(FORCE)
	@$(MKDIR) $(BUILD_DIR)
	$(CC) $(CC_FLAGS) -I$(HEADER_DIR) -c $< -o $@
	$(CC) $(CC_FLAGS) -I$(HEADER_DIR) -MM $< | sed "1 s|^|$(BUILD_DIR)/|" > $(BUILD_DIR)/$*.d

$(BUILD_DIR)/$(TARGET:.hex=.elf): $(APP_OBJECTS) $(FORCE)
	@$(MKDIR) $(OUTPUT_DIR)
	@echo "PRNG seed: $(PRNG_SEED)"
	$(CC) $(LINK_FLAGS) -o $@ $(APP_OBJECTS)

$(OUTPUT_DIR)/$(TARGET): $(BUILD_DIR)/$(TARGET:.hex=.elf) $(FORCE)
	$(OBJCOPY) $(OBJCOPY_FLAGS) $(BUILD_DIR)/$(TARGET:.hex=.elf) $(OUTPUT_DIR)/$(TARGET)

clean:
	$(RMDIR) $(BUILD_DIR)
	$(RMDIR) $(OUTPUT_DIR)

force:

.PHONY: all build install clean force