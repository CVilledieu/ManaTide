#include <glad/glad.h>
#include <GLFW/glfw3.h>


//Size of window
const int HEIGHT = 640;
const int WIDTH = 480;

//Function Prototypes
void windowResize_cb(GLFWwindow* window, int width, int height);
GLFWwindow* createNewWindow(char *title);
void windowInput(GLFWwindow *window);

int main(void)
{
    GLFWwindow* window;
    window = createNewWindow("Mana Tide");
    if(window == NULL){
        return -1;
    }
    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResize_cb);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    
    

    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        windowInput(window);
        glClear(GL_COLOR_BUFFER_BIT);

        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}

GLFWwindow* createNewWindow(char *title){
    GLFWwindow* window;
    /* Create a windowed mode window and its OpenGL context */
    if (!glfwInit()) return NULL;

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    window = glfwCreateWindow(HEIGHT, WIDTH, title,NULL, NULL);

    if(!window){
        glfwTerminate();
        return NULL;
    }
    return window;
}

//framebuffer_size_callback 
//Call back function for when window is resized
//Should rerender both front and back buffers by updating glViewport
void windowResize_cb(GLFWwindow* window, int width, int height){
    //First 2 augs are screen pos
    //Last 2 are size in pixels 
    glViewport(0,0, width, height);
}

void windowInput(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_ESCAPE)==GLFW_PRESS){
        glfwSetWindowShouldClose(window, 1);
    }
        
}