
#include <stdlib.h>     /* rand */
#include <time.h>       /* time */
#include <math.h>
#include <string>
#include <vector>
using namespace std;

namespace NeuralNetworkLibrary2
{
	//#define Length(a) (sizeof(a) / sizeof(a[0]))	// Returns the length of the array (!!! only for static !!!)
#define randDouble() ((double)(rand() / (double)RAND_MAX))	// Returns a random double from 0 to 1

#pragma region Transfer functions and their derivative

	enum TransferFunction
	{
		None,
		Sigmoid,
		Linear,
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
	
	class Layer
	{	
		
		class Neuron
		{
		private:
			// For input layers(is not used by hidden and output layers)
			double inputData;
			// For hidden and output layers(is not used by input layers)
			vector<double> weights;
			double *bias; // Bias is dynamic because of it can be NULL
			Layer* parentLayer;

		public:
			// Default constructor
			Neuron(Layer* _parentLayer)
			{
				parentLayer = _parentLayer;
				if (parentLayer->transferFunction != TransferFunction::None) // If neuron is not on input
				{
					for (unsigned int i = 0; i < parentLayer->previousLayer->neurons.size(); i++)
						weights.push_back(Gaussian::GetRandomGaussian());
					bias = new double(Gaussian::GetRandomGaussian());
				}
			}
			// Merge constructor
			Neuron(Layer* _parentLayer, vector<double> _weights, double* _bias)
			{
				parentLayer = _parentLayer;
				weights = _weights;
				bias = _bias;
			}

			double Run()
			{
				if (parentLayer->transferFunction != TransferFunction::None) // If neuron is not on input
				{
					double sum = 0;
					for (unsigned int i = 0; i < parentLayer->previousLayer->neurons.size(); i++)
						sum += weights[i] * parentLayer->previousLayer->neurons[i]->Run();
					return TransferFunctions::Evaluate(parentLayer->transferFunction, sum + *bias);
				}
				else
					return inputData;
			}

			void SetInputData(double _inputData)
			{
				inputData = _inputData;
			}

		private:
			static void CastWeights(vector<double> &a, Layer *_parentLayer)
			{
				while (a.size() < _parentLayer->previousLayer->neurons.size())
					a.push_back(Gaussian::GetRandomGaussian());

				if (a.size() > _parentLayer->previousLayer->neurons.size())
					a.resize(_parentLayer->previousLayer->neurons.size());
			}

		public:
			// MergeFunction() is situated in [GeneticEngine] source file 
			// !!!parentLayer is NULL!!!
			// Cannot be used to create input neuron
			static Neuron* MergeNeurons(Neuron* neuron1, Neuron* neuron2, Layer* _parentLayer, double(*MergeFunction)(double a, double b))
			{
				if (_parentLayer->transferFunction != TransferFunction::None)
					throw("MergeNeurons function cannot be used to create input neuron");

				vector<double> weights1, weights2, finalWeights;
				double *bias1, *bias2, *finalBias;

				// Getting data from neurons 1 and 2
				neuron1->GetInvolvedData(weights1, bias1);
				neuron2->GetInvolvedData(weights2, bias2);


				//Casting weights to be the same demention
				CastWeights(weights1, _parentLayer);
				CastWeights(weights2, _parentLayer);

				for (unsigned int i = 0; i < _parentLayer->previousLayer->neurons.size(); i++)
					finalWeights.push_back(MergeFunction(weights1[i], weights2[i]));
				finalBias = new double(MergeFunction(*bias1, *bias2));

				return new Neuron(_parentLayer, finalWeights, finalBias);
			}

			void GetInvolvedData(vector<double> &_weights, double *_bias)
			{
				_weights = weights;
				_bias = bias;
			}

			~Neuron()
			{
				delete bias;
				weights.clear();
			}
		};		

	public:
		
		vector<Neuron*> neurons;
		TransferFunction transferFunction;
		Layer* previousLayer;

		// Default constructor
		Layer(int size, TransferFunction _transferFunction, Layer *_previousLayer)
		{
			transferFunction = _transferFunction;
			previousLayer = _previousLayer;

			// Create neurons
			for (int i = 0; i < size; i++)
				neurons.push_back(new Neuron(this));
		}
		// Merge constructor
		Layer(vector<Neuron*> _neurons, TransferFunction _transferFunction, Layer *_previousLayer)
		{
			neurons = _neurons;
			transferFunction = _transferFunction;
			previousLayer = _previousLayer;
		}


