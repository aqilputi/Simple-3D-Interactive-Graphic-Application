#ifndef _FAN_H_

#define _FAN_H_


void framebuffer_size_callback (GLFWwindow* window, int width, int height);

void key_callback (GLFWwindow* window, int key, int scancode, int action, int mods);

float* transformacoes2D (float *M, float x, float y);

// ENCONTRAR MATRIZ DE TRANSFORMAÇÃO
float* matriz_transformacao2D (float *M1, float *M2);

void move (GLFWwindow *window, float *v, float *T2D);

void rotate (float *v, float *T2D, float *R2D, float *vel);

void spin (GLFWwindow *window, float *v, float *T2D, float *R2D, float *vel);


#endif 
