#include "RenderSystem.hpp"
#include "Components/MeshRenderer.hpp"
#include "Components/Transform.hpp"
#include "Core/Coordinator.hpp"

extern Coordinator gCoordinator;

void RenderSystem::Init()
{
	for (auto const& entity : entities)
	{
		auto& renderer = gCoordinator.GetComponent<MeshRenderer>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

        InitialiseMeshRender(transform, renderer);
	}
}

void RenderSystem::Update(float dt)
{
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
        
	for (auto const& entity : entities)
	{
		auto& renderer = gCoordinator.GetComponent<MeshRenderer>(entity);
		auto& transform = gCoordinator.GetComponent<Transform>(entity);

        RenderMesh(transform, renderer);
	}
}

void InitialiseMeshRender(Transform transform, MeshRenderer renderer)
{
    unsigned int VBO;
    glGenVertexArrays(1, &renderer.VAO);
    glGenBuffers(1, &VBO);

    // bind the Vertex Array Object first, then bind and set vertex buffer(s), and then configure vertex attributes(s).
    glBindVertexArray(renderer.VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(renderer.mesh.vertices), renderer.mesh.vertices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
}

void RenderMesh(Transform transform, MeshRenderer renderer)
{
    int vertexOffsetLocation = glGetUniformLocation(renderer.shader.ID, "offset");
    renderer.shader.use();
    glUniform3f(vertexOffsetLocation, transform.position.x, transform.position.y, transform.position.z);

    glBindVertexArray(renderer.VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
}