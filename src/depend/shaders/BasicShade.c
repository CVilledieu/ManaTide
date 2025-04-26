#include <projHeaders/BasicShade.h>
// version number x.xx = xxx ex: 330 = v 3.3
//Vec datatype contains 1-4 floats. number after vec refers to how many we want. 


//vec3 is asking for first 3 floats.
//vec.x, vec.y, vec.z, vec.w
//vec.w describes perspective division
//output(gl_Pos) must be vec4
//vec.w is set to 1.0, so

const char *oldVertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n" 
"{\n"
    "gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0); \n"
"}\0";

//FragColor uses the 4 vectors to describe color. 
//RGBA are the 4 different vectors
//float values are between 0.0 and 1.0
//describing how much of those colors will be added.
//final arg is transparency. 1 being solid and 0 being completely transparent.  
const char *fragmentShaderSource = "#version 330 core \n"
"out vec4 FragColor; \n"
"in vec4 vertexColor;\n"
"void main() \n"
"{\n"
    "FragColor = vertexColor; \n"
"}\n";


const char *vertexShaderSource = "#version 330\n"
"layout (location = 0) in vec3 aPos; \n"
"out vec4 vertexColor;\n"
"void main()\n"
"{\n"
    "gl_Position = vec4(aPos, 1.0);\n"
    "vertexColor = vec4(0.5,0.0,0.0,1.0);\n"
"}\n";