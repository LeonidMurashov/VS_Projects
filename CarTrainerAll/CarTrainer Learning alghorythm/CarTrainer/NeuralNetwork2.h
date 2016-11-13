
/*
*
*	Author: Leonid Murashov 30.05.2016
*
*	Neural network consists of classes(network, layer and neuron),
*	All neurons have connetions with all neurons of previous layer,
*	Several transfer functions,
*	Standart deviation random generator(Gaussian),
*	Merge networks method with passed to merge functions as parameters,
*	Save to and load from XML files methods 
*
*/
#pragma once
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string>
#include <vector>
#include "tinyxml2.h"
//using namespace std;
//using namespace tinyxml2;

namespace NeuralNetworkLibrary2
{
	//#define Length(a) (sizeof(a) / sizeof(a[0]))	// Returns the length of the array (!!! only for static !!!)
#define randDouble() ((double)(rand() / (double)RAND_MAX))	// Returns a random double from 0 to 1

#define NORMAL_HIDDEN_LAYER_SIZE 7
#define NORMAL_HIDDEN_LAYERS_COUNT 1

#define TRANSFER_FUNCTIONS_COUNT 5


#pragma region Transfer functions and their derivative

	enum TransferFunction
	{
		None,
		Linear,
		Sigmoid,
		Gaussian,
		RationalSigmoid
	};

	class TransferFunctions
	{
	public:
		static double Evaluate(TransferFunction tFunc, double input)
		{
			switch (tFunc)
			{
			case TransferFunction::Sigmoid:
				return sigmoid(input);
			case TransferFunction::Linear:
				return linear(input);
			case TransferFunction::Gaussian:
				return gaussian(input);
			case TransferFunction::RationalSigmoid:
				return rationalsigmoid(input);
			case TransferFunction::None:
			default:
				return 0.0;
			}
		}
		static double EvaluateDerivative(TransferFunction tFunc, double input)
		{
			switch (tFunc)
			{
			case TransferFunction::Sigmoid:
				return sigmoid_derivative(input);
			case TransferFunction::Linear:
				return linear_derivative(input);
			case TransferFunction::Gaussian:
				return gaussian_derivative(input);
			case TransferFunction::RationalSigmoid:
				return rationalsigmoid_derivative(input);
			case TransferFunction::None:
			default:
				return 0.0;
			}
		}

		/* Transfer functions declaration*/
	private:
		static double sigmoid(double x)
		{
			return 1.0 / (1.0 + exp(-x));
		}
		static double sigmoid_derivative(double x)
		{
			return sigmoid(x) * (1 - sigmoid(x));
		}

		static double linear(double x)
		{
			return x;
		}
		static double linear_derivative(double x)
		{
			return 1;
		}

		static double gaussian(double x)
		{
			return exp(-pow(x, 2));
		}
		static double gaussian_derivative(double x)
		{
			return -2.0 * x * gaussian(x);
		}

		static double rationalsigmoid(double x)
		{
			return x / (1.0 + sqrt(1.0 + x * x));
		}
		static double rationalsigmoid_derivative(double x)
		{
			double val = sqrt(1.0 + x * x);
			return 1.0 / (val * (1 + val));
		}
	};

#pragma endregion

	class Gaussian
	{

	public:

		static double GetRandomGaussian()
		{
			return GetRandomGaussian(0.0, 1.0);
		}
		static double GetRandomGaussian(double mean, double stddev)
		{
			double rVal1, rVal2;

			GetRandomGaussian(mean, stddev, rVal1, rVal2);

			return rVal1;
		}
		static void GetRandomGaussian(double mean, double stddev, double &val1, double &val2)
		{
			double u, v, s, t;

			do
			{
				u = 2 * randDouble() - 1;
				v = 2 * randDouble() - 1;
			} while (u * u + v * v > 1 || (u == 0 && v == 0));

			s = u * u + v * v;
			t = sqrt((-2.0 * log(s)) / s);

			val1 = stddev * u * t + mean;
			val2 = stddev * v * t + mean;
		}
	};

