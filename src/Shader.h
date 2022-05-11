
#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> // include glad to get all the required OpenGL headers
//#include <glm/glm.hpp>
//#include <glm/gtc/type_ptr.hpp>
#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

using namespace std;


class Shader
{
public:
    // the program ID
    unsigned int ID;

    // constructor reads and builds the shader
    Shader(const char*, const char*);
    // use/activate the shader
    void use();
    // utility uniform functions
    void setBool(const string&, bool) const;
    void setInt(const string&, int) const;
    void setFloat(const string&, float) const;
    //void setMat4(const std::string& name, glm::mat4 value) const;
    //void setVec3(const std::string& name, glm::vec3 value) const;
    //void setVec4(const std::string& name, glm::vec4 value) const;
};

#endif