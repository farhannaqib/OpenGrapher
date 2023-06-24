#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Grapher {
    public:
        unsigned int width, height;
        const char* windowName = "OpenGrapher";

        Grapher(unsigned int width = 800, unsigned int height = 600);
        ~Grapher();

        // initializes GLFW3, GLAD, sets up the window
        // and the shader program
        bool init();

        void run();

    private:
        GLFWwindow* window;
        unsigned int shaderProgram;
        unsigned int VAO, VBO;
};