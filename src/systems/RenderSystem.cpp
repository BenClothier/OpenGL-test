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
void applyRotation(glm::vec3 rotation, glm::mat4& transform);

const unsigned int SCR_WIDTH = 800;
const unsigned int SCR_HEIGHT = 600;

void RenderSystem::Init(View& view)
{
    RenderSystem::view = view;
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
                glGenBuffers(1, &renderer.EBO);

                glBindVertexArray(renderer.VAO);

                glBindBuffer(GL_ARRAY_BUFFER, renderer.VBO);
                glBufferData(GL_ARRAY_BUFFER, sizeof(renderer.vertices), renderer.vertices, GL_STATIC_DRAW);

                glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, renderer.EBO);
                glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(renderer.indices), renderer.indices, GL_STATIC_DRAW);

                // position attribute
                glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
                glEnableVertexAttribArray(0);

                // color attribute
                glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
                glEnableVertexAttribArray(1);

                // texture attribute
                glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
                glEnableVertexAttribArray(2);  

                renderer.initialised = true;
            }

            // bind texture
            glBindTexture(GL_TEXTURE_2D, renderer.texture.texture);

            // activate shader
            renderer.shader.use();

            // create transformations
            glm::mat4 modelMat = glm::translate(glm::mat4(1.0f), transform.position);
            applyRotation(transform.rotation, modelMat);
            modelMat = glm::scale(modelMat, transform.scale);
            
            glm::mat4 viewMat = glm::perspective(glm::radians(view.fov), (float)SCR_WIDTH / (float)SCR_HEIGHT, view.nearClip, view.farClip);
            applyRotation(view.transform.rotation, viewMat);
            viewMat *= glm::translate(glm::mat4(1.0f), -view.transform.position);

            renderer.shader.setMat4("model", modelMat);
            renderer.shader.setMat4("view", viewMat);

            glBindVertexArray(renderer.VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
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
        glDeleteBuffers(1, &renderer.EBO);
    }

    glfwTerminate();
}

void applyRotation(glm::vec3 rotation, glm::mat4& transform)
{
    transform = glm::rotate(transform, glm::radians(rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
    transform = glm::rotate(transform, glm::radians(rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
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