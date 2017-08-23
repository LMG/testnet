#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nnet.h"

// mutate: slightly tweak values of the network at random
// *net*: the net to mutate
// *chance*: chance that a single value is tweaked in %
// *deviation*: max deviation of a single value
void mutate(NNet* net, double chance, double deviation)
{
  for(int i=0; i<net->size; i++)
  {
      printf("mutate?\n");
    for(int j=0; j<net->neurons[i]->nbInputs; j++)
    {
      if(doubleRandom(0,100)<chance)
      {
        double change = doubleRandom(-deviation, deviation);
        printf("%f\n", change);
        net->neurons[i]->weights[j] += change;
      }
    }
  }
}

// generation: a group of *population* neural networks
//  with associated fitness ranking
typedef struct Generation {
  int population;
  NNet** nets;
  double* rankings;
} Generation;

// Creates a new generation with *pop* random networks
//  each of size *size*, with *inputs* inputs and *outputs* outputs
Generation* initGeneration(int pop, int size, int inputs, int outputs)
{
  Generation* out = malloc(sizeof(Generation));
  out->population = pop;
  out->nets = malloc(sizeof(NNet)*pop);
  for(int i=0; i<pop; i++)
  {
    out->nets[i] = initNet(size, inputs, outputs);
    populate(out->nets[i]);
  }
  out->rankings = malloc(sizeof(double)*pop);

  return out;
}

void cleanGeneration(Generation* gen) {
  free(gen->rankings);
  for(int i=0; i<gen->population; i++)
  {
    cleanNet(gen->nets[i]);
  }
  free(gen->nets);
  free(gen);
}

// run:
//          run the simulation for each network until it stabilizes with *inputs*
//          then calculate its fitness using *fitness*
void run(Generation* gen, double* inputs, double* fitness(double* output))
{
  for(int i=0; i<gen->population; i++)
  {
    double* output = runNet(gen->nets[i], inputs);
    gen->rankings[i] = (*fitness)(output);
  }
}

// evolve: 
//          pick the best *best* elements and clone them to make a new generation 
//          then mutate all the newly created elements
//          returns: the new generation
Generation* evolve(Generation* gen, int best)
{
  Generation* out=initGeneration(gen->population, 
                                  gen->nets[0]->size, 
                                  gen->nets[0]->inputs,
                                  gen->nets[0]->outputs);
  for(int i=0; i<best; i++)
  {
    for(int j=0; j<gen->population/best; j++)
    {
      out[i*j]=copyNet(gen->nets[i]);
      mutate(out[i*j]);
    }
  }

  return out;
}


int main(char argc, char* argv[])
{
  Generation* gen = initGeneration(100, 100, 30, 1);
  
  cleanGeneration(gen);
  return EXIT_SUCCESS;
}