	enum LayerPosition { INPUT_LAYER, HIDDEN_LAYER, OUTPUT_LAYER };

	/*Some defines for MergeFunctions*/
	// Merge weights and biases
	typedef double(*Merge1)(double a, double b);
	// Merge layers and neurons count
	typedef int(*Merge2)(int a, int b);
	// Merge TransferFunctions
	typedef TransferFunction(*Merge3)(TransferFunction a, TransferFunction b);

#pragma region Neuron class
	class Neuron
	{
	private:
		double output;

		// For input layers(is not used by hidden and output layers)
		double inputData;
		// For hidden and output layers(is not used by input layers)
		std::vector<double> weights;
		double bias;

	public:
		// Default constructor
		Neuron(TransferFunction transferFunction, std::vector<Neuron *>previousLayerNeurons)
		{
			if (transferFunction != TransferFunction::None) // If neuron is not on input
			{
				for (int i = 0; i < previousLayerNeurons.size(); i++)
					weights.push_back(Gaussian::GetRandomGaussian());
				bias = Gaussian::GetRandomGaussian();
			}
		}
		// Merge constructor
		Neuron(std::vector<double> _weights, double _bias)
		{
			weights = _weights;
			bias = _bias;
		}

		void Run(TransferFunction transferFunction, std::vector<Neuron *>previousLayerNeurons)
		{
			if (transferFunction != TransferFunction::None) // If neuron is not on input
			{
				double sum = 0;
				for (int i = 0; i < previousLayerNeurons.size(); i++)
					sum += weights[i] * previousLayerNeurons[i]->GetOutput();

				output = TransferFunctions::Evaluate(transferFunction, sum + bias);
			}
			else
				output = inputData;
		}

		double GetOutput() { return output; }

		void SetInputData(double _inputData) { inputData = _inputData; }

	private:
		static void CastWeights(std::vector<double> &a, int previousLayerSize)
		{
			while (a.size() < previousLayerSize)
				a.push_back(Gaussian::GetRandomGaussian());

			if (a.size() > previousLayerSize)
				a.resize(previousLayerSize);
		}

	public:
		// MergeFunction() is situated in [GeneticEngine] source file 
		// Cannot be used to create input neuron
		static Neuron* MergeNeurons(Neuron* neuron1, Neuron* neuron2, int previousLayerSize, TransferFunction transferFunction, Merge1 MergeFunction)
		{
			if (transferFunction == TransferFunction::None)
				throw("MergeNeurons function cannot be used to create input neuron");

			std::vector<double> weights1, weights2, finalWeights;
			double bias1, bias2, finalBias;

			// Getting data from neurons 1 and 2
			neuron1->GetInvolvedData(weights1, bias1);
			neuron2->GetInvolvedData(weights2, bias2);

			//Casting weights to be the same demention
			CastWeights(weights1, previousLayerSize);
			CastWeights(weights2, previousLayerSize);

			// Merging data
			for (int i = 0; i < previousLayerSize; i++)
				finalWeights.push_back((*MergeFunction)(weights1[i], weights2[i]));
			finalBias = (*MergeFunction)(bias1, bias2);

			return new Neuron(finalWeights, finalBias);
		}

		void GetInvolvedData(std::vector<double> &_weights, double &_bias)
		{
			_weights = weights;
			_bias = bias;
		}

		~Neuron()
		{
			weights.clear();
		}
	};

#pragma endregion

	class Layer
	{
	public:
		std::vector<Neuron*> neurons;
		TransferFunction transferFunction;
		Layer* previousLayer;

		// Default constructor
		Layer(int size, TransferFunction _transferFunction, Layer *_previousLayer)
		{
			if (size == 0)
				throw("Layer cannot be empty");
			if (_transferFunction == TransferFunction::None && _previousLayer || !_transferFunction == TransferFunction::None && !_previousLayer)
				throw("Only input layer can have None TransferFunction");

			transferFunction = _transferFunction;
			previousLayer = _previousLayer;

			// Create neurons
			for (int i = 0; i < size; i++)
				neurons.push_back(new Neuron(transferFunction, (previousLayer) ? previousLayer->neurons : std::vector<Neuron*>()));
		}

