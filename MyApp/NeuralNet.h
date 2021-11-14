#pragma once
#include <iostream>
#include <Eigen/Dense>


float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}

static float Sigmoid(float z)
{
	return 1.0f / (1.0f + std::exp(-z));
}

using namespace Eigen;

class NeuralNet
{
public:

	void GenerateRandomBrain()
	{
		w1.setRandom();
		w2.setRandom();
		b1.setRandom();
		b2.setRandom();
	}

	float Think(float input1, float input2)
	{
		Vector<float, 2> input(input1, input2);

		Vector<float, 3> layer1 = ((w1 * input) + b1).unaryExpr(&Sigmoid);
		Vector<float, 1> layer2 = ((w2 * layer1) + b2).unaryExpr(&Sigmoid);

		return layer2(0);
	}

	void MutateWeights()
	{
		w1(rand() % 3, rand() % 2) = RandomFloat(-2.0f, 2.0f);
		w2(rand() % 3, 0) = RandomFloat(-2.0f, 2.0f);
	}

	void MutateBiases()
	{
		b1(rand() % 3) = RandomFloat(-2.0f, 2.0f);

		if (rand() % 4 == 3)
			b2(0) = RandomFloat(-2.0f, 2.0f);
	}

	//weights
	Matrix<float, 3, 2> w1;
	Matrix<float, 1, 3> w2;

	//biases
	Vector<float, 3> b1;
	Vector<float, 1> b2;
};


void UniformCrossover(NeuralNet& net1, NeuralNet& net2)
{
	for (int i = 0; i < 3; i++)
	{
		if ((rand() % 2) + 1 == 2)
		{
			float tmp = net1.b1(i);
			net1.b1(i) = net2.b1(i);
			net2.b1(i) = tmp;
		}
	}

	if ((rand() % 2) + 1 == 2)
	{
		float tmp = net1.b2(0);
		net1.b2(0) = net2.b2(0);
		net2.b2(0) = tmp;
	}
}
