
/*
*
*	Author: Leonid Murashov 29.05.2016
*
*	Neural network consists of tons of arrays,
*	All neurons have connetions with all neurons of previous layer,
*	Several transfer functions,
*	Error back-propagation method of training,
*	Normal distribution random generator(Gaussian),
*	Get and set involved data methods.
*
*/

#include <stdlib.h>     /* rand */
#include <time.h>       /* time */
#include <math.h>
#include <string>
#include <vector>
#include "tinyxml2.h"
using namespace std;

namespace NeuralNetworkLibrary
{
	using namespace tinyxml2;

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

	class NeuralNetwork
	{

#pragma region Constructors and destructors

	public:
		NeuralNetwork(vector<int> layerSizes, vector <TransferFunction> transferFunctions)
		{
			//Validate the input data
			if (transferFunctions.size() != layerSizes.size() || transferFunctions[0] != TransferFunction::None)
				throw ("Cannot construct a network with these parameters");

			// Initialize the randomizer	 ( Some bug with randomizer has gone away )
		//	Sleep(1); // Sleep to get true random values from randomizer
		//	srand(clock());

			// Saving data for exporting method
			Actual_layerSize = layerSizes;
			Actual_transferFunction = transferFunctions;

			//Initialize network layers
			layerCount = (uint32_t)layerSizes.size() - 1;
			inputSize = layerSizes[0];

			layerSize.resize(layerCount);
			for (int i = 0; i < layerCount; i++)
				layerSize[i] = layerSizes[i + 1];

			transferFunction.resize(layerCount);
			for (int i = 0; i < layerCount; i++)
				transferFunction[i] = transferFunctions[i + 1];

			//Start dementioning arrays
			bias.resize(layerCount);
			previousBiasDelta.resize(layerCount);
			delta.resize(layerCount);
			layerOutput.resize(layerCount);
			layerInput.resize(layerCount);

			weight.resize(layerCount);
			previousWeightDelta.resize(layerCount);

			//Fill 2 dimentional arrays
			for (int l = 0; l < layerCount; l++)
			{
				bias[l].resize(layerSize[l]);
				previousBiasDelta[l].resize(layerSize[l]);
				delta[l].resize(layerSize[l]);
				layerOutput[l].resize(layerSize[l]);
				layerInput[l].resize(layerSize[l]);

				weight[l].resize(l == 0 ? inputSize : layerSize[l - 1]);
				previousWeightDelta[l].resize(l == 0 ? inputSize : layerSize[l - 1]);

				for (int i = 0; i<(l == 0 ? inputSize : layerSize[l - 1]); i++)
				{
					weight[l][i].resize(layerSize[l]);
					previousWeightDelta[l][i].resize(layerSize[l]);
				}
			}

			// Initialize the weights
			for (int l = 0; l<layerCount; l++)
			{
				for (int j = 0; j<layerSize[l]; j++)
				{
					bias[l][j] = Gaussian::GetRandomGaussian();
					previousBiasDelta[l][j] = 0.0;
					layerOutput[l][j] = 0.0;
					layerInput[l][j] = 0.0;
					delta[l][j] = 0.0;
				}

				for (int i = 0; i< (l == 0 ? inputSize : layerSize[l - 1]); i++)
				{
					for (int j = 0; j<layerSize[l]; j++)
					{
						weight[l][i][j] = Gaussian::GetRandomGaussian();
						previousWeightDelta[l][i][j] = 0.0;
					}
				}
			}
		}

		~NeuralNetwork()
		{
			Name.clear();

			layerSize.clear();
			transferFunction.clear();

			layerOutput.clear();
			layerInput.clear();
			bias.clear();
			delta.clear();
			previousBiasDelta.clear();

			weight.clear();
			previousWeightDelta.clear();

			Actual_layerSize.clear();
			Actual_transferFunction.clear();
			Actual_weight.clear();
		}

#pragma endregion

#pragma region Methods

