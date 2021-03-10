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

static  unsigned int CompileShader( unsigned int type, const std::string& source){
   unsigned int id = glCreateShader(type);
   const char* src = source.c_str();         // this does not return the array instead returns pointer
   glShaderSource(id,1,&src,nullptr);
   glCompileShader(id);

   int result;
   glGetShaderiv(id,GL_COMPILE_STATUS,&result);
   if(result == GL_FALSE){
      int length;
      glGetShaderiv(id, GL_INFO_LOG_LENGTH,&length);
      char* message = (char*)alloca(length * sizeof(char));
      glGetShaderInfoLog(id,length,&length,message);
      std::cout<< " Failed to compile " << (type==GL_VERTEX_SHADER ? "vertex" : "fragment" ) << " Shader! "<< std::endl;
      std::cout<< message << std::endl;
      glDeleteShader(id);
      return 0;
   }

   return id;
}

static unsigned  int CreateShader(const std::string& vertexShader, const std::string& fragmentShader){
   unsigned int program = glCreateProgram();
   unsigned int vs = CompileShader(GL_VERTEX_SHADER,vertexShader);
   unsigned int fs = CompileShader(GL_FRAGMENT_SHADER,fragmentShader);

   glAttachShader(program,vs);
   glAttachShader(program,fs);
   glLinkProgram(program);
   glValidateProgram(program);

   glDetachShader(program,vs);
   glDetachShader(program,fs);
   // glDeleteShader(vs);
   // glDeleteShader(fs);

   return program;

}

int main(int argc, char* argv[]) {
   glfwSetErrorCallback(errorCallback);

   GLFWwindow* window = initialize();
   if (!window) {
      return 0;
   }

   // Set the clear color to a nice green
   // glClearColor(252.0/255.0f, 119.0/255.0f, 3.0/255.0f, 1.0f);

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

   std::string vertexShader =
      "#version 450 core\n"
      "\n"
      "layout(location = 0) in vec4 position;\n"
      "\n"
      "void main()\n"
      "{\n"
      "  gl_Position = position;\n"
      "}\n";
   std::string fragmentShader =
      "#version 450 core\n"
      "\n"
      "layout(location = 0) out vec4 color;\n"
      "\n"
      "void main()\n"
      "{\n"
      "  color = vec4(1.0,0.0,0.0,1.0);\n"
      "}\n";
   unsigned int shader = CreateShader(vertexShader, fragmentShader);
   glUseProgram(shader);

   while (!glfwWindowShouldClose(window)) {
      // glClear(GL_COLOR_BUFFER_BIT);

      glDrawArrays(GL_TRIANGLES, 0, 3);
      // glDrawElements(GL_TRIANGLES, 3,)

      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   glDeleteProgram(shader);
   // glfwDestroyWindow(window);
   glfwTerminate();

   return 0;
}