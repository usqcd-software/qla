#define QLA_F3_V_meq_Ma_times_V(aa,bb,cc) \
{ \
__asm__ __volatile__ ("movlps %0, %%xmm0" \
                      : \
                      : \
                      "m" ((cc)->c[0])); \
__asm__ __volatile__ ("movlps %0, %%xmm1" \
                      : \
                      : \
                      "m" ((cc)->c[1])); \
__asm__ __volatile__ ("movlps %0, %%xmm2" \
                      : \
                      : \
                      "m" ((cc)->c[2])); \
__asm__ __volatile__ ("shufps $0x44, %%xmm0, %%xmm0 \n\t" \
                      "shufps $0x44, %%xmm1, %%xmm1 \n\t" \
                      "shufps $0x44, %%xmm2, %%xmm2 \n\t" \
                      "movss %0, %%xmm3" \
                      : \
                      : \
                      "m" ((bb)->e[0][0].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[0][1].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm3 \n\t" \
                      "movss %0, %%xmm4" \
                      : \
                      : \
                      "m" ((bb)->e[1][0].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[1][1].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm4 \n\t" \
                      "mulps %%xmm0, %%xmm3 \n\t" \
                      "mulps %%xmm1, %%xmm4 \n\t" \
                      "addps %%xmm4, %%xmm3 \n\t" \
                      "movss %0, %%xmm5" \
                      : \
                      : \
                      "m" ((bb)->e[2][0].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[2][1].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm5 \n\t" \
                      "mulps %%xmm2, %%xmm5 \n\t" \
                      "addps %%xmm5, %%xmm3 \n\t" \
                      "shufps $0x44, %%xmm0, %%xmm1 \n\t" \
                      "movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[0][2].real)); \
__asm__ __volatile__ ("movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((bb)->e[1][2].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm6 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "shufps $0xB1, %%xmm0, %%xmm0 \n\t" \
                      "xorps %0, %%xmm0" \
                      : \
                      : \
                      "m" (_sse_sgn24)); \
__asm__ __volatile__ ("shufps $0x11, %%xmm1, %%xmm1 \n\t" \
                      "xorps %0, %%xmm1" \
                      : \
                      : \
                      "m" (_sse_sgn24)); \
__asm__ __volatile__ ("shufps $0xB1, %%xmm2, %%xmm2 \n\t" \
                      "xorps %0, %%xmm2" \
                      : \
                      : \
                      "m" (_sse_sgn24)); \
__asm__ __volatile__ ("movss %0, %%xmm4" \
                      : \
                      : \
                      "m" ((bb)->e[0][0].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[0][1].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm4 \n\t" \
                      "mulps %%xmm0, %%xmm4 \n\t" \
                      "addps %%xmm4, %%xmm3 \n\t" \
                      "movss %0, %%xmm5" \
                      : \
                      : \
                      "m" ((bb)->e[1][0].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[1][1].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm5 \n\t" \
                      "mulps %%xmm1, %%xmm5 \n\t" \
                      "addps %%xmm5, %%xmm3 \n\t" \
                      "movss %0, %%xmm5" \
                      : \
                      : \
                      "m" ((bb)->e[2][0].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[2][1].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm5 \n\t" \
                      "movups %0, %%xmm4" \
                      : \
                      : \
                      "m" ((aa)->c[0])); \
__asm__ __volatile__ ("mulps %%xmm2, %%xmm5 \n\t" \
                      "addps %%xmm5, %%xmm3 \n\t" \
                      "subps %%xmm3, %%xmm4 \n\t" \
                      "movups %%xmm4, %0" \
                      : \
                      "=m" ((aa)->c[0])); \
__asm__ __volatile__ ("shufps $0x44, %%xmm0, %%xmm1 \n\t" \
                      "movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[0][2].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm5" \
                      : \
                      : \
                      "m" ((bb)->e[1][2].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm7, %%xmm5 \n\t" \
                      "mulps %%xmm1, %%xmm5 \n\t" \
                      "addps %%xmm5, %%xmm6 \n\t" \
                      "shufps $0xB4, %%xmm2, %%xmm2 \n\t" \
                      "xorps %0, %%xmm2" \
                      : \
                      : \
                      "m" (_sse_sgn3)); \
__asm__ __volatile__ ("movlps %0, %%xmm7" \
                      : \
                      : \
                      "m" ((bb)->e[2][2])); \
__asm__ __volatile__ ("shufps $0x05, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm2, %%xmm7 \n\t" \
                      "addps %%xmm7, %%xmm6 \n\t" \
                      "movaps %%xmm6, %%xmm7 \n\t" \
                      "shufps $0xEE, %%xmm7, %%xmm7 \n\t" \
                      "movlps %0, %%xmm4" \
                      : \
                      : \
                      "m" ((aa)->c[2])); \
__asm__ __volatile__ ("addps %%xmm7, %%xmm6 \n\t" \
                      "subps %%xmm6, %%xmm4 \n\t" \
                      "movlps %%xmm4, %0" \
                      : \
                      "=m" ((aa)->c[2])); \
}
