INCLUDES_PATHS = -I ./depend/glfw/include -I ./depend/glad/include
LIBRARIES = ./depend/glfw/lib-mingw-w64/libglfw3dll.a -lgdi32 -lopengl32
application: ./src/main.c
	gcc src/*.c -o build/ManaTide -D GLFW_DLL $(INCLUDES_PATHS) $(LIBRARIES)