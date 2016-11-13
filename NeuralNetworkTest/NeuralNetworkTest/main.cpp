#include <iostream>
#include <vector>
#include <time.h>
#include "NeuralNetwork.h"

using namespace std;
using namespace NeuralNetworkLibrary;
int main()
{
	srand(time(NULL));
	vector<int> sizes = {1, 5, 1};
	//int i = 0;
	vector<TransferFunction> tFuncs = { TransferFunction::None,
										TransferFunction::RationalSigmoid,
										TransferFunction::Linear };
	NeuralNetwork *Network = new NeuralNetwork(sizes, tFuncs);
	
	//NeuralNetwork *Network = NeuralNetwork::LoadFromFile("D://newXML2.XML");
	for (int i = 0; i < 500; i++)
	{
		double a = (rand() % 10) + randDouble();
		vector<double> input = { a };
		vector<double> desired = { a*a };
		Network->Train(input, desired, 0.001, 0.00001);
		if (i % 1000 == 0)
		{
			vector<double> input = { 3 };
			vector<double> output;
			Network->Run(input, output);
			cout << "Pass " << i << ": " << (int(output[0]*100))/(double)100 << endl;
		}
	}

	Network->SaveToFile("D://newXML2.XML");

	system("pause");
	return 0;
}