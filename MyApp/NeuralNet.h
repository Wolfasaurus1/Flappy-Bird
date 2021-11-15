#pragma once
#include <Eigen/Dense>


class NeuralNet
{
public:

	void GenerateRandomBrain();
	float Think(float input1, float input2);
	void MutateWeights();
	void MutateBiases();

	//weights
	Eigen::Matrix<float, 3, 2> w1;
	Eigen::Matrix<float, 1, 3> w2;

	//biases
	Eigen::Vector<float, 3> b1;
	Eigen::Vector<float, 1> b2;
};

std::pair<NeuralNet, NeuralNet> UniformCrossover(NeuralNet net1, NeuralNet net2);
float RandomFloat(float a, float b);
float Sigmoid(float z);