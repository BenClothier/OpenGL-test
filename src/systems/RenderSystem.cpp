#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <iostream>

#include "RenderSystem.hpp"
#include "../components/MeshRenderer.hpp"
#include "../components/Transform.hpp"
#include "../core/Coordinator.hpp"

extern Coordinator coordinator;

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow *window);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void RenderSystem::Init()
{
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    // glfw window creation
    // --------------------
    window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return;
    }
}

void RenderSystem::Update(float dt)
{
    if (!glfwWindowShouldClose(window))
    {
        processInput(window);

        glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        for (auto const& entity : entities)
        {
            MeshRenderer &renderer = coordinator.GetComponent<MeshRenderer>(entity);
            Transform &transform = coordinator.GetComponent<Transform>(entity);

            if (!renderer.initialised)
            {
                glGenVertexArrays(1, &renderer.VAO);
                glGenBuffers(1, &renderer.VBO);

                glBindVertexArray(renderer.VAO);

                glBindBuffer(GL_ARRAY_BUFFER, renderer.VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(renderer.vertices), renderer.vertices, GL_STATIC_DRAW);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                // color attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                renderer.initialised = true;
            }

            // translate/rotate/scale shape based on the entity's transform
            glm::mat4 trans = glm::mat4(1.0f);
            trans = glm::translate(trans, transform.position);
            trans = glm::rotate(trans, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            trans = glm::rotate(trans, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            trans = glm::rotate(trans, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            trans = glm::scale(trans, transform.scale);
            unsigned int transformLoc = glGetUniformLocation(renderer.shader.ID, "transform");
            glUniformMatrix4fv(transformLoc, 1, GL_FALSE, glm::value_ptr(trans));

            renderer.shader.use();
            glBindVertexArray(renderer.VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);
        }

        glfwSwapBuffers(window);
        glfwPollEvents();
    }
}

void RenderSystem::Finish()
{
    for (auto const& entity : entities)
    {
        MeshRenderer &renderer = coordinator.GetComponent<MeshRenderer>(entity);
        glDeleteVertexArrays(1, &renderer.VAO);
        glDeleteBuffers(1, &renderer.VBO);
    }

    glfwTerminate();
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
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    // make sure the viewport matches the new window dimensions; note that width and 
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}