#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <math.h>
#include <time.h>

#include "transf2d.h"

int pause = 0;


// TRANSFORMAÇÕES DE TRANSLAÇÃO E ROTAÇÃO EM UM PONTO
float* transformacoes2D (float *M, float x, float y) {
  float v[3] = {x, y, 1};
  float *vt = (float *) malloc (sizeof (float) * 3);
  int i, j;

  for (i = 0; i < 3; i++){
    vt[i] = 0;
    for (j = 0; j < 3; j++){
      vt[i] += M[i * 3 + j] * v[j];
    }
  }

  return vt;
}

// ENCONTRAR MATRIZ DE TRANSFORMAÇÃO
float* matriz_transformacao2D (float *M1, float *M2) {
  float *M = (float *) malloc (sizeof (float) * 9);
  float sum = 0;
  int i, j, k;

  for (i = 0; i < 3; i++) {
    for (j = 0; j < 3; j++) {
      for (k = 0; k < 3; k++) {
        sum += M1[i * 3 + k] * M2[k * 3 + j];
      }
      M[i * 3 + j] = sum;
      sum = 0;
    }
  }

  return M;
}

void move (GLFWwindow *window, float *v, float *T2D) {
  float *p; // ponto de transformação
  int i;

  if (glfwGetKey (window, GLFW_KEY_W) == GLFW_PRESS) { // top
    T2D[5] = 0.005; // ty = 0.005

    for (i = 0; i < 10; i++) {
      p = transformacoes2D (T2D, v[i * 3], v[i * 3 + 1]);
      v[i * 3] = p[0];
      v[i * 3 + 1] = p[1];
    }

    T2D[5] = 0; // ty = 0
  } else if (glfwGetKey (window, GLFW_KEY_A) == GLFW_PRESS) { // left
    T2D[2] = -0.005; // tx = -0.005

    for (i = 0; i < 10; i++) {
        p = transformacoes2D (T2D, v[i * 3], v[i * 3 + 1]);
        v[i * 3] = p[0];
        v[i * 3 + 1] = p[1];
      }

    T2D[2] = 0;
  } else if (glfwGetKey (window, GLFW_KEY_S) == GLFW_PRESS) { // buttom 
    T2D[5] = -0.005; // ty = -0.005

    for (i = 0; i < 10; i++) {
        p = transformacoes2D (T2D, v[i * 3], v[i * 3 + 1]);
        v[i * 3] = p[0];
        v[i * 3 + 1] = p[1];
      }

    T2D[5] = 0; // ty = 0
  } else if (glfwGetKey (window, GLFW_KEY_D) == GLFW_PRESS) { // right
    T2D[2] = 0.005; // tx = 0.005

    for (i = 0; i < 10; i++) {
        p = transformacoes2D (T2D, v[i * 3], v[i * 3 + 1]);
        v[i * 3] = p[0];
        v[i * 3 + 1] = p[1];
      }

    T2D[2] = 0;
  }
}

void rotate (float *v, float *T2D, float *R2D, float *vel) {
  float *M, *p; // matriz e ponto de transformação
  int i;

  // Rotação horária de 1º
  R2D[0] = cos (*vel);
  R2D[1] = -sin (*vel);
  R2D[3] = -R2D[1];
  R2D[4] = R2D[0];

  // Movo eixo de rotação para origem
  T2D[2] = v[0]; 
  T2D[5] = v[1];

  M = matriz_transformacao2D (T2D, R2D); // executo a rotação
  
  T2D[2] = -v[0]; 
  T2D[5] = -v[1];
  
  M = matriz_transformacao2D (M, T2D); // movo o ponto de rotação para a posição original

  for (i = 0; i < 10; i++) {
      p = transformacoes2D (M, v[i * 3], v[i * 3 + 1]);
      v[i * 3] = p[0];
      v[i * 3 + 1] = p[1];
  }
  
  T2D[2] = 0;
  T2D[5] = 0;
}

void spin (GLFWwindow *window, float *v, float *T2D, float *R2D, float *vel) {
  if (pause == 0) {
    rotate (v, T2D, R2D, vel);
  }
  
  if (glfwGetKey (window, GLFW_KEY_E) == GLFW_PRESS) { // increase speed
    *vel += ((-0.25 * M_PI) / 180);
  } else if (glfwGetKey (window, GLFW_KEY_Q) == GLFW_PRESS) { // decrease speed
    *vel -= ((-0.25 * M_PI) / 180);
  }
}

void sleepcp(int milliseconds) { // Cross-platform sleep function
    clock_t time_end;
    time_end = clock () + milliseconds * CLOCKS_PER_SEC / 1000;
    while (clock () < time_end) {}
}

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods) {
  if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
  printf("GLFW - %d, pressing - %d\n", GLFW_KEY_E, key);
	if(pause == 1)
	  pause--;
	else
	  pause ++;
  } else if (glfwGetKey (window, GLFW_KEY_ESCAPE) == GLFW_PRESS) {
      glfwSetWindowShouldClose (window, true);
  }
}