		// Merge constructor
		Layer(std::vector<Neuron*> _neurons, TransferFunction _transferFunction, Layer *_previousLayer)
		{
			if (_neurons.size() == 0)
				throw("Layer cannot be empty");
			if (_transferFunction == TransferFunction::None && !_previousLayer)
				throw("Only input layer can have None TransferFunction");

			neurons = _neurons;
			transferFunction = _transferFunction;
			previousLayer = _previousLayer;
		}

		void Run()
		{
			for (int i = 0; i < neurons.size(); i++)
				neurons[i]->Run(transferFunction, (previousLayer) ? previousLayer->neurons : std::vector<Neuron*>());
		}

		// MergeFunction() is situated in [GeneticEngine] source file 
		// Layer* previosActualLayer is needed for creating layer, but if
		//		layer is on input can be NULL
		static Layer* MergeLayers(Layer* lay1, Layer* lay2, Layer* previosActualLayer, LayerPosition layerPosition,
			Merge1 MergeFunction, Merge2 MergeFunctionInt,
			Merge3 MergeFunctionTransfer)
		{
			std::vector<Neuron*> _neurons;
			TransferFunction _transferFunction = (*MergeFunctionTransfer)(lay1->transferFunction, lay2->transferFunction);
			int size;

			// Set demention of layer			
			if (layerPosition == LayerPosition::HIDDEN_LAYER)
				size = (*MergeFunctionInt)((int)lay1->neurons.size(), (int)lay2->neurons.size());
			else
				size = (int)lay1->neurons.size();

			// Neurons will be merged and set later
			Layer *finalLayer = new Layer(0, _transferFunction, previosActualLayer);

			// Actions for not input layer 
			if (previosActualLayer != NULL)
			{
				CastLayer(lay1, size);
				CastLayer(lay2, size);
				for (int i = 0; i < size; i++)
					_neurons.push_back(Neuron::MergeNeurons(lay1->neurons[i], lay2->neurons[i], (int)previosActualLayer->neurons.size(), _transferFunction, MergeFunction));
			}
			else // Actions in case of input layer
			{
				for (int i = 0; i < size; i++)
					_neurons.push_back(new Neuron(_transferFunction, previosActualLayer->neurons));
			}

			finalLayer->neurons = _neurons;
			return finalLayer;
		}

		static Layer* GetRandomLayer(Layer* _previousLayer)
		{
			int size;
			do
			{
				size = (int)round(Gaussian::GetRandomGaussian(NORMAL_HIDDEN_LAYER_SIZE, (double)NORMAL_HIDDEN_LAYER_SIZE / (double)2));
			} while (size < 1);

			return new Layer(size, TransferFunction(rand() % (TRANSFER_FUNCTIONS_COUNT - 2) + 2), _previousLayer);
		}

		~Layer()
		{
			neurons.clear();
		}


	private:
		static void CastLayer(Layer * lay, int size)
		{
			while (lay->neurons.size() < size)
				lay->neurons.push_back(new Neuron(lay->transferFunction, lay->previousLayer->neurons));
			if (lay->neurons.size() > size)
				lay->neurons.resize(size);
		}
	};

	class NeuralNetwork
	{
		std::vector<Layer*> layers;

	public:
		// Default constructor
		NeuralNetwork(std::vector<int> layerSizes, std::vector <TransferFunction> transferFunctions)
		{
			// Validate the input data
			if (transferFunctions.size() != layerSizes.size() || transferFunctions[0] != TransferFunction::None)
				throw ("Cannot construct a network with these parameters");

			// Create layers
			for (int i = 0; i < layerSizes.size(); i++)
				layers.push_back(new Layer(layerSizes[i], transferFunctions[i], i == 0 ? NULL : layers[i - 1]));
		}

		// Merge constructor
		NeuralNetwork(std::vector<Layer*> _layers)
		{
			// Validate the input data
			if (_layers.size() < 2)
				throw ("Cannot construct a network with these parameters");

			// Set layers
			layers = _layers;
		}

