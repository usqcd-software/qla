/* round function */
/* This function is part of the C99 standard so should be required only
   for non C99 compilers*/

#include <math.h>

double round(double x){
  double y;

  y = floor(x);

  /* According to the standard, halfway cases round away from zero */
  if(x - y == 0.5 && y > 0) y += 1;
  else if(x - y > 0.5) y += 1.;

  return y;
}

