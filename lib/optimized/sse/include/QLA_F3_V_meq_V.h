#define QLA_F3_V_meq_V(aa,bb) \
{ \
__asm__ __volatile__ ("movups %0, %%xmm0" \
                      : \
                      : \
                      "m" ((aa)->c[0])); \
__asm__ __volatile__ ("movups %0, %%xmm2" \
                      : \
                      : \
                      "m" ((bb)->c[0])); \
__asm__ __volatile__ ("movlps %0, %%xmm1" \
                      : \
                      : \
                      "m" ((aa)->c[2])); \
__asm__ __volatile__ ("subps %%xmm2, %%xmm0 \n\t" \
                      "shufps $0x44, %%xmm1, %%xmm1 \n\t" \
                      "movlps %0, %%xmm3" \
                      : \
                      : \
                      "m" ((bb)->c[2])); \
__asm__ __volatile__ ("shufps $0x44, %%xmm3, %%xmm3 \n\t" \
                      "movups %%xmm0, %0" \
                      : \
                      "=m" ((aa)->c[0])); \
__asm__ __volatile__ ("subps %%xmm3, %%xmm1 \n\t" \
                      "movlps %%xmm1, %0" \
                      : \
                      "=m" ((aa)->c[2])); \
}
