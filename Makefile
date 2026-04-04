SRC_DIR := src
INC_DIR := include
BUILD_DIR := build
DIST_DIR := dist

CC := gcc
BASE_CFLAGS := -Wall -Wextra -I$(INC_DIR) $(shell sdl2-config --cflags)
LDFLAGS := $(shell sdl2-config --libs) \
           -lSDL2_ttf -lSDL2_image -lSDL2_mixer \
           -Wl,-rpath,'$$ORIGIN/lib'

SRC := $(SRC_DIR)/main.c $(SRC_DIR)/core/ui/font.c \
	   $(SRC_DIR)/core/ui/widget.c $(SRC_DIR)/core/engine.c \
	   $(SRC_DIR)/core/render.c $(SRC_DIR)/core/scene.c \
	   $(SRC_DIR)/util/error.c $(SRC_DIR)/util/window.c

OBJ := $(patsubst $(SRC_DIR)/%.c,$(BUILD_DIR)/%.o,$(SRC))

TARGET := $(DIST_DIR)/game

CFLAGS := $(BASE_CFLAGS) -O2 -DNDEBUG

all: $(TARGET) copy_libs

$(TARGET): $(OBJ)
	mkdir -p $(DIST_DIR)
	$(CC) $(OBJ) -o $(TARGET) $(LDFLAGS)
	cp -r assets $(DIST_DIR)/

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c
	mkdir -p $(dir $@)
	$(CC) -c $< -o $@ $(CFLAGS)

debug:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(BASE_CFLAGS) -g" all

release:
	$(MAKE) clean
	$(MAKE) CFLAGS="$(BASE_CFLAGS) -O2 -DNDEBUG" all
	strip $(TARGET)

copy_libs:
	mkdir -p $(DIST_DIR)/lib
	ldd $(TARGET) | awk '{print $$3}' | grep -E '^/' | \
	grep -vE 'libc\.so|libm\.so|ld-linux' | sort -u | \
	while read lib; do \
		cp -n $$lib $(DIST_DIR)/lib/; \
	done

clean:
	rm -rf $(BUILD_DIR) $(DIST_DIR)

run: all
	cd $(DIST_DIR) && ./game
