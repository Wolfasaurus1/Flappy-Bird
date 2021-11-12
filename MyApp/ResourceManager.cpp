#include "ResourceManager.h"

std::unordered_map<std::string, Shader> ResourceManager::Shaders;

Shader ResourceManager::LoadShader(const char *vertexShaderFile, const char *fragmentShaderFile, std::string name)
{
	Shaders[name] = loadShaderFromFile(vertexShaderFile, fragmentShaderFile);
	return Shaders[name];
}


Shader ResourceManager::GetShader(std::string name)
{
	return Shaders[name];
}


Shader ResourceManager::loadShaderFromFile(const char *vShaderFile, const char *fShaderFile)
{
	// 1. retrieve the vertex/fragment source code from filePath
	std::string vertexCode;
	std::string fragmentCode;
	std::string geometryCode;
	try
	{
		// open files
		std::ifstream vertexShaderFile(vShaderFile);
		std::ifstream fragmentShaderFile(fShaderFile);
		std::stringstream vShaderStream, fShaderStream;
		// read file's buffer contents into streams
		vShaderStream << vertexShaderFile.rdbuf();
		fShaderStream << fragmentShaderFile.rdbuf();
		// close file handlers
		vertexShaderFile.close();
		fragmentShaderFile.close();
		// convert stream into string
		vertexCode = vShaderStream.str();
		fragmentCode = fShaderStream.str();
	}
	catch (std::exception e)
	{
		std::cout << "ERROR::SHADER: Failed to read shader files" << std::endl;
	}
	const char *vShaderCode = vertexCode.c_str();
	const char *fShaderCode = fragmentCode.c_str();
	const char *gShaderCode = geometryCode.c_str();
	// 2. now create shader object from source code
	Shader shader;
	shader.compile(vShaderCode, fShaderCode);
	return shader;
}