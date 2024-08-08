// **************************************************
// TRIANGLE DEMO
//
// Draw a triangle using opengl 4.6 core profile
// **************************************************

#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/ext.hpp>

// INITIAL SETTINGS
static int width = 1200;
static int height = 800;

// GLOBAL VARIABLES
static GLFWwindow *window;

static GLuint demoShader;
static GLuint demoVertexArray;
static GLuint demoVertexBuffer;
static GLuint demoVertexCount;

// ROTATION OF TRIANGLE IN DEGREES
static float demoRotation = 0.0f;

int main()
{
    //
    // Create the rendering window and load opengl functions
    //
    glfwInit();
    window = glfwCreateWindow(width, height, "HELLO OPENGL", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    glewInit();

    //
    // Set some opengl settings
    // 
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glClearDepth(1.0f);

    //
    // Create a buffer containing the vertices of a triangle
    //
    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f,
         0.5f, -0.5f, 0.0f
    };

    glGenVertexArrays(1, &demoVertexArray);
    glBindVertexArray(demoVertexArray);

    glGenBuffers(1, &demoVertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, demoVertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    // Input attrribute 0 is bound to the vertex data in the buffer
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);

    //
    // Create a shader program
    //
    const char *vertexShaderSource = R"(
        #version 460 core
        // INPUTS
        layout(location = 0) in vec3 position;

        // UNIFORMS
        layout(location = 0) uniform mat4 model;
        layout(location = 1) uniform mat4 view;
        layout(location = 2) uniform mat4 projection;

        void main()
        {
            mat4 transform = projection * view * model;
            gl_Position = transform * vec4(position, 1.0);
        }
    )";

    const char *fragmentShaderSource = R"(
        #version 460 core
        out vec4 color;
        void main()
        {
            color = vec4(1.0, 0.0, 0.0, 1.0);
        }
    )";

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, nullptr);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, nullptr);
    glCompileShader(fragmentShader);

    demoShader = glCreateProgram();
    glAttachShader(demoShader, vertexShader);
    glAttachShader(demoShader, fragmentShader);
    glLinkProgram(demoShader);

    //
    // Main loop
    //

    auto projectionMatrix = glm::perspective(glm::radians(45.0f), (float)width / (float)height, 0.1f, 100.0f);
    auto viewMatrix = glm::lookAt(glm::vec3(0, 0, 2), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));

    while (!glfwWindowShouldClose(window))
    {
        demoRotation += 1.0f;
        auto modelMatrix = glm::rotate(glm::mat4(1.0f), glm::radians(demoRotation), glm::vec3(0, 0.0, 1.0));

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glUseProgram(demoShader);
        glUniformMatrix4fv(0, 1, GL_FALSE, glm::value_ptr(modelMatrix));
        glUniformMatrix4fv(1, 1, GL_FALSE, glm::value_ptr(viewMatrix));
        glUniformMatrix4fv(2, 1, GL_FALSE, glm::value_ptr(projectionMatrix));
     
        glBindVertexArray(demoVertexArray);
        glBindBuffer(GL_ARRAY_BUFFER, demoVertexBuffer);
        glDrawArrays(GL_TRIANGLES, 0, 3);

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}