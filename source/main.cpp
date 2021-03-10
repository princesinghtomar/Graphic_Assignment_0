#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <iostream>
#include <GL/glut.h>
#include <stdio.h>

namespace {
   void errorCallback(int error, const char* description) {
      fprintf(stderr, "GLFW error %d: %s\n", error, description);
   }

   GLFWwindow* initialize() {
      int glfwInitRes = glfwInit();
      if (!glfwInitRes) {
         fprintf(stderr, "Unable to initialize GLFW\n");
         return nullptr;
      }

      glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
      glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 2);
      glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
      glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

      GLFWwindow* window = glfwCreateWindow(1280, 720, "InitGL", nullptr, nullptr);
      if (!window) {
         fprintf(stderr, "Unable to create GLFW window\n");
         glfwTerminate();
         return nullptr;
      }

      glfwMakeContextCurrent(window);

      int gladInitRes = gladLoadGL();
      if (!gladInitRes) {
         fprintf(stderr, "Unable to initialize glad\n");
         glfwDestroyWindow(window);
         glfwTerminate();
         return nullptr;
      }

      return window;
   }
}

static int 

int main(int argc, char* argv[]) {
   glfwSetErrorCallback(errorCallback);

   GLFWwindow* window = initialize();
   if (!window) {
      return 0;
   }

   // Set the clear color to a nice green
   glClearColor(252.0/255.0f, 119.0/255.0f, 3.0/255.0f, 1.0f);

   float positions[6] = {
      -0.5f,-0.5f,
       0.0f, 0.5f,
       0.5f,-0.5f 
   };

   unsigned int buffer;
   glGenBuffers(1,&buffer);
   glBindBuffer(GL_ARRAY_BUFFER,buffer);
   glBufferData(GL_ARRAY_BUFFER,6*sizeof(float), positions, GL_STATIC_DRAW);

   glEnableVertexAttribArray(0);
   glVertexAttribPointer(0,2,GL_FLOAT,GL_FALSE,sizeof(float)*2,0);

   while (!glfwWindowShouldClose(window)) {
      glClear(GL_COLOR_BUFFER_BIT);
      
      glDrawArrays(GL_TRIANGLES, 0, 3);
      // glDrawElements(GL_TRIANGLES, 3,)

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}