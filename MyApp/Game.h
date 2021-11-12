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
	const static int numObjects = 21; // 1 player, 10 pipes, 10 gaps
	GameObject objects[numObjects];

	void Init()
	{
		ResourceManager::LoadShader("shaders/shader.vs", "shaders/shader.fs", "general_rectangle");
		renderer = new SpriteRenderer(ResourceManager::GetShader("general_rectangle"));

		//
		float pipeSpacing = 300.0f;
		float pipeShift = 1000.0f;

		objects[20].position = glm::vec2(1000.0f, 600.0f);
		objects[20].size = glm::vec2(100.0f, 100.0f);
		objects[20].velocity = glm::vec2(0.0f, 0.0f);
		objects[20].color = glm::vec3(1.0f, 1.0f, 1.0f);

		for (int i = 0; i < 10; i++) {
			objects[i].position = glm::vec2(1000.0f + pipeSpacing * i, 600.0f);
			objects[i].size = glm::vec2(50.0f, 1200.0f);
			objects[i].velocity = glm::vec2(-10.0f, 0.0f);
			objects[i].color = glm::vec3(1.0f, 1.0f, 1.0f);
		}

		//create the gaps in the pipes through which the bird can fly
		srand((unsigned)time(NULL));
		for (int i = 10; i < 20; i++)
		{
			objects[i].position = glm::vec2(1000.0f + pipeSpacing * (i - 10), (rand() % 500) + 350);
			objects[i].size = glm::vec2(100.0f, 300.0f);
			objects[i].velocity = glm::vec2(-10.0f, 0.0f);
			objects[i].color = glm::vec3(0.0f, 0.0f, 0.0f);
		}
		//making a change
	}

	void Update(float dt)
	{
		for (GameObject& obj : objects)
			obj.position.x += obj.velocity.x;
	}

	bool IsCollision(GameObject entity1, GameObject entity2, float dt)
	{
		float averageXLength = abs(entity1.size.x - entity2.size.x);
		float averageYLength = abs(entity1.size.y - entity2.size.y);

		glm::vec2 ds = glm::abs((entity1.position + entity1.velocity * dt) - (entity2.position + entity2.velocity * dt));

		if (ds.y < averageYLength && ds.x < averageXLength)
		{
			return true;
		}

		return false;
	}

	void Render()
	{
		for (GameObject& obj : objects)
			renderer->DrawSprite(obj.position, obj.size, 0.0f, obj.color); 
	}

	void ProcessInput()
	{
		
	}

private:
};
