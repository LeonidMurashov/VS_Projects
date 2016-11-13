#include "GeneticEngine.h"

vector<NeuralNetwork*> GeneticEngine::GeneticCircle(vector<NeuralNetwork*> _creatures, vector<double> _fitnesses, bool _boom)
{
	boom = _boom;
	creatures = _creatures;
	fitnesses = _fitnesses;
	vector<NeuralNetwork*> halfFinal;

	// Runs natural selection to half(a verb) current generation
	halfFinal = RunRoulett();

	// Create new generation from best of previous one
	Selection(halfFinal);	

	return creatures;
}

vector<NeuralNetwork*> GeneticEngine::RunRoulett()
{
	vector<double> dists;
	vector<int> roulett;	// Array size of [Roulett_Size]
	vector<NeuralNetwork*> halfFinal;
	double distSum = 0;

	for (int i = 0; i < creatures.size(); i++)
	{
		double a = fitnesses[i];
		dists.push_back(a);
		distSum += a;
	}

	// Creating roulett wheel
	for (int i = 0; i < dists.size(); i++)
	{
		int distsInt = round((dists[i] / (double)distSum) * Roulett_Size);
		for (int j = 0; j < distsInt; j++)
			roulett.push_back(i);
	}
	// Correct error of round function
	while (roulett.size() < Roulett_Size && creatures.size() > 0)
		roulett.push_back(rand() % creatures.size());

	// Run roulett wheel
	vector<bool> isCreaturePass(creatures.size(), false);
	for (int i = 0; i < (int)(creatures.size() / 2); i++)
	{
	mark:
		int creatureID = roulett[rand() % Roulett_Size];
		if (!isCreaturePass[creatureID])
		{
			halfFinal.push_back(creatures[creatureID]);
			isCreaturePass[creatureID] = true;
		}
		else
			goto mark;
	}	
	return halfFinal;
}

void GeneticEngine::Selection(vector<NeuralNetwork*> halfFinal)
{
	vector<NeuralNetwork*> newGeneration;
	int halfFinalSize = halfFinal.size();

	// Find and save the most succesful one	
	/*halfFinal.Sort();
	ASpider* bestOne = halfFinal[halfFinal.size() - 1];
	ASpider* bestOneChild = World->SpawnActor<ASpider>(ASpider::StaticClass());	// Transforms is set later
	bestOneChild->setNetwork(new NeuralNetwork(*bestOne->getNetwork()));
	newGeneration.Push(bestOneChild);*/

	// Crossovering creatures
	if(!boom)
		while (newGeneration.size() < creatures.size())
			newGeneration.push_back(BreedingFunction(halfFinal[rand() % halfFinalSize], halfFinal[rand() % halfFinalSize]));
	else
	{
		while (newGeneration.size() < creatures.size()/2)
			newGeneration.push_back(BreedingFunction(halfFinal[rand() % halfFinalSize], halfFinal[rand() % halfFinalSize]));
		while (newGeneration.size() < creatures.size())
			newGeneration.push_back(NeuralNetwork::GetRandomNetwork(creatures[0]->GetLayers()[0]->neurons.size(), 1));
	}
	creatures = newGeneration;
}
NeuralNetwork* GeneticEngine::BreedingFunction(NeuralNetwork* creature1, NeuralNetwork* creature2)
{
	NeuralNetwork* NN = NeuralNetwork::MergeNetworks(creature1, creature2, &GeneticEngine::MergeFunction1, &GeneticEngine::MergeFunction2, &GeneticEngine::MergeFunction3);
	return NN;
}

// Merging weights and biases
double GeneticEngine::MergeFunction1(double a, double b)
{
	double ka = NeuralNetworkLibrary2::Gaussian::GetRandomGaussian(0.5, 0.1);
	return (a*ka + b*(1 - ka))*(rand() % 10 == 0 ? randDouble() * 4 - 2 : 1);
}

// Merging number of layers and neurons
int GeneticEngine::MergeFunction2(int a, int b)
{
	return a;
}

// Merging Transfer functions
TransferFunction GeneticEngine::MergeFunction3(TransferFunction a, TransferFunction b)
{
	return a;
}
