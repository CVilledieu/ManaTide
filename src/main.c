#include <glad/glad.h>
#include <GLFW/glfw3.h>

int HEIGHT =640;
int WIDTH = 480;

GLFWwindow* create_window(){
    GLFWwindow* window;
    
        /* Initialize the library */
        if (!glfwInit())
            return NULL;
    
        /* Create a windowed mode window and its OpenGL context */
        window = glfwCreateWindow(HEIGHT, WIDTH, "Hello World", NULL, NULL);
        if (!window)
        {
            glfwTerminate();
            return NULL;
        }
    
        /* Make the window's context current */
        glfwMakeContextCurrent(window);
    
        return window;
}


int main(void)
{
    GLFWwindow* window;

    window = create_window();

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


