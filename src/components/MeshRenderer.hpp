#pragma once

#include "../Core/Shader.hpp"
#include "../Meshes/TriangleMesh.hpp"

struct MeshRenderer
{
	TriangleMesh mesh;
	Shader shader;
	unsigned int VAO;
};