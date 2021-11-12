#pragma once

#include <iostream>
#include <glad\glad.h>

#include "Shader.h"
#include "Window.h"
#include "EventQueue.h"


class App
{
public:

	App();
	void OnKeyEvent(int key, int action);
	void OnMouseButtonEvent(int button, int action);
	void Run();

	virtual void Init() = 0;
	virtual void ProcessInput() = 0;
	virtual void Update(float dt) = 0;
	virtual void Render() = 0;

protected:

	GLFWwindow* window;
	EventQueue <KeyPressEvent> KeyEventQueue;
	EventQueue <MouseClickEvent> MouseClickEventQueue;
	int screenWidth = 2000.0f, screenHeight = 1200.0f;
	float mouseX, mouseY;
};
