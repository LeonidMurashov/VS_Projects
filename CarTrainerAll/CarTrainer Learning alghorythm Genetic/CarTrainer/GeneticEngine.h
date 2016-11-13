// Genetic Engine

#pragma once
#include "NeuralNetwork2.h"

using namespace NeuralNetworkLibrary2;
using std::vector;

class GeneticEngine
{	
public:
	// Main circle of Genetic Algorythm
	vector<NeuralNetwork*> GeneticCircle(vector<NeuralNetwork*> _creatures, vector<double> _fitnesses, bool _boom);

private:
	bool boom = false;
	vector<NeuralNetwork*> creatures;
	vector<double> fitnesses;
	const int Roulett_Size = 5000;	// Count of segments of Roulett, should be grater than creatures.size()
	
	// Run "roulett" randomizer - return a half of creatures (Selection Function)
	vector<NeuralNetwork*> RunRoulett();

	// Crossing Function
	void Selection(vector<NeuralNetwork*> halfFinal);

	// Merge Networks data
	NeuralNetwork* BreedingFunction(NeuralNetwork* creature1, NeuralNetwork* creature2);

	// Merge functions, which allow to control merging networks process 
	static double MergeFunction1(double a, double b);									// Merge weights and biases
	static int MergeFunction2(int a, int b);											// Merge layers and neurons count
	static TransferFunction MergeFunction3(TransferFunction a, TransferFunction b);	// Merge transfer functions

};
