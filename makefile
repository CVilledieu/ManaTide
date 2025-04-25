CC = gcc

INC_DIR = ./include ./src/depend/shaders/
LIB_DIR = ./lib
OUT_DIR = ./build
DEP_DIR = ./src/depend
OBJ_DIR = $(OUT_DIR)/obj
LIBS = -lopengl32 -lglfw3

_DEP = $(DEP_DIR)/glad.c
SRC = src/main.c
_OBJ = shaders.o glad.o main.o
OBJ = $(patsubst %,$(OBJ_DIR)/%,$(_OBJ))



CFLAGS = $(addprefix -I,$(INC_DIR)) -Wall -D GLFW_DLL

all: cleanExe app clean

$(OBJ_DIR)/shaders.o: $(DEP_DIR)/shaders/BasicShade.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Rule to compile glad.c into glad.o
$(OBJ_DIR)/glad.o: $(DEP_DIR)/glad.c
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

# Rule to compile main.c into main.o
$(OBJ_DIR)/main.o: $(SRC)
	@mkdir -p $(OBJ_DIR)
	$(CC) -c $< -o $@ $(CFLAGS)

app: $(OBJ)
	$(CC) -o $(OUT_DIR)/$@ $^ $(CFLAGS) $(LIBS)

.PHONY: clean

clean:
	rm -rf $(OBJ_DIR) 

cleanExe:
	rm -rf $(OUT_DIR)/app.exe
	@echo "Removed previous exe"