	public:
		void Run(vector <double> input, vector <double> &output)
		{
			//Make sure we have enough data
			if (input.size() != inputSize)
				throw ("Input data is not of the correct dimention.");

			//Dimention 
			output = vector<double>();
			output.resize(layerSize[layerCount - 1]);
			
			/* Run the network */
			for (int l = 0; l < layerCount; l++)
			{
				for (int j = 0; j < layerSize[l]; j++)
				{
					double sum = 0.0;
					for (int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
						sum += weight[l][i][j] * (l == 0 ? input[i] : layerOutput[l - 1][i]);

					sum += bias[l][j];
					layerInput[l][j] = sum;

					layerOutput[l][j] = TransferFunctions::Evaluate(transferFunction[l], sum);
				}
			}

			//Copy the output to the output array
			for (int i = 0; i < layerSize[layerCount - 1]; i++)
				output[i] = layerOutput[layerCount - 1][i];
		}

		double Train(vector<double> input, vector<double> &desired, double TrainingRate, double Momentum)
		{
			// Parameter Validation
			if (input.size() != inputSize)
				throw ("Ivalid input parameter", "input");
			if (desired.size() != layerSize[layerCount - 1])
				throw ("Invalid input parameter", "desired");

			// Local variable
			double error = 0.0, sum = 0.0, weightDelta = 0.0, biasDelta = 0.0;

			vector <double> output;
			output.resize(layerSize[layerCount - 1]);

			//Run the network
			Run(input, output);

			// Back-propagate the error
			for (int l = layerCount - 1; l >= 0; l--)
			{
				//Output layer
				if (l == layerCount - 1)
				{
					for (int k = 0; k<layerSize[l]; k++)
					{
						delta[l][k] = output[k] - desired[k];
						error += pow(delta[l][k], 2);
						delta[l][k] *= TransferFunctions::EvaluateDerivative(transferFunction[l],
							layerInput[l][k]);
					}
				}
				else //Hidden layer
				{
					for (int i = 0; i < layerSize[l]; i++)
					{
						sum = 0.0;
						for (int j = 0; j < layerSize[l + 1]; j++)
						{
							sum += weight[l + 1][i][j] * delta[l + 1][j];
						}
						sum *= TransferFunctions::EvaluateDerivative(transferFunction[l], layerInput[l][i]);

						delta[l][i] = sum;
					}
				}
			}

			//Update the weights and biases
			for (int l = 0; l < layerCount; l++)
				for (int i = 0; i < (l == 0 ? inputSize : layerSize[l - 1]); i++)
					for (int j = 0; j<layerSize[l]; j++)
					{
						weightDelta = TrainingRate * delta[l][j] * (l == 0 ? input[i] : layerOutput[l - 1][i])
							+ Momentum * previousWeightDelta[l][i][j];
						weight[l][i][j] -= weightDelta;

						previousWeightDelta[l][i][j] = weightDelta;
					}
			for (int l = 0; l < layerCount; l++)
				for (int i = 0; i<layerSize[l]; i++)
				{
					biasDelta = TrainingRate * delta[l][i] + Momentum * previousBiasDelta[l][i];
					bias[l][i] -= biasDelta;

					previousBiasDelta[l][i] = biasDelta;
				}
			return error;
		}

		#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { return nullptr; }
		#define XMLCheckResultForNull(a_eResult) if(!a_eResult) { return nullptr; }
		/*
		Return a Neural Network created according to file
		*/

		static NeuralNetwork *LoadFromFile(const char* filePath)
		{
			tinyxml2::XMLDocument xmlDoc;
			XMLCheckResult(xmlDoc.LoadFile(filePath));

			tinyxml2::XMLNode * pRoot = xmlDoc.FirstChild();
			XMLCheckResultForNull(pRoot);
		}

		#undef XMLCheckResult
		#define XMLCheckResult(a_eResult) if (a_eResult != tinyxml2::XML_SUCCESS) { return false; }

		/*
		Save Network to XML file
		*/
		bool SaveToFile(const char* filePath)
		{
			tinyxml2::XMLDocument xmlDoc;
			XMLCheckResult(xmlDoc.SaveFile(filePath));

			tinyxml2::XMLNode * pRoot = xmlDoc.NewElement("BPNeuralNetwork");
			xmlDoc.InsertFirstChild(pRoot);
			tinyxml2::XMLElement * nameElement = xmlDoc.NewElement("Name");
			nameElement->SetText(Name.c_str());
			pRoot->InsertFirstChild(nameElement);



		}

		void getInvolvedData(vector<vector<vector<double>>> &_weight, vector<vector<double>> &_bias, vector<int> &_layerSize, vector<TransferFunction> &_transferFunction)
		{
			_weight = weight;
			_bias = bias;		
			_layerSize = Actual_layerSize;
			_transferFunction = Actual_transferFunction;
		}

		void setInvolvedData(vector<vector<vector<double>>> _weight, vector<vector<double>> _bias)
		{
			weight = _weight;
			bias = _bias;			
		}

#pragma endregion

#pragma region Public data

	public:
		string Name = "Default";

#pragma endregion

#pragma region Private data

	private:
		int layerCount;
		int inputSize;
		vector<int> layerSize;
		vector<TransferFunction> transferFunction;

		vector<vector<double>> layerOutput;
		vector<vector<double>> layerInput;
		vector<vector<double>> bias;
		vector<vector<double>> delta;
		vector<vector<double>> previousBiasDelta;

		vector<vector<vector<double>>> weight;
		vector<vector<vector<double>>> previousWeightDelta;

		vector<int> Actual_layerSize;
		vector<TransferFunction> Actual_transferFunction;
		vector<vector<vector<double>>> Actual_weight;

#pragma endregion

	};

}