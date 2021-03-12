

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void processInput(GLFWwindow *window);

// settings
const unsigned int SCR_WIDTH = 1280;
const unsigned int SCR_HEIGHT = 720;

GLFWwindow *initialise()
{
   // glfw: initialize and configure
   // ------------------------------
   glfwInit();
   glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
   glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
   glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

   // glfw window creation
   // --------------------
   GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
   if (window == NULL)
   {
      std::cout << "Failed to create GLFW window" << std::endl;
      glfwTerminate();
      _Exit(-1);
   }
   glfwMakeContextCurrent(window);
   glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

   // glad: load all OpenGL function pointers
   // ---------------------------------------
   if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
   {
      std::cout << "Failed to initialize GLAD" << std::endl;
      _Exit(-1);
   }
   return window;
}

const char *vertexShaderSource = "\n"
   "#version 330 core\n"
   "layout (location = 0) in vec3 aPos;\n"
   "layout (location = 1) in vec3 aColor;\n"
   "out vec3 ourColor;\n"
   "uniform mat4 model;\n"
   "uniform mat4 view;\n"
   "uniform mat4 projection;\n"
   "void main()\n"
   "{\n"
   "  gl_Position = projection * view * model * vec4(aPos, 1.0f);\n"
   "  ourColor = aColor;\n"
   "}\0";

const char *fragmentShaderSource = "\n"
   "#version 330 core\n"
   "out vec4 FragColor;\n"
   "in vec3 ourColor;\n"
   "void main()\n"
   "{\n"
   "  FragColor = vec4(ourColor, 1.0);\n"
   "}\n\0";

const char *geometryShaderSource = "";

static unsigned int CompileShader(unsigned int type,const char *typeShaderSource ){
   unsigned int shader = glCreateShader(type);
   glShaderSource(shader, 1, &typeShaderSource, NULL);
   glCompileShader(shader);

   // check for shader compile errors
   int success;
   char infoLog[512];
   glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
   if (!success)
   {
      glGetShaderInfoLog(shader, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::"<< type <<" COMPILATION_FAILED\n"
                << infoLog << std::endl;
   }
   return shader;
}

static unsigned int CreateShader(){
   int success;
   char infoLog[512];
   unsigned int shaderProgram = glCreateProgram();
   unsigned int vertexShader = CompileShader(GL_VERTEX_SHADER,vertexShaderSource);
   unsigned int fragmentShader = CompileShader(GL_FRAGMENT_SHADER,fragmentShaderSource);
   unsigned int geometryShader;
   if(geometryShaderSource != ""){
      geometryShader =  CompileShader(GL_GEOMETRY_SHADER,geometryShaderSource);
   }
   glAttachShader(shaderProgram, vertexShader);
   glAttachShader(shaderProgram, fragmentShader);
   if(geometryShaderSource != ""){
      glAttachShader(shaderProgram,geometryShader);
   }
   glLinkProgram(shaderProgram);

   // check for linking errors
   glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
   if (!success)
   {
      glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
      std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n"
                << infoLog << std::endl;
   }
   glDeleteShader(vertexShader);
   glDeleteShader(fragmentShader);
   if(geometryShaderSource!=""){
      glDeleteShader(geometryShader);
   }

   return shaderProgram;
}

int main()
{
   GLFWwindow *window = initialise();
   glEnable(GL_DEPTH_TEST);  
   unsigned int shaderProgram = CreateShader();

   // set up vertex data (and buffer(s)) and configure vertex attributes
   // ------------------------------------------------------------------
   float vertices[] = {
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 0.0f,0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 0.0f,0.0f,

      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 1.0f,0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 1.0f,0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,

      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      -0.5f, 0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,
      -0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,

      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,

      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      0.5f, -0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      0.5f, -0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      -0.5f, -0.5f, 0.5f, 0.0f, 0.0f,0.0f,
      -0.5f, -0.5f, -0.5f, 0.0f, 1.0f,0.0f,

      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f,
      0.5f, 0.5f, -0.5f, 1.0f, 1.0f,0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      0.5f, 0.5f, 0.5f, 1.0f, 0.0f,0.0f,
      -0.5f, 0.5f, 0.5f, 0.0f, 0.0f,0.0f,
      -0.5f, 0.5f, -0.5f, 0.0f, 1.0f,0.0f
   };

   unsigned int VBO, VAO;
   glGenVertexArrays(1, &VAO);
   glGenBuffers(1, &VBO);
   // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
   glBindVertexArray(VAO);

   glBindBuffer(GL_ARRAY_BUFFER, VBO);
   glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

   glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void *)0);
   glEnableVertexAttribArray(0);

   glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

   // note that this is allowed, the call to glVertexAttribPointer registered VBO as the vertex attribute's bound vertex buffer object so afterwards we can safely unbind
   // glBindBuffer(GL_ARRAY_BUFFER, 0);

   // You can unbind the VAO afterwards so other VAO calls won't accidentally modify this VAO, but this rarely happens. Modifying other
   // VAOs requires a call to glBindVertexArray anyways so we generally don't unbind VAOs (nor VBOs) when it's not directly necessary.
   // glBindVertexArray(0);

   // uncomment this call to draw in wireframe polygons.
   glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

   // render loop
   // -----------
   while (!glfwWindowShouldClose(window))
   {
      // input
      // -----
      processInput(window);

      // render
      // ------
      glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
      glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

      // draw our first triangle
      glUseProgram(shaderProgram);
      glm::mat4 model = glm::mat4(1.0f);
      glm::mat4 view = glm::mat4(1.0f);
      glm::mat4 projection = glm::mat4(1.0f);
      model = glm::rotate(model, (float)glfwGetTime(), glm::vec3(0.5f, 1.0f, 0.0f));
      view = glm::translate(view, glm::vec3(0.0f, 0.0f, -3.0f));
      projection = glm::perspective(glm::radians(45.0f), (float)SCR_WIDTH / (float)SCR_HEIGHT, 0.1f, 100.0f);
      unsigned int modelLoc = glGetUniformLocation(shaderProgram,"model");
      unsigned int viewLoc = glGetUniformLocation(shaderProgram, "view");
      glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(model));
      glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &view[0][0]);
      glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "projection"), 1, GL_FALSE, &projection[0][0]);
      
      glBindVertexArray(VAO); // seeing as we only have a single VAO there's no need to bind it every time, but we'll do so to keep things a bit more organized
      glDrawArrays(GL_TRIANGLES, 0, 36);
      // glBindVertexArray(0); // no need to unbind it every time

      // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
      // -------------------------------------------------------------------------------
      glfwSwapBuffers(window);
      glfwPollEvents();
   }

   // optional: de-allocate all resources once they've outlived their purpose:
   // ------------------------------------------------------------------------
   glDeleteVertexArrays(1, &VAO);
   glDeleteBuffers(1, &VBO);
   glDeleteProgram(shaderProgram);

   // glfw: terminate, clearing all previously allocated GLFW resources.
   // ------------------------------------------------------------------
   glfwTerminate();
   return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window)
{
   if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
      glfwSetWindowShouldClose(window, true);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height)
{
   // make sure the viewport matches the new window dimensions; note that width and
   // height will be significantly larger than specified on retina displays.
   glViewport(0, 0, width, height);
}
