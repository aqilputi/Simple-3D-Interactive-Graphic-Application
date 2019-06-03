#include "glad/glad.h"
#include <GLFW/glfw3.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>

//obj loader
#include "objLoader.h"

#include "fan.h"
#include "openglsys.h"
#include "transf2d.h"


int main (void){

  glfwInit ();
  GLFWwindow* window = initWindow();

  // compiling vertex shader
  unsigned int vertexShader = compVertexShader();
  // compiling fragment shader
  unsigned int fragmentShader = compFragmentShader();
  //create and config shader program
  unsigned int shaderProgram = initShaderProgram(vertexShader, fragmentShader);
  glDeleteShader (vertexShader);   //garbage 4 now
  glDeleteShader (fragmentShader); //garbage 4 now


  //loading obj
  objLoader *objData = new objLoader();
  objData->load("test.obj");

  /*
  float* vertices = (float*) malloc(sizeof(float)*objData->vertexCount*3); //3 para x y z
  for(int i=0; i<objData->vertexCount; i++){
    obj_vector *o = objData->vertexList[i];
    for(int j=0; j<3; j++){
      vertices[(i*3)+j] = o->e[j];
      //printf("%d ", vertices[(i*3)+j]);
      printf("%f ", o->e[j]);
    }
    printf("\n");
  }

  unsigned int* indices = (unsigned int*) malloc(sizeof(unsigned int)*objData->faceCount*3); //3 para triangulos
  printf("%d\n", objData->faceCount);
  for(int i=0; i<objData->faceCount; i++){
    obj_face *o = objData->faceList[i];
    for(int j=0; j<3; j++){
      indices[(i*3)+j] = (unsigned int) o->vertex_index[j];
      printf("%u ", indices[(i*3)+j]);
    }
    printf("\n");
  }
  */

  float vertices[] = {
    // axis
       0.0f,   0.0f,   0.0f, // P0
    // first triangle
     -0.25f,   0.5f,   0.0f, // P1
      0.25f,   0.5f,   0.0f, // P2
    // second triangle
       0.5f,  0.25f,   0.0f, // P3
       0.5f, -0.25f,   0.0f, // P4
    // third triangle
      0.25f,  -0.5f,   0.0f, // P5
     -0.25f,  -0.5f,   0.0f, // P6
    // fourth triangle
      -0.5f, -0.25f,   0.0f, // P7
      -0.5f,  0.25f,   0.0f, // P8
  };

  unsigned int indices[] = {  // note that we start from 0!
    0, 1, 2, // first triangle
    0, 3, 4, // second triangle
    0, 5, 6, // third triangle
    0, 7, 8, // fourth triangle
  }; 
  

  // configuring triangle to gpu
  unsigned int EBO;
  glGenBuffers (1, &EBO);  
  unsigned int VBO;
  glGenBuffers (1, &VBO);  
  unsigned int VAO;
  glGenVertexArrays (1, &VAO);  

  glBindVertexArray (VAO);
 
  glBindBuffer (GL_ARRAY_BUFFER, VBO);
  glBufferData (GL_ARRAY_BUFFER, sizeof(float)*objData->vertexCount*3, vertices, GL_STATIC_DRAW);
  
  glBindBuffer (GL_ELEMENT_ARRAY_BUFFER, EBO);
  glBufferData (GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int)*objData->faceCount*3, indices, GL_STATIC_DRAW);

  glVertexAttribPointer (0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
  glEnableVertexAttribArray (0);

  // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
  glBindBuffer (GL_ARRAY_BUFFER, 0); 

  // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
  // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
  glBindVertexArray (0); 


  // inicia uma matriz de translação 2D
  float T2D [] = {
    1, 0, 0, // tx = 0
    0, 1, 0, // ty = 0
    0, 0, 1,
  };

  // inicia uma matriz de rotação 2D, teta = 0º
  float R2D [] = {
    1,  0, 0, // cos 0 = 1, -sen 0 = 0
    0,  1, 0, // sen 0 = 0,  cos 0 = 1
    0,  0, 1
  };

  float vel = ((-0.25 * M_PI) / 180); // velocidade pre determinada de 0.25º no sentido horário

  //set callbacks in events
  glfwSetKeyCallback (window, key_callback);

  // loop
  while(!glfwWindowShouldClose (window)) {
    move (window, vertices, T2D);
    spin (window, vertices, T2D, R2D, &vel);

    // movimentacao da casa
    glBindBuffer (GL_ARRAY_BUFFER, VBO); //associa um buffer ao gpu
    glBufferData (GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW); //escreve buffer de vertices ao buffer VBO
    glBindBuffer (GL_ARRAY_BUFFER, 0); 

    //rendering commands
    glClearColor (0.2f, 0.3f, 0.3f, 1.0f);
    glClear (GL_COLOR_BUFFER_BIT);

    //draw
    glUseProgram (shaderProgram);
    glBindVertexArray (VAO);
    glDrawElements (GL_TRIANGLES, objData->faceCount*3, GL_UNSIGNED_INT, 0);
    
    //swap 
    glfwPollEvents ();    
    glfwSwapBuffers (window);
  }
  
  glfwTerminate ();
  return 0;
}
