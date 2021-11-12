#pragma once

#include <GLFW\glfw3.h>

class Window
{
public: 

	Window(int width, int height, char* name) : width_(width), height_(height), windowName_(name) 
	{
		glfwInit();

		glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
		glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);
		glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

		window = glfwCreateWindow(width, height, name, NULL, NULL);
	}

	GLFWwindow* GetWindow()
	{
		return this->window;
	}

private:

	GLFWwindow* window;
	int width_, height_;
	char* windowName_;
};

