#include "random.h"

// Returns a random double between min and max
double doubleRandom(double min, double max)
{
  double range = max-min;
  double sub = - (min/range) * (double) RAND_MAX;
  return ((double)rand()-sub)
            / ((double)RAND_MAX/range);
}
