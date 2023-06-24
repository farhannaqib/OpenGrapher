int TEMPNAME();

#ifdef __APPLE__
// Defined before OpenGL and GLUT includes to avoid deprecation messages
#define GL_SILENCE_DEPRECATION
#endif
#include <glad/glad.h>
#include <GLFW/glfw3.h>

class Grapher {
    public:
        unsigned int width, height;
        const std::string windowName = "OpenGrapher";

        Grapher(int width = 800, int height = 600);
        ~Grapher();

        bool init();

};