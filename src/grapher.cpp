// #ifdef __APPLE__
// // Defined before OpenGL and GLUT includes to avoid deprecation messages
// #define GL_SILENCE_DEPRECATION
// #include <glad/glad.h>
// #include <GLFW/glfw3.h>
// #endif

// #include <iostream>
// #include <string>

// #include "tokenizer.h"
// #include "ast.h"
// #include "solver.h"
// #include "grapher.h"

// const size_t WIDTH = 800;
// const size_t HEIGHT = 600;
// const char* WINDOW_NAME = "Test Window";

// const char *vertexShaderSource = "#version 330 core\n"
//     "layout (location = 0) in vec3 aPos;\n"
//     "out vec4 vertexColor;\n"
//     "void main()\n"
//     "{\n"
//     "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
//     "   vertexColor = vec4(1.0, 0.0, 0.0, 1.0);\n"
//     "}\0";

// const char *fragmentShaderSource = "#version 330 core\n"
//     "out vec4 FragColor;\n"
//     "in vec4 vertexColor;\n"
//     "void main()\n"
//     "{\n"
//     "   FragColor = vertexColor;\n"
//     "}\0";

// void processInput(GLFWwindow *window) 
// {
//     if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
//         glfwSetWindowShouldClose(window, GLFW_TRUE);
// }

// void framebuffer_size_callback(GLFWwindow* window, int width, int height)
// {
//     glViewport(0, 0, width, height);
// }

// int main()
// {
//     if (!glfwInit()) {
//         std::cerr << "ERROR: can't start GLFW3" << std::endl;
//         return -1;
//     }

//     glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
//     glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
//     glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
// #ifdef __APPLE__
//     glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
// #endif

//     // create window and set context
//     GLFWwindow* window = glfwCreateWindow(WIDTH, HEIGHT, WINDOW_NAME, NULL, NULL);
//     if (!window) {
//         std::cerr << "ERROR: can't open window" << std::endl;
//         glfwTerminate();
//         return -1;
//     }
//     glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
//     glfwMakeContextCurrent(window);

//     if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
//         std::cerr << "ERROR: can't load GLAD" << std::endl;
//         return -1;
//     }

//     const GLubyte* renderer = glGetString(GL_RENDERER);
//     const GLubyte* version = glGetString(GL_VERSION);
//     std::cout << "Renderer: " << renderer << std::endl;
//     std::cout << "Version: " << version << std::endl;


//     // build shader program
//     unsigned int vertexShader;
//     vertexShader = glCreateShader(GL_VERTEX_SHADER);
//     glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
//     glCompileShader(vertexShader);

//     int success;
//     char infoLog[512];
//     glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }

//     unsigned int fragmentShader;
//     fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
//     glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
//     glCompileShader(fragmentShader);
//     glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
//     if (!success) {
//         glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
//         std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
//     }

//     unsigned int shaderProgram;
//     shaderProgram = glCreateProgram();
//     glAttachShader(shaderProgram, vertexShader);
//     glAttachShader(shaderProgram, fragmentShader);
//     glLinkProgram(shaderProgram);
//     glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
//     if (!success) {
//         glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
//         std::cout << "ERROR::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
//     }

//     glDeleteShader(vertexShader);
//     glDeleteShader(fragmentShader);


//     float vertices[] = {
//         -1.0f, 0.5f, 0.0f,
//         -0.5f, 0.0f, 0.0f,
//         0.0f, 0.0f, 0.0f,
//         0.5f, 0.5f, 0.0f,
//         1.0f, -0.5f, 0.0f
//     };

//     unsigned int VAO;
//     unsigned int VBO;
//     glGenBuffers(1, &VBO);
//     glGenVertexArrays(1, &VAO);
//     glBindVertexArray(VAO);

//     glBindBuffer(GL_ARRAY_BUFFER, VBO);
//     glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

//     glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
//     glEnableVertexAttribArray(0);
//     glBindBuffer(GL_ARRAY_BUFFER, 0);

//     glBindVertexArray(0);

//     //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

//     while (!glfwWindowShouldClose(window)) {
//         processInput(window);

//         glClearColor(0.0718f, 0.0718f, 0.0718f, 1.0f);
//         glClear(GL_COLOR_BUFFER_BIT);

//         glUseProgram(shaderProgram);
//         glBindVertexArray(VAO);
//         glDrawArrays(GL_LINE_STRIP, 0, 5);

//         glfwSwapBuffers(window);
//         glfwPollEvents();
//     }

//     glDeleteBuffers(1, &VBO);
//     glDeleteVertexArrays(1, &VAO);
//     glDeleteProgram(shaderProgram);
//     glfwTerminate();

//     return 0;
// }