#pragma once
class Bird
{
public:

	Bird(float y = 600.0, float vy = 0.0f, float ay = 0.0f)
	{
		this->y = y;
		this->vy = vy;
		this->ay = ay;
	}

	void Update(float dt)
	{
		y += (vy * dt) + (ay * dt * dt * 0.5f); //do gravity physics
		vy += ay * dt;
	}

	float y;
	float vy;
	float ay;
};

