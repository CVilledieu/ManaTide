#include <glad/glad.h>
#include <GLFW/glfw3.h>

int HEIGHT =640;
int WIDTH = 480;



int main(void)
{
    GLFWwindow* window;
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwInit()) {return -1;}
    window = glfwCreateWindow(HEIGHT, WIDTH, "Mana Tide",NULL, NULL);

    if(!window){
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

