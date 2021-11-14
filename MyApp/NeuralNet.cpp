#include "NeuralNet.h"

using namespace Eigen;


void NeuralNet::GenerateRandomBrain()
{
	w1.setRandom();
	w2.setRandom();
	b1.setRandom();
	b2.setRandom();
}


float NeuralNet::Think(float input1, float input2)
{
	Vector<float, 2> input(input1, input2);

	Vector<float, 3> layer1 = ((w1 * input) + b1).unaryExpr(&Sigmoid);
	Vector<float, 1> layer2 = ((w2 * layer1) + b2).unaryExpr(&Sigmoid);

	return layer2(0);
}


void NeuralNet::MutateWeights()
{
	w1(rand() % 3, rand() % 2) = RandomFloat(-2.0f, 2.0f);
	w2(rand() % 3, 0) = RandomFloat(-2.0f, 2.0f);
}


void NeuralNet::MutateBiases()
{
	b1(rand() % 3) = RandomFloat(-2.0f, 2.0f);

	if (rand() % 4 == 3)
		b2(0) = RandomFloat(-2.0f, 2.0f);
}


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


float RandomFloat(float a, float b)
{
	float random = ((float)rand()) / (float)RAND_MAX;
	float diff = b - a;
	float r = random * diff;
	return a + r;
}


float Sigmoid(float z)
{
	return 1.0f / (1.0f + std::exp(-z));
}