		std::vector<double> Run(std::vector<double> input)
		{
			// Make sure we have enough data
			if (input.size() != layers[0]->neurons.size())
				throw ("Input data is not of the correct dimention.");

			for (int i = 0; i < layers[0]->neurons.size(); i++)
				layers[0]->neurons[i]->SetInputData(input[i]);

			// Calculating the result 
			for (int i = 0; i < layers.size(); i++)
				layers[i]->Run();

			// Pushing the result to std::vector
			std::vector<double> output;
			for (int i = 0; i < layers[layers.size() - 1]->neurons.size(); i++)
				output.push_back(layers[layers.size() - 1]->neurons[i]->GetOutput());

			return output;
		}

		std::vector<Layer*> GetLayers() { return layers; }

	private:
		static void CastNetworkLayers(std::vector<Layer*> &a, int size)
		{
			if (size < 2)
				throw("Casting network layers failed");

			Layer* outputLayer = a[a.size() - 1];
			a.pop_back();

			while (a.size() < size - 1)
				a.push_back(Layer::GetRandomLayer(a[a.size() - 1]));
			if (a.size() > size - 1)
				a.resize(size - 1);

			a.push_back(outputLayer);
		}

	public:
		// MergeFunction() is situated in [GeneticEngine] source file
		static NeuralNetwork* MergeNetworks(NeuralNetwork* net1, NeuralNetwork* net2,
			Merge1 MergeFunction, Merge2 MergeFunctionInt,
			Merge3 MergeFunctionTransfer)
		{
			if (!MergeFunction || !MergeFunctionInt || !MergeFunctionTransfer)
				throw ("NULL MergeFuction recieved");

			std::vector<Layer*> layers1 = net1->GetLayers(),
				layers2 = net2->GetLayers(),
				finalLayers;
			int size = (*MergeFunctionInt)((int)layers1.size(), (int)layers2.size());

			// Casting layers to be the same demention
			CastNetworkLayers(layers1, size);
			CastNetworkLayers(layers2, size);

			for (int i = 0; i < size; i++)
			{
				LayerPosition layerPosition;
				if (i == 0) layerPosition = LayerPosition::INPUT_LAYER;
				else if (i == size - 1) layerPosition = LayerPosition::OUTPUT_LAYER;
				else layerPosition = LayerPosition::HIDDEN_LAYER;

				finalLayers.push_back(Layer::MergeLayers(layers1[i], layers2[i], i == 0 ? NULL : finalLayers[i - 1], layerPosition,
					MergeFunction, MergeFunctionInt, MergeFunctionTransfer));
			}

			return new NeuralNetwork(finalLayers);
		}

		static NeuralNetwork* GetRandomNetwork(int inputsCount, int outputsCount)
		{
			std::vector<Layer*> _layers;
			_layers.push_back(new Layer(inputsCount, TransferFunction::None, NULL));
			int size;
			do
			{
				size = (int)round(Gaussian::GetRandomGaussian(NORMAL_HIDDEN_LAYERS_COUNT, (double)NORMAL_HIDDEN_LAYERS_COUNT / (double)2));
			} while (size < 0);

			for (int i = 0; i < size; i++)
				_layers.push_back(Layer::GetRandomLayer(_layers[_layers.size() - 1]));

			_layers.push_back(new Layer(outputsCount, TransferFunction::Linear, _layers[_layers.size() - 1]));
			return new NeuralNetwork(_layers);
		}

