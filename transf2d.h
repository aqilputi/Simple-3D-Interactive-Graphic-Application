#ifndef _TRANSF_H_
#define _TRANSF_H_

#include <GLFW/glfw3.h>

float* transformacoes2D (float *M, float x, float y);
float* matriz_transformacao2D (float *M1, float *M2);


void move (GLFWwindow *window, float *v, float *T2D);
void rotate (float *v, float *T2D, float *R2D, float *vel);
void spin (GLFWwindow *window, float *v, float *T2D, float *R2D, float *vel);

void sleepcp(int milliseconds);


//callback para pause and close
void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

#endif
