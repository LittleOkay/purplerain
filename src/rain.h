#ifndef RAIN_H
#define RAIN_H

#include <GL/glut.h>

typedef struct{
    float x, y;         //postion
    float length;         //point size
    float speed;        //speed of raindrop
    float r, g, b;      //RGB colour
} rainDrop;

void initRainDrop(rainDrop* drop, float x, float y, float length, float speed, float r, float g, float b);
void drawRainDrop(rainDrop* drop);
void updateRainDrop(rainDrop* drop, float deltaTime);

#endif RAIN_H