		#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { return nullptr; }
		#define XMLCheckResultForNull(a_eResult) if(!a_eResult) { return nullptr; }
		/*
		Return a Neural Network created according to file
		*/
		static NeuralNetwork* LoadFromFile(const char* str)
		{
			std::vector<Layer*> layers;
			tinyxml2::XMLDocument xmlDoc;
			XMLCheckResult(xmlDoc.LoadFile(str));

			tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
			XMLCheckResultForNull(pRoot);

			tinyxml2::XMLElement * layElement = pRoot->FirstChildElement("Layer");
			XMLCheckResultForNull(layElement);

			int size;
			XMLCheckResult(layElement->QueryIntAttribute("size", &size));
			layers.push_back(new Layer(size, TransferFunction::None, NULL));

			layElement = layElement->NextSiblingElement();
			while (layElement)
			{
				std::vector<Neuron*> neurons;
				TransferFunction transferFunction;
				layElement->QueryAttribute("transferFunction", (int*)&transferFunction);
				XMLCheckResultForNull(transferFunction);

				tinyxml2::XMLElement *neuronElement = layElement->FirstChildElement("Neuron");
				XMLCheckResultForNull(neuronElement);
				while (neuronElement)
				{
					double bias;
					std::vector<double> weights;

					tinyxml2::XMLElement *paramElement = neuronElement->FirstChildElement("Bias");
					XMLCheckResultForNull(paramElement);
					XMLCheckResult(paramElement->QueryDoubleText(&bias));

					paramElement = neuronElement->LastChildElement("Weights");
					XMLCheckResultForNull(paramElement);
					
					tinyxml2::XMLElement *weightElement = paramElement->FirstChildElement("Weight");
					XMLCheckResultForNull(weightElement);
					while (weightElement)
					{
						double weight;
						XMLCheckResult(weightElement->QueryDoubleText(&weight));
						weights.push_back(weight);

						weightElement = weightElement->NextSiblingElement("Weight");
					}
					neurons.push_back(new Neuron(weights, bias));

					neuronElement = neuronElement->NextSiblingElement();
				}
				layers.push_back(new Layer(neurons, transferFunction, layers[layers.size()-1]));

				layElement = layElement->NextSiblingElement();
			}

			try {				
				return new NeuralNetwork(layers);
			}
			catch (...) {
				return nullptr;
			}
		}

		#undef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { return false; }

		/*
		Save Network to XML file
		*/
		bool SaveToFile(const char* str)
		{
			tinyxml2::XMLDocument xmlDoc;
			XMLCheckResult(xmlDoc.SaveFile(str));

			tinyxml2::XMLNode * pRoot = xmlDoc.NewElement("NeuralNetwork");
			xmlDoc.InsertFirstChild(pRoot);

			tinyxml2::XMLElement * layElement = xmlDoc.NewElement("Layer");
			layElement->SetAttribute("type", "input");
			layElement->SetAttribute("transferFunction", TransferFunction::None);
			layElement->SetAttribute("size", (int)layers[0]->neurons.size());
			pRoot->InsertFirstChild(layElement);
			for (int i = 1; i < layers.size(); i++)
			{
				layElement = xmlDoc.NewElement("Layer");
				if(i != layers.size() - 1)
					layElement->SetAttribute("type", "hidden");
				else
					layElement->SetAttribute("type", "output");
				
				layElement->SetAttribute("transferFunction", layers[i]->transferFunction);

				for (auto neuron : layers[i]->neurons)
				{
					tinyxml2::XMLElement * neuronElement = xmlDoc.NewElement("Neuron");
					std::vector<double> weights;
					double bias;
					neuron->GetInvolvedData(weights, bias);

					tinyxml2::XMLElement * weightsElement = xmlDoc.NewElement("Weights");
					for (int j = -1; j < (int)weights.size(); j++)
					{
						tinyxml2::XMLElement * paramElement;
						if (j == -1)
						{
							paramElement = xmlDoc.NewElement("Bias");
							paramElement->SetText(bias);
							neuronElement->InsertFirstChild(paramElement);
						}
						else
						{
							paramElement = xmlDoc.NewElement("Weight");
							paramElement->SetText(weights[j]);
							weightsElement->InsertEndChild(paramElement);
						}
					}
					neuronElement->InsertEndChild(weightsElement);
					layElement->InsertEndChild(neuronElement);
				}

				pRoot->InsertEndChild(layElement);
			}

			xmlDoc.InsertEndChild(pRoot);
			
			XMLCheckResult(xmlDoc.SaveFile(str));
			return true;
		}

		~NeuralNetwork()
		{
			layers.clear();
		}
	};
}