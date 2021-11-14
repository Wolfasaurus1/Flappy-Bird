#pragma once
#include <glm/glm.hpp>
#include <vector>
#include <memory>

class Pipe
{
public:

	Pipe(float x, float gapy) {
		this->x = x;
		this->gapy = gapy;
	}
	
	float x, gapy;
};

class PipeSystem
{
public:

	std::vector<Pipe> pipes;
	float pipeGapSize = 300, pipeSpacing = 350.0f, pipeSpeed = 400.0f;
	glm::vec3 pipeColor;

	void Init()
	{
		for (int i = 0; i < 10; i++)
			pipes.push_back(Pipe(1500.0f + (i * pipeSpacing), (rand() % 500) + 350));
	}

	void Update(float dt)
	{
		for (Pipe& pipe : pipes)
			pipe.x -= pipeSpeed * dt;
	}

	void Reset()
	{
		int i = 0;
		for (Pipe& pipe : pipes)
			pipe.x = 1500.0f + (i++ * pipeSpacing);
	}
};

