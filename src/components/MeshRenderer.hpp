#pragma once

#include "../Core/Shader.hpp"
#include "../Meshes/TriangleMesh.hpp"

struct MeshRenderer
{
	Shader shader;
	float vertices[18] = {
        // positions         // colors
         0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
        -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
         0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 
    };
	unsigned int VBO, VAO;
	bool initialised = false;
};