		// MergeFunction() is situated in [GeneticEngine] source file 
		// Layer* previosActualLayer is needed for get neurons count in it, but if
		//		layer is on input can be NULL
		static Layer* MergeLayers(Layer* lay1, Layer* lay2, Layer* previosActualLayer, LayerPosition layerPosition,
			double(*MergeFunction)(double a, double b), int(*MergeFunctionInt)(int a, int b),
			TransferFunction(*MergeFunctionTransfer)(TransferFunction a, TransferFunction b))
		{
			vector<Neuron*> _neurons;
			TransferFunction _transferFunction = MergeFunctionTransfer(lay1->transferFunction, lay2->transferFunction);

			// Set demention of layer
			int size;
			if (layerPosition == LayerPosition::HIDDEN_LAYER)
				size = MergeFunctionInt(lay1->neurons.size(), lay2->neurons.size());
			else
				size = lay1->neurons.size();

			// Neurons will be merged and set later
			Layer *finalLayer = new Layer(size, _transferFunction, previosActualLayer);

			// Actions for not input layer 
			if (previosActualLayer != NULL)
			{
				CastLayer(lay1, size);
				CastLayer(lay2, size);
				for (int i = 0; i < size; i++)
					_neurons.push_back(Neuron::MergeNeurons(lay1->neurons[i], lay2->neurons[i], finalLayer, MergeFunction));
			}
			else // Actions in case of input layer
			{
				for (int i = 0; i < size; i++)
					_neurons.push_back(new Neuron(finalLayer));
			}

			finalLayer->neurons = _neurons;
			return finalLayer;
		}

		~Layer()
		{
			neurons.clear();
		}


	private:
		static void CastLayer(Layer * lay, unsigned int size)
		{
			while (lay->neurons.size() < size)
				lay->neurons.push_back(new Neuron(lay));
			if (lay->neurons.size() > size)
				lay->neurons.resize(size);
		}
	};	

	class NeuralNetwork
	{
		vector<Layer*> layers;

	public:
		// Default constructor
		NeuralNetwork(vector<int> layerSizes, vector <TransferFunction> transferFunctions)
		{
			// Validate the input data
			if (transferFunctions.size() != layerSizes.size() || transferFunctions[0] != TransferFunction::None)
				throw ("Cannot construct a network with these parameters");

			// Create layers
			for (unsigned int i = 0; i < layerSizes.size(); i++)
				layers.push_back(new Layer(layerSizes[i], transferFunctions[i], i == 0 ? NULL : layers[i - 1]));
		}

		// Merge constructor
		NeuralNetwork(vector<Layer*> _layers)
		{
			// Validate the input data
			if (_layers.size()<3)
				throw ("Cannot construct a network with these parameters");

			// Set layers
			layers = _layers;
		}

		vector<double> Run(vector<double> input)
		{
			// Make sure we have enough data
			if (input.size() != layers[0]->neurons.size())
				throw ("Input data is not of the correct dimention.");

			for (unsigned int i = 0; i < layers[0]->neurons.size(); i++)
				layers[0]->neurons[i]->SetInputData(input[i]);

			// Calculating the result 
			vector<double> output;
			for (unsigned int i = 0; i < layers[layers.size() - 1]->neurons.size(); i++)
				output.push_back(layers[layers.size() - 1]->neurons[i]->Run());
			return output;

		}

		vector<Layer*> GetLayers()
		{
			return layers;
		}

		// MergeFunction() is situated in [GeneticEngine] source file
		// NeuralNetworks net1 and net2 should be of the same demention
		static NeuralNetwork* MergeNetworks(NeuralNetwork* net1, NeuralNetwork* net2,
			double(*MergeFunction)(double a, double b), int(*MergeFunctionInt)(int a, int b),
			TransferFunction(*MergeFunctionTransfer)(TransferFunction a, TransferFunction b))
		{
			vector<Layer*> layers1 = net1->GetLayers(),
				layers2 = net2->GetLayers(),
				finalLayers;
			int size = MergeFunctionInt(layers1.size(), layers2.size());
			for (int i = 0; i < size; i++)
			{
				LayerPosition layerPosition;
				if (i == 0) layerPosition = LayerPosition::INPUT_LAYER;
				else if (i == size - 1) layerPosition = LayerPosition::OUTPUT_LAYER;
				else layerPosition = LayerPosition::HIDDEN_LAYER;

				finalLayers.push_back(Layer::MergeLayers(layers1[i], layers2[i], i == 0 ? NULL : finalLayers[i - 1], layerPosition,
					MergeFunction, MergeFunctionInt, MergeFunctionTransfer));
				return new NeuralNetwork(finalLayers);
			}
			//NeuralNetwork* finalNetwork = new NeuralNetwork(net1->Actual_layerSize, net1->Actual_transferFunction);

		}

		~NeuralNetwork()
		{
			layers.clear();
		}
	};
}