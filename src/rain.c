#include "rain.h"
#include <stdio.h>

splashEffect splashes[MAX_SPLASHES] = {0};

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
        createSplash(drop->x, 365);
        drop->y = -drop->length;
        drop->x = rand() % 640; 
    }
}

void createSplash(float x, float y){
    for (int i = 0; i < MAX_SPLASHES; i++){
        if (splashes[i].timeLeft <= 0){
            splashes[i].x = x;
            splashes[i].y = y;
            splashes[i].length = 5 + (rand() % 10);
            splashes[i].timeLeft = 0.6f;                //splash lifetime
            printf("Splash created at (%.2f, %.2f) with length %.2f\n", x, y, splashes[i].length);

            //splash effect particles
            for (int j = 0; j < SPLASH_PARTS; j++){
                float angle = (float)j / (float)SPLASH_PARTS * 3.14159f;    // distribute angles evenly
                float speed = 50.0f + (rand() % 50);                        // random speed for each part
                splashes[i].vx[j] = speed * cosf(angle);
                splashes[i].vy[j] = -sinf(angle) * speed * 0.5f;            // make more sideways
            }
            return;
        }
    }
}

void updateSplashes(float deltaTime){
    for (int i = 0; i < MAX_SPLASHES; i++){
        if (splashes[i].timeLeft > 0){
            splashes[i].timeLeft -= deltaTime * 2.0f;  // fade out over time
            if(splashes[i].timeLeft <= 0){
                splashes[i].timeLeft = 0;
            }
            // Move particles
            for (int j = 0; j < SPLASH_PARTS; j++){
                splashes[i].vx[j] *= 0.98f; // apply friction
                splashes[i].vy[j] += 9.81f * deltaTime; // apply gravity
            }
        }
    }
}

void drawSplashes() {
    glEnable(GL_LINE_SMOOTH);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(2.0f);

    glBegin(GL_LINES);
    for (int i = 0; i < MAX_SPLASHES; i++) {
        if (splashes[i].timeLeft > 0) {
            float t = 1.0f - splashes[i].timeLeft;
            float fade = splashes[i].timeLeft;
            float x = splashes[i].x;
            float y = splashes[i].y;
            float length = splashes[i].length;
            float spread = length * (0.3f + ((rand() % 30) / 100.0f)); // controls horizontal spread
            float height = length * 0.6f; // controls vertical height

            // Color with alpha fade
            glColor4f(0.4f, 0.2f, 1.0f, fade);

            // Left angled splash
            glVertex2f(x, y);
            glVertex2f(x - spread, y - height);

            // Right angled splash
            glVertex2f(x, y);
            glVertex2f(x + spread, y - height);
        }
    }
    glEnd();
}
