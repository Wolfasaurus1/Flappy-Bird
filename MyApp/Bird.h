#pragma once
#include "NeuralNet.h"
#include <glm/glm.hpp>
#include <iostream>

class Bird
{
public:

	Bird(float y = 600.0, float vy = 0.0f, float ay = 0.0f)
	{
		this->y = y;
		this->vy = vy;
		this->ay = ay;
		brain.GenerateRandomBrain();
	}

	void Update(float dt, glm::vec2 brain_inputs)
	{
		y += (vy * dt) + (ay * dt * dt * 0.5f); //do gravity physics
		vy += ay * dt;

		float output = brain.Think(brain_inputs.x, brain_inputs.y);

		if (output > 0.5f) {
			WillFlap = true;
		}
		else {
			WillFlap = false;
		}
	}

	void Reset()
	{
		y = 600.0f;
		vy = 0.0f;
		IsDead = false;
		fitness = -1000.0f;
	}

	float y;
	float vy;
	float ay;
	NeuralNet brain;
	bool WillFlap = false;
	bool IsDead = false;
	float fitness = -1000.0f;
};

