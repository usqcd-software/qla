/* QLA test code */
/* for indexed tensor routines */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

int test_tensor_idx1(FILE *fp, int ealign);
int test_tensor_idx2(FILE *fp, int ealign);
int test_tensor_idx3(FILE *fp, int ealign);
int test_tensor_idx4(FILE *fp, int ealign);

int
main(int argc, char* argv[])
{
  FILE *fp;
  char *fn = basename(argv[0]);
  int len = strlen(fn) + 10;
  char buf[len];
  strcpy(buf, fn);
  fn = strcat(buf, ".result");
  fp = fopen(fn, "w");
  if (fp == NULL) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", fn);
    exit(-1);
  }

  for(int i=1; i<=32; i*=2) {
    test_tensor_idx1(fp, i);
    test_tensor_idx2(fp, i);
    test_tensor_idx3(fp, i);
    test_tensor_idx4(fp, i);
  }

  return 0;
}
