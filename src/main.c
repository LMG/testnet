#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// A neuron: it has a number of inputs,
// each with a weight and a neuron
// as well as a value
typedef struct Neuron {
  int nbInputs;
  double* weights;
  struct Neuron **inputs;
  double oldvalue;
  double newvalue;
} Neuron;

// A neural network is a dynamic array of
// Neurons. It has a set of input neurons 
// that's a subset of the whole network, 
// consisting of the first *inputs* neurons;
// the ouputs neurons being the end *outputs*
// ones.
typedef struct NNet {
  int size;
  Neuron **neurons;
  int inputs;
  int outputs;
} NNet;

// Initalize a neuron with *in* inputs
// Note: initializes input 
// neurons with NULL
Neuron* initNeuron (int in)
{
  Neuron* outNeuron = malloc(sizeof(Neuron));
  outNeuron->nbInputs = in;
  outNeuron->weights = malloc(sizeof(double)*in+1);
  outNeuron->inputs = malloc(sizeof(Neuron*)*in);
  outNeuron->oldvalue = 0;
  outNeuron->newvalue = 0;

  for(int i=0; i<in; i++)
  {
    outNeuron->inputs[i] = NULL;
  }

  return outNeuron;
}

// Initialize a neural network of 
// size *size*, with *inputs* inputs and
// *outputs* outputs.
// assert: inputs + outputs <= size
NNet* initNet (int size, int inputs, int outputs) {
  if(inputs+outputs>size) { exit(EXIT_FAILURE); }

  NNet* outNet = malloc(sizeof(NNet));
  outNet->size = size;
  outNet->neurons = malloc(sizeof(Neuron*)*size);
  outNet->inputs = inputs;
  outNet->outputs = outputs;

  for(int i=0; i<size; i++)
  {
    //neurons are initialized with *size* inputs
    outNet->neurons[i] = initNeuron(size);
  }
  //we connect each input to the neurons,
  // including recursively
  for(int i=0; i<size; i++)
  {
    for(int j=0; j<size; j++)
    {
      outNet->neurons[i]->inputs[j] = outNet->neurons[j];
    }
  }

  return outNet;
}

// Free the neuron memory
void cleanNeuron (Neuron* n)
{
  free(n->weights);
  free(n->inputs);
  free(n);
}


// Free the net memory
void cleanNet (NNet* n)
{
  for(int i=0; i<n->size; i++)
  {
    cleanNeuron(n->neurons[i]);
  }
  free(n->neurons);
  free(n);
}

// Randomly populate a network *n*
void populate (NNet* n)
{
  for(int i=0; i<n->size; i++)
  {
    Neuron* ne = n->neurons[i];
    for(int j=0; j<ne->nbInputs+1; j++)
    {
      //We want doubles between -1 and 1 
      double min = (double) RAND_MAX/2;
      double range = 2;
      ne->weights[j]=((double)rand()-min)
                          / ((double)RAND_MAX/range);
      printf("%f\n", ne->weights[j]);
    }
    printf("\n");
  }
}

// Sigmoid function
double sigmoid (double x, double lambda)
{
  return 1 / (1 + exp (-lambda * x));
}

// Compute a tick for a neural net
// with inputs *inputs
// assert: size of array == net inputs
void tick(NNet* n, double inputs[])
{
  //if((sizeof(inputs)/sizeof(double)!=n->inputs)){exit(EXIT_FAILURE);}

  for(int i=0; i<n->size; i++)
  {
    Neuron* ne = n->neurons[i];
    ne->newvalue = 0;
    //inputs for the input neurons
    if(i<n->inputs)
    {
      ne->newvalue += inputs[i] * ne->weights[0];
    }
    for(int j=0; j<ne->nbInputs; j++)
    {
      ne->newvalue += ne->inputs[j]->oldvalue*ne->weights[j+1];
    }
    ne->newvalue = sigmoid(ne->newvalue, 1);//TODO: check sigmoid coef
  }

  //once all the values are computed, we copy them to oldvalue
  for(int i=0; i<n->size; i++)
  {
    n->neurons[i]->oldvalue = n->neurons[i]->newvalue;
  }
}

// Returns the output of the neural network
double* getOut(NNet* n)
{
	double* out = malloc(sizeof(double)*n->outputs);
	for(int i=0; i<n->outputs; i++)
	{
    out[i] = n->neurons[n->size-i-1]->oldvalue;
	}
  return out;
}

int main(char argc, char* argv[])
{
  //iterate step by step over randomly populated 2 inputs 1 output net
  NNet* nnet1 = initNet(10, 2, 1);
  populate(nnet1);

  double inputs[2] = {0.1, 0};
  double* out = getOut(nnet1);
  while(1)
  {
    tick(nnet1, inputs);

    printf("printing net:\n");
    for(int i=0; i<nnet1->size; i++)
    {
      printf("%f\n", nnet1->neurons[i]->oldvalue);
    }

    getchar();
  }

  free(out);
  cleanNet(nnet1);
  return EXIT_SUCCESS;
}