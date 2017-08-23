#ifndef DEF_INCLUDE_NNET
#define DEF_INCLUDE_NNET
#include <stdio.h>
#include <stdlib.h>

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
Neuron* initNeuron (int in);

// Initialize a neural network of 
// size *size*, with *inputs* inputs and
// *outputs* outputs.
// assert: inputs + outputs <= size
NNet* initNet (int size, int inputs, int outputs);

// Free the neuron memory
void cleanNeuron (Neuron* n);

// Free the net memory
void cleanNet (NNet* n);

// Randomly populate a network *n*
void populate (NNet* n);

// Sigmoid function
double sigmoid (double x, double lambda);

// Compute a tick for a neural net
// with inputs *inputs
// assert: size of array == net inputs
void tick(NNet* n, double inputs[]);

// Returns the output of the neural network
double* getOut(NNet* n);

#endif
