#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>

#include "openglsys.h"

const char *vertexShaderSource = "#version 330 core\n"
    "layout (location = 0) in vec3 aPos;\n"
    "void main()\n"
    "{\n"
    "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
    "}\0";
const char *fragmentShaderSource = "#version 330 core\n"
    "out vec4 FragColor;\n"
    "void main()\n"
    "{\n"
    "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
    "}\n\0";
  
void framebuffer_size_callback (GLFWwindow* window, int width, int height) {
  glViewport (0, 0, width, height);
}

GLFWwindow* initWindow(){
  glfwWindowHint (GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint (GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint (GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  // glfwWindowHint (GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  GLFWwindow* window = glfwCreateWindow (800, 600, "Trabalho 1", NULL, NULL);
  if (window == NULL) {
    std::cout << "Failed to create GLFW window" << std::endl;
    glfwTerminate ();
    return NULL;
  }

  glfwMakeContextCurrent (window);

  if (!gladLoadGLLoader ((GLADloadproc) glfwGetProcAddress)) {
    std::cout << "Failed to initialize GLAD" << std::endl;
    return NULL;
  }    

  glViewport (0, 0, 800, 600);

  glfwSetFramebufferSizeCallback (window, framebuffer_size_callback);  

  return window;
}


unsigned int compVertexShader(){
  unsigned int vertexShader;
  vertexShader = glCreateShader (GL_VERTEX_SHADER);
  glShaderSource (vertexShader, 1, &vertexShaderSource, NULL);
  glCompileShader (vertexShader);
  
  //// check
  int  success;
  char infoLog [512];
  glGetShaderiv (vertexShader, GL_COMPILE_STATUS, &success);
  
  if(!success) {
    glGetShaderInfoLog (vertexShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
    return -1;
  }

  return vertexShader;
}

unsigned int compFragmentShader(){
  //// check
  int  success;
  char infoLog [512];
  // compiling fragment shader
  unsigned int fragmentShader;
  fragmentShader = glCreateShader (GL_FRAGMENT_SHADER);
  glShaderSource (fragmentShader, 1, &fragmentShaderSource, NULL);
  glCompileShader (fragmentShader);
  
  //// check
  glGetShaderiv (fragmentShader, GL_COMPILE_STATUS, &success);
  if (!success) {
    glGetShaderInfoLog (fragmentShader, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
    return -1;
  }

  return fragmentShader;
}

unsigned int initShaderProgram(unsigned int vertexShader,
                               unsigned int fragShader){
  int  success;
  char infoLog [512];
  unsigned int shaderProgram;
  shaderProgram = glCreateProgram ();
  glAttachShader (shaderProgram, vertexShader);
  glAttachShader (shaderProgram, fragShader);
  glLinkProgram (shaderProgram);


  glGetProgramiv (shaderProgram, GL_LINK_STATUS, &success);
  
  if(!success) {
    glGetProgramInfoLog (shaderProgram, 512, NULL, infoLog);
    std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
    return -1;
  }

  return shaderProgram;
}

