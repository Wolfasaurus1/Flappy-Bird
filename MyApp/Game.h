#pragma once

#include "App.h"
#include "SpriteRenderer.h"
#include "ResourceManager.h"
#include "Bird.h"
#include "PipeSystem.h"
#include "NeuralNet.h"

#include <vector>
#include <numeric>


class Game : public App
{
public:

	SpriteRenderer *renderer;
	std::vector<Bird> birds;
	PipeSystem pipeSystem;
	glm::vec2 targetCoord;

	void Init()
	{
		ResourceManager::LoadShader("shaders/shader.vs", "shaders/shader.fs", "general_rectangle");
		renderer = new SpriteRenderer(ResourceManager::GetShader("general_rectangle"));

		srand(time(NULL));

		for(int i = 0; i < 10; i++)
			birds.push_back({ 600.0f, 0.0f, -4000.0f });

		pipeSystem.Init();
	}

	std::vector<size_t> RankBirds()
	{
		std::vector<size_t> idx(birds.size());
		std::iota(idx.begin(), idx.end(), 0);

		stable_sort(idx.begin(), idx.end(),
			[this](size_t i1, size_t i2) {return birds[i1].fitness > birds[i2].fitness; });

		return idx;
	}

	void ResetLevel()
	{
		pipeSystem.Reset();

		for (auto& bird : birds)
			bird.Reset();
	}

	void Update(float dt)
	{
		pipeSystem.Update(dt);

		//number of pipes passed can easily be calculated
		int pipeIndex = fmaxf(floor((925.0f - pipeSystem.pipes[0].x) / 350.0f), -1.0f) + 1;

		if(pipeIndex < 25)
			targetCoord = glm::vec2(pipeSystem.pipes[pipeIndex].x, pipeSystem.pipes[pipeIndex].gapy);

		int BirdsAliveCount = 0;
		for (Bird& bird : birds) 
		{
			if (!bird.IsDead) 
			{
				bird.Update(dt, (targetCoord - glm::vec2(1000.0f, bird.y)) / 300.0f);
				float averageSizeX = (100.0f + 50.0f) / 2;

				if (abs(pipeSystem.pipes[pipeIndex].x - 1000.0f) < averageSizeX && abs(pipeSystem.pipes[pipeIndex].gapy - bird.y) > 100.0f || !(bird.y > 0.0f)) 
				{
					bird.IsDead = true;
					bird.fitness = 1000.0f - pipeSystem.pipes[0].x; //then we can sort them based on fitness when all of them die
				}
				else 
				{
					BirdsAliveCount++;
				}
			}
		}

		if (BirdsAliveCount == 0)
			ResetLevel();
	}

	void Render()
	{
		for (Pipe& pipe : pipeSystem.pipes) {
			renderer->DrawSprite(glm::vec2(pipe.x, 600.0f), glm::vec2(50.0f, 1200.0f));
			renderer->DrawSprite(glm::vec2(pipe.x, pipe.gapy), glm::vec2(50.0f, 300.0f), 0.0f, glm::vec3(0.0f));
		}
		
		for(Bird& bird: birds)
			if(!bird.IsDead)
				renderer->DrawSprite(glm::vec2(1000.0f, bird.y), glm::vec2(100.0f, 100.0f), 0.0f, glm::vec3(1.0f, 0.5f, 0.1f));
		
		renderer->DrawSprite(targetCoord, glm::vec2(20.0f, 20.0f));
	}

	void ProcessInput()
	{
		for (Bird& bird : birds) {
			if (bird.WillFlap)
			{
				bird.vy = 900.0f;
				bird.WillFlap = false;
			}
/*
			int new_SPACE_state = glfwGetKey(this->window, GLFW_KEY_SPACE);

			if (new_SPACE_state == GLFW_PRESS && old_SPACE_state != GLFW_PRESS)
			{
				bird.vy = 900.0f;
			}

			old_SPACE_state = new_SPACE_state;
			*/
		}
	}

private:
	int old_SPACE_state = 0;
};