/* QLA test code */
/* for indexed tensor routines */

extern int test_tensor_idx1(void);
extern int test_tensor_idx2(void);
extern int test_tensor_idx3(void);
extern int test_tensor_idx4(void);

int
main()
{
  test_tensor_idx1();
  test_tensor_idx2();
  test_tensor_idx3();
  test_tensor_idx4();

  return 0;
}
