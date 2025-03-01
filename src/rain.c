#include "rain.h"
#include <stdio.h>

void initRainDrop(rainDrop* drop, float x, float y, float length, float speed, float r, float g, float b){
    drop->x = x;
    drop->y = y;
    drop->length = length;
    drop->speed = speed;
    drop->r = r;
    drop->g = g;
    drop->b = b;
}

void drawRainDrop(rainDrop* drop) {
glColor3f(drop->r, drop->g, drop->b);        
glLineWidth(2.0f);               
glBegin(GL_LINES);
    glVertex2f(drop->x, drop->y);   
    glVertex2f(drop->x, drop->y + drop->length);   
glEnd();
}

void updateRainDrop(rainDrop* drop, float deltaTime){
    printf("Speed: %f, deltaTime: %f, Movement: %f\n", drop->speed, deltaTime, drop->speed * deltaTime);
    fflush(stdout);
    drop->y += drop->speed * deltaTime ; 
    if (drop->y > 360){
        drop->y = -drop->length;
        drop->x = rand() % 640; 
    }
}