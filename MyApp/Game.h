#pragma once

#include "App.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include <vector>


struct GameObject {
	glm::vec2 position, velocity, size;
	glm::vec3 color;
};

class Game : public App
{
public:

	SpriteRenderer *renderer;
	const static int numObjects = 20; // 1 player, 10 pipes, 10 gaps
	GameObject objects[numObjects];
	float bird_y = 600.0f;
	float bird_vy = 0.0f;
	float bird_ay = -4000.0f;

	void Init()
	{
		ResourceManager::LoadShader("shaders/shader.vs", "shaders/shader.fs", "general_rectangle");
		renderer = new SpriteRenderer(ResourceManager::GetShader("general_rectangle"));

		float pipeSpacing = 300.0f;
		float pipeShift = 2000.0f;

		for (int i = 0; i < 10; i++) {
			objects[i].position = glm::vec2(pipeShift + pipeSpacing * i, 600.0f);
			objects[i].size = glm::vec2(50.0f, 1200.0f);
			objects[i].velocity = glm::vec2(-200.0f, 0.0f);
			objects[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
		}

		//create the gaps in the pipes through which the bird can fly
		srand((unsigned)time(NULL));
		for (int i = 10; i < 20; i++)
		{
			objects[i].position = glm::vec2(pipeShift + pipeSpacing * (i - 10), (rand() % 500) + 350);
			objects[i].size = glm::vec2(50.0f, 300.0f);
			objects[i].velocity = glm::vec2(-200.0f, 0.0f);
			objects[i].color = glm::vec3(0.0f, 0.0f, 0.0f);
		}
	}

	void ResetLevel()
	{
		float pipeSpacing = 300.0f;
		float pipeShift = 2000.0f;

		for (int i = 0; i < 10; i++)
			objects[i].position.x = pipeShift + pipeSpacing * i;

		for (int i = 10; i < 20; i++)
			objects[i].position.x = pipeShift + pipeSpacing * (i - 10);
	}

	void Update(float dt)
	{
		for (GameObject& obj : objects)
			obj.position.x += obj.velocity.x * dt;

		bird_y += (bird_vy * dt) + (bird_ay * dt * dt * 0.5f);
		bird_vy += bird_ay * dt;

		for (int i = 10; i < 20; i++)
		{
			float averageSizeX = (100.0f + 50.0f) / 2;

			if (abs(objects[i].position.x - 1000.0f) < averageSizeX && abs(objects[i].position.y - bird_y) > 100.0f)
				ResetLevel();
		}
	}

	void Render()
	{
		for (GameObject& obj : objects)
			renderer->DrawSprite(obj.position, obj.size, 0.0f, obj.color); 

		renderer->DrawSprite(glm::vec2(1000.0f, bird_y), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f, 1.0f, 1.0f));
	}

	void ProcessInput()
	{
		int new_SPACE_state = glfwGetKey(this->window, GLFW_KEY_SPACE);

		if (new_SPACE_state == GLFW_PRESS && old_SPACE_state != GLFW_PRESS)
		{
			bird_vy = 900.0f;
		}

		old_SPACE_state = new_SPACE_state;
	}

private:
	int old_SPACE_state = 0;
};
