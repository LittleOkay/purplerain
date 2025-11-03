#ifndef MAIN_H
#define MAIN_H

#include <windows.h>
#include <stdio.h>
#include <stdlib.h>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include "rain.h"

//BACKGROUND 240, 240, 250 RGB LAVENDER
//RAIN 138, 43, 226 RBG Purple

#define MAX_RAIN 100
rainDrop rain[MAX_RAIN];
//extern splashEffect splashes[MAX_SPLASHES];

GLFWwindow* createWindow(void);
void drawScene(void);
void display(void);
void renderParticles(void);
void setOrthographicProjection(void);
void initRain(void);
void renderRain(void);
void updateRain(float);

#endif