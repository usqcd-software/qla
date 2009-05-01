/* QLA test code */
/* for indexed tensor routines */

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <libgen.h>

extern int test_tensor_idx1(FILE *fp);
extern int test_tensor_idx2(FILE *fp);
extern int test_tensor_idx3(FILE *fp);
extern int test_tensor_idx4(FILE *fp);

int
main(int argc, char* argv[])
{
  char name[64];
  FILE *fp;

  char *test_program_name= basename(argv[0]); 
  test_program_name = strcat(test_program_name, ".result");
  if (NULL == (fp = fopen(test_program_name,"w"))) {
    fprintf(stderr, "Error in report function - cannot create \"%s\"\n", test_program_name);
    exit(-1);
  }

  test_tensor_idx1(fp);
  test_tensor_idx2(fp);
  test_tensor_idx3(fp);
  test_tensor_idx4(fp);

  return 0;
}
