#ifndef RAIN_H
#define RAIN_H

#include <GL/glut.h>
#include <math.h>

#define MAX_SPLASHES 100
#define SPLASH_PARTS 12      // number of lines per splash (used for roudness of splash)
typedef struct{
    float x, y;         //postion
    float length;       //point size
    float speed;        //speed of raindrop
    float r, g, b;      //RGB colour
} rainDrop;


typedef struct{
    float x, y;                 //position
    float vx[SPLASH_PARTS];     //velocity x components
    float vy[SPLASH_PARTS];     //velocity y components
    float length;               //length of splash lines
    float timeLeft;             //lifetime of splash
} splashEffect;

extern splashEffect splashes[MAX_SPLASHES];

void initRainDrop(rainDrop* drop, float x, float y, float length, float speed, float r, float g, float b);
void drawRainDrop(rainDrop* drop);
void updateRainDrop(rainDrop* drop, float deltaTime);

void createSplash(float x, float y);
void updateSplashes(float deltaTime);
void drawSplashes();

#endif // RAIN_H