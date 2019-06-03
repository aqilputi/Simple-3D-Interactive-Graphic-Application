#ifndef _OPENGLSYS_H_
#define _OPENGLSYS_H_

#include "glad/glad.h"
#include <GLFW/glfw3.h>


//window
GLFWwindow* initWindow();
//framebuffersize callback
void framebuffer_size_callback (GLFWwindow* window, int width, int height);


//vertex shader
unsigned int compVertexShader();
//fragment shader
unsigned int compFragmentShader();
//shader program
unsigned int initShaderProgram(unsigned int vertexShader,
                                 unsigned int fragShader);

#endif
