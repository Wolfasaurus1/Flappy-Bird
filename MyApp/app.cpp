#include "App.h"


App::App()
{
	Window window(screenWidth, screenHeight, "First App!");
	this->window = window.GetWindow();

	glfwSetWindowUserPointer(window.GetWindow(), this);

	glfwSetKeyCallback(this->window, [](GLFWwindow* window, int key, int scancode, int action, int mods) 
	{
		App* dataPtr = static_cast <App*> (glfwGetWindowUserPointer(window));
		dataPtr->OnKeyEvent(key, action);
	});

	glfwSetMouseButtonCallback(this->window, [](GLFWwindow* window, int button, int action, int mods)
	{
		App* dataPtr = static_cast <App*> (glfwGetWindowUserPointer(window));
		dataPtr->OnMouseButtonEvent(button, action);
	});

	glfwMakeContextCurrent(this->window);

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
	}
	
	glViewport(0.0f, 0.0f, (float)screenWidth, (float)screenHeight);
}

void App::OnKeyEvent(int key, int action)
{
	KeyPressEvent keyEvent;
	keyEvent.key = key;
	keyEvent.action = action;

	KeyEventQueue.Enqueue(keyEvent);
}

void App::OnMouseButtonEvent(int button, int action)
{
	//figure out what we want to do with this info.. 
	MouseClickEvent mouseClickEvent;
	mouseClickEvent.button = button;
	mouseClickEvent.action = action;

	MouseClickEventQueue.Enqueue(mouseClickEvent);
}

void App::Run()
{
	Init();

	float lastTime = glfwGetTime();

	while (!glfwWindowShouldClose(this->window))
	{
		float currentTime = glfwGetTime();
		float deltaTime = currentTime - lastTime;
		lastTime = currentTime;

		ProcessInput();
		Update(deltaTime);

		//glClearColor(0.203, 0.439, 0.819, 1.0f);
		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
		Render();

		glfwSwapBuffers(window);

		glfwPollEvents();

		glfwSwapInterval(1);
	}
}