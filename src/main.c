#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "depend/shaders/BasicShade.h"
#include <stdio.h>
#include <stdlib.h>


//Size of window
const int HEIGHT = 640;
const int WIDTH = 480;

//Function Prototypes
void windowResize_cb(GLFWwindow* window, int width, int height);
GLFWwindow* createNewWindow(char *title);
void windowInput(GLFWwindow *window);
float* getTriangle();
int shaderCompSuccess(unsigned int);
unsigned int createProgramShaderObj();

int main(void)
{
    GLFWwindow* window;
    window = createNewWindow("Mana Tide");
    if(window == NULL){
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, windowResize_cb);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
        return -1;
    }

    unsigned int shaderProgram;
    shaderProgram = createProgramShaderObj();
    if (!shaderProgram){
        printf("Shader Program Obj failed to be created");
        return -1;
    }
   //(x,y,z) cords for a triangle
    //range for each point/vertex is -1 to 1
    //standard xyz-plane
    //ex: (0,1) is up (0,-1) is down and (1,0) is right
    /*
    float triangleVertices[] = {
            -0.5f, -0.5f, 0.0f,
            0.5f, -0.5f, 0.0f,
            0.0f, 0.5f, 0.0f,
    };*/

    float vertices[] = {
         0.5f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f, 
        -0.5f, -0.5f, 0.0f, 
        -0.5f,  0.5f, 0.0f
    };

    //The order the vertices will be drawn
    unsigned int drawIndexes[] = { 
        0,1,3,
        1,2,3,
    };


    //Buffer Object id
    unsigned int VBO, VAO, EBO;
    //asigns ids for buffers
    //Parameters:
    //  Size
    //  Address to store Id(s)
    //address can be an array to store multiple ids
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);   
    glGenVertexArrays(1, &VAO);

    glBindVertexArray(VAO); 

    //copy data to buffer
    //Parameters: where data is copied to, sizeOfdata, data being copied, uses/type of use grahpics card will do
    //Uses/Types: 
    //  GL_STREAM_DRAW : the data is set only once and used by the GPU at most a few times.
    //  GL_STATIC_DRAW : the data is set only once and used many time
    //  GL_DYNAMIC_DRAW : the data is changed a lot and used many times.
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(drawIndexes), drawIndexes, GL_STATIC_DRAW);

    //Parameters: 
    //  index 
    //  num of components in each vertex
    //  data type
    //  if it should normalize the input data
    //  stride: byte offset between each vertex
    //  pointer to an offset for first vertex
    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);
    glBindVertexArray(0);
    //All shader and render calls after this will use the object created by createProgramShaderObj()
    //Called within render loop to draw object
    //glUseProgram(shaderProgram);
    //glBindVertexArray(VAO);
    //main event loop
    while (!glfwWindowShouldClose(window))
    {

        //input
        windowInput(window);

        //Render
        //-----
        //Clear screen by drawing all pixels black
        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        //glDrawArrays(GL_TRIANGLES, 0,3);
        glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT,0);


        /* Swap front and back buffers */
        glfwSwapBuffers(window);
        glfwPollEvents();
        } //end window loop

    glfwTerminate();
    return 0;
} //end main


GLFWwindow* createNewWindow(char *title){
    GLFWwindow* window;
    if (!glfwInit()) return NULL;

    //requirements to be able to run app
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //size/shape and titel of window
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


//check for errors when compiling shader
int shaderCompSuccess(unsigned int Shader){
    int success;
    char infoLog[512];
    glGetShaderiv(Shader, GL_COMPILE_STATUS, &success);
    if(success) {
        return 0;
    }
    glGetShaderInfoLog(Shader, 512, NULL, infoLog);
    printf("Error compiling shader\n");
    printf("%s\n",infoLog);
    return 1;
}

unsigned int createProgramShaderObj() {

    unsigned int vertexShader;
    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);
    
    //error check compile of Shader
    if (shaderCompSuccess(vertexShader)) {
        return 0;
    }
    
    unsigned int fragmentShader;
    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    if (shaderCompSuccess(fragmentShader)){
        return 0;
    }

    //
    unsigned int shaderProgram;
    shaderProgram = glCreateProgram();

    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    int success;
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
    if(!success) {
        char infoLog[512];
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        printf("%s\n",infoLog);
    }

    glUseProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    return shaderProgram;
}
