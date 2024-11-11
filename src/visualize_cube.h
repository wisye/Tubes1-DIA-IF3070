#include "cube.h"
#include <GL/glu.h>
#include <GL/glut.h>
#include <GLFW/glfw3.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#ifndef _VC_
#define _VC

bool isPartOfSequence(int x, int y, int z, Cube *cube);
void drawBlock(int value, float x, float y, float z, bool isGreen);
void drawCube(Cube *cube);
void display(Cube *cube);
void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);
void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
int visualize_cube(Cube *cube);

#endif