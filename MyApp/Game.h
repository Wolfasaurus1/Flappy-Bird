#pragma once

#include "App.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Bird.h"
#include "PipeSystem.h"
#include <vector>


class Game : public App
{
public:

	SpriteRenderer *renderer;

	Bird bird;
	PipeSystem pipeSystem;
	glm::vec2 targetCoord;

	void Init()
	{
		ResourceManager::LoadShader("shaders/shader.vs", "shaders/shader.fs", "general_rectangle");
		renderer = new SpriteRenderer(ResourceManager::GetShader("general_rectangle"));

		//do this in bird init?
		bird.y = 600.0f;
		bird.vy = 0.0f;
		bird.ay = -4000.0f;

		srand(time(NULL));
		pipeSystem.Init();
	}

	void ResetLevel()
	{
		pipeSystem.Reset();
		bird.y = 600.0f;
		bird.vy = 0.0f;
	}

	void Update(float dt)
	{
		pipeSystem.Update(dt);
		bird.Update(dt);

		//number of pipes passed can easily be calculated
		int pipeIndex = fmaxf(floor((925.0f - pipeSystem.pipes[0].x) / 350.0f), -1.0f) + 1;

		if(pipeIndex < 25)
			targetCoord = glm::vec2(pipeSystem.pipes[pipeIndex].x, pipeSystem.pipes[pipeIndex].gapy);
		
		//do collision detection to make sure bird doesn't collide with pipes
		for (int i = 0; i < 25; i++)
		{
			float averageSizeX = (100.0f + 50.0f) / 2;

			if (abs(pipeSystem.pipes[i].x - 1000.0f) < averageSizeX && abs(pipeSystem.pipes[i].gapy - bird.y) > 100.0f || !(bird.y > 0.0f))
				ResetLevel();
		}
	}

	void Render()
	{
		for (Pipe& pipe : pipeSystem.pipes) {
			renderer->DrawSprite(glm::vec2(pipe.x, 600.0f), glm::vec2(50.0f, 1200.0f));
			renderer->DrawSprite(glm::vec2(pipe.x, pipe.gapy), glm::vec2(50.0f, 300.0f), 0.0f, glm::vec3(0.0f));
		}
		
		renderer->DrawSprite(glm::vec2(1000.0f, bird.y), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f, 0.5f, 0.1f));
		renderer->DrawSprite(targetCoord, glm::vec2(20.0f, 20.0f));
	}

	void ProcessInput()
	{
		int new_SPACE_state = glfwGetKey(this->window, GLFW_KEY_SPACE);

		if (new_SPACE_state == GLFW_PRESS && old_SPACE_state != GLFW_PRESS)
		{
			bird.vy = 900.0f;
		}

		old_SPACE_state = new_SPACE_state;
	}

private:
	int old_SPACE_state = 0;
};