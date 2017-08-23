#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "nnet.h"

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
