#pragma once

#include <string>
#include <unordered_map>

#include "Shader.h"

class ResourceManager
{
public:
	static std::unordered_map<std::string, Shader> Shaders;

	static Shader LoadShader(const char *vertexShaderFile, const char *fragmentShaderFile, std::string name);
	static Shader GetShader(std::string name);

private:
	ResourceManager() {} //we don't want to instantiate objects of this class. it's a singleton
	static Shader loadShaderFromFile(const char *vShaderFile, const char *fShaderFile);
};


