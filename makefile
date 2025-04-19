CC = gcc

PROJECT := ManaTide

INCLUDES := -I ./include
CFLAGS := -Wall -D GLFW_DLL $(INCLUDES)

LIB_DIR := ./lib
LIBRARIES := $(LIB_DIR) $(patsubst $(LIB_DIR)/lib%.a,-l%,$(wildcard $(LIB_DIR)/*.a)) -lopengl32
LDFLAGS := -L$(LIBRARIES)

SRC_DIR := src/
SRC = $(SRC_DIR)main.c

DEPEND_DIR = depend/

PROJECT_DIR = $(SRC_DIR) $(DEPEND_DIR)

SRC_FILES = $(shell find $(PROJECT_DIR) -type f -name "\*.c")
OBJ_FILES := $(patsubst %.c,%.o,$(SRC_FILES))
DEP_FILES := $(patsubst %.c,%.d,$(SRC_FILES))

OUTPUT_DIR = build/
MAIN = -o $(OUTPUT_DIR)app

.PHONY: all clean

all: $(PROJECT)

clean:
	-@$(RM) $(wildcard $(OBJ_FILES) $(DEP_FILES) $(PROJECT))


-include $(DEP_FILES)

$(PROJECT): $(OBJ_FILES)
	@$(CC) $(LDFLAGS) $^

%.o: %.c Makefile
	@$(CC) $(CFLAGS) -MMD -MP -c $< -o $@

#APP: ./src/main.c ./depend/glad.c
#	$(CC) $(SRC) $(MAIN) $(CFLAGS) $(LDFLAGS)



