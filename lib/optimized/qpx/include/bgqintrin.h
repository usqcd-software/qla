#include <stddef.h>
#include <qla_config.h>

#define is_aligned(p,a) ((((size_t)(p))&((size_t)(a-1)))==0)

#define foff(a,n) (((float *)(a))+(n))

#define V4D __vector4double

#define LOAD4DFA(x) vec_ld(0,x)
#define STORE4FDA(x,y) vec_st(vec_rsp(y),0,x)
#define LOADFX(x,o) vec_ld(o,x)
#define STOREFX(x,o,y) vec_st(vec_rsp(y),o,x)
#define SPLAT1DF(x) vec_splats((double)(x))

#define MUL4D(x,y) vec_mul(x,y)


#define v4loadf(a,o)      vec_ld(o,a)
#define v4storef(a,o,x)   vec_st(vec_rsp(x),o,a)
#define v4storefnr(a,o,x) vec_st(x,o,a)
#define v4load2f(a,o)     vec_ld2(o,a)

#define v4load(a,o)      vec_ld(o,a)
#define v4store(a,o,x)   vec_st(x,o,a)
#define v4storenr(a,o,x) vec_st(x,o,a)
#define v4load2(a,o)     vec_ld2(o,a)

#define v4zero(a)  vec_xor(a,a)
#define v4splat(x) vec_splats((double)(x))

#define v4add(x,y) vec_add(x,y)
#define v4sub(x,y) vec_sub(x,y)
