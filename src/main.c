#include "main.h"

int main(){
   if(!glfwInit()){
      fprintf(stderr, "Failed to initialize GLFW\n");
      return -1;
   }
   GLFWwindow* window = createWindow();
   initRain();
   float lastTime = glfwGetTime();
   do{
      fflush(stdout);
      float currentTime = glfwGetTime();
      float deltaTime = currentTime - lastTime;
      lastTime = currentTime;
      drawScene();
      updateRain(deltaTime);
      renderParticles();
      glfwSwapBuffers(window);
      glfwPollEvents();
   }
   while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0);
   glfwTerminate();
   return 0;
}

GLFWwindow* createWindow(){
   glfwWindowHint(GLFW_SAMPLES, 4); 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); 
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); 
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_COMPAT_PROFILE); 
   GLFWwindow* window;
   window = glfwCreateWindow( 640 , 360 , "Purple Rain" , NULL , NULL); 
   if(window == NULL){
      fprintf(stderr,"FAILED to open GLFW window. IF you have an Intel GPU, they are not 3.3 comptaible. Try the 2.1 version of OpenGL.\n");
      glfwTerminate();
      return -1;
   }
   glfwMakeContextCurrent(window);
   glViewport(0,0,640,360);   //window resolution
   glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE); 
   return window;
}

void drawScene(){
   glClearColor(0.902f, 0.902f, 0.980f, 1.0f);  
   glClear(GL_COLOR_BUFFER_BIT);
}

void renderParticles(){
   setOrthographicProjection();
   for(int i = 0; i < MAX_RAIN; i++){
      drawRainDrop(&rain[i]);
   }
   drawSplashes();
}

void setOrthographicProjection(){
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity(); 
   glOrtho(0.0, 640.0, 365.0, -20.0, -1.0, 1.0);
   glMatrixMode(GL_MODELVIEW);   
   glLoadIdentity();
}

void initRain(){
   for (int i=0; i < MAX_RAIN; i++){
      float x = rand() % 640; 
      float y = -50 + (rand() % 360); 
      float length = 5 + (rand() % 10);
      float speed = 100 + (rand() % 150); 
     //float speed = 20;
      initRainDrop(&rain[i], x, y, length, speed, 0.541f, 0.169f, 0.886f);
   }
}

void updateRain(float deltaTime){
   for (int i = 0; i < MAX_RAIN; i++){
      updateRainDrop(&rain[i], deltaTime);
   }
   updateSplashes(deltaTime);
}

