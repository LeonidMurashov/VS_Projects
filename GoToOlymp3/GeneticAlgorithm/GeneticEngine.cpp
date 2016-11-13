#include <algorithm>
#include <fstream>
#include "GeneticEngine.h"
//#include "Extra.hpp"

// Sets default values
GeneticEngine::GeneticEngine(TestNetwork _testFunction, NetworkProperty _networkProperty)
{
	testFunction = _testFunction;
	networkProperty = _networkProperty;
}

Creature* GeneticEngine::GeneticCircle(int _line)
{
	iteration++;
	line = _line;
	if (creatures.size() > 0)
	{
		vector<Creature*> halfFinal;

		// Runs natural selection to half(a verb) current generation
		halfFinal = RunRoulett();

		// Create new generation from best of previous one
		Selection(halfFinal);

		// Remove previous generation
		Remove();

		// Spawn current generaton
		Run();
		return bestOne;
	}
	else
	{
		// Create starting generation
		srand(time(NULL));
		CreateFirstGeneration();
		Run();
		return nullptr;
	}
}

void GeneticEngine::CreateFirstGeneration()
{
	creatures.clear();
	for (int i = 0; i < Population_Size; i++)
	{
		creatures.push_back(new Creature());
		creatures[i]->GenerateNewNetwork(networkProperty);
	}
}

void GeneticEngine::Run()
{
	cout << "Testing networks: 0%" << endl;
	int i2 = 0;
	for (auto creature : creatures)
	{
		creature->Run(testFunction);
		//SetCursorPosistion(18, line);
		cout << i2 / (double)Population_Size << "%";
		i2++;
	}
	cout << "Testing networks: 100%" << endl;
	line++;
}

void GeneticEngine::Remove()
{
	// Just emptying array
	oldCreatures.clear();
}

vector<Creature*> GeneticEngine::RunRoulett()
{
	vector<double> dists;
	vector<int> roulett;	// Array size of [Roulett_Size]
	vector<Creature*> halfFinal;
	double distSum = 0;

	for (int i = 0; i < creatures.size(); i++)
	{
		double a = creatures[i]->GetFitness();
		dists.push_back(a);
		distSum += a;
	}

	// Creating roulett wheel
	for (int i = 0; i < dists.size(); i++)
	{
		int distsInt = min((int)round(dists[i] * ((double)Roulett_Size / distSum)), 1);
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

bool CreaturesComparator(Creature* a, Creature *b)
{
	return a->GetFitness() < b->GetFitness();
}

void GeneticEngine::Selection(vector<Creature*> halfFinal)
{
	vector<Creature*> newGeneration;
	int halfFinalSize = halfFinal.size();

	// Find and save the most succesful one
	sort(halfFinal.begin(), halfFinal.end(), CreaturesComparator); // Sort by increase
	Creature* _bestOne = halfFinal[halfFinal.size() - 1];
	Creature* bestOneChild = new Creature();
	bestOne = new Creature();
	bestOne->SetFitness(_bestOne->GetFitness());
	bestOne->SetNetwork(new NeuralNetwork(*_bestOne->GetNetwork()));
	bestOneChild->SetNetwork(new NeuralNetwork(*_bestOne->GetNetwork()));
	//newGeneration.push_back(bestOneChild);

	// Crossovering creatures
	while (newGeneration.size() < Population_Size)
		newGeneration.push_back(BreedingFunction(halfFinal[rand() % halfFinalSize], halfFinal[rand() % halfFinalSize]));

	oldCreatures = creatures;
	creatures = newGeneration;
}
Creature* GeneticEngine::BreedingFunction(Creature* creature1, Creature* creature2)
{
	Creature* finalSpider = new Creature();	// Transforms is set later
	finalSpider->SetNetwork(NeuralNetwork::MergeNetworks(creature1->GetNetwork(), creature2->GetNetwork(), &GeneticEngine::MergeFunction));

	return finalSpider;
}

// Merging weights and biases
double GeneticEngine::MergeFunction(double a, double b)
{
	double k = NeuralNetworkLibrary::Gaussian::GetRandomGaussian(0.5, 0.1);
	return (a*k + b*(1 - k))*(rand() % 3 == 0 ? randDouble() * 4 - 2 : 1);
}