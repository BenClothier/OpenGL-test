#version 330 core
layout (location = 0) in vec3 aPos;   // the position variable has attribute position 0
layout (location = 1) in vec3 aColour; // the colour variable has attribute position 1
layout (location = 2) in vec2 aTexCoord; // the texture coordinate variable has attribute position 2
  
out vec3 colour; // output a colour to the fragment shader
out vec2 texCoord; // output a texture position to the fragment

uniform mat4 transform; // the world position of the centre of the shader

void main()
{
    gl_Position = transform * vec4(aPos, 1.0f);
    colour = aColour; // set colour to the input colour we got from the vertex data
    texCoord = aTexCoord; // set texCoord to the input texture coordinate we got from the vertex data
}