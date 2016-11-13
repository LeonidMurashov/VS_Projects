#include <iostream>
#include "NeuralNetwork.cpp"
using namespace std;

int main()
{
	int layerCount[]{1, 2, 1};
	NeuralNetworkLibrary::TransferFunction tFuncs[]{ NeuralNetworkLibrary::TransferFunction::None,
													NeuralNetworkLibrary::TransferFunction::Sigmoid,
													NeuralNetworkLibrary::TransferFunction::Linear };
	NeuralNetworkLibrary::NeuralNetwork(layerCount, tFuncs);
	return 0;
}