#define QLA_F3_H_eq_M_times_H(cc,aa,bb) \
{ \
__asm__ __volatile__ ("movlps %0, %%xmm0" \
                      : \
                      : \
                      "m" ((bb)->h[0].c[0])); \
__asm__ __volatile__ ("movlps %0, %%xmm1" \
                      : \
                      : \
                      "m" ((bb)->h[0].c[1])); \
__asm__ __volatile__ ("movlps %0, %%xmm2" \
                      : \
                      : \
                      "m" ((bb)->h[0].c[2])); \
__asm__ __volatile__ ("movhps %0, %%xmm0" \
                      : \
                      : \
                      "m" ((bb)->h[1].c[0])); \
__asm__ __volatile__ ("movhps %0, %%xmm1" \
                      : \
                      : \
                      "m" ((bb)->h[1].c[1])); \
__asm__ __volatile__ ("movhps %0, %%xmm2" \
                      : \
                      : \
                      "m" ((bb)->h[1].c[2])); \
__asm__ __volatile__ ("movss %0, %%xmm3" \
                      : \
                      : \
                      "m" ((aa)->e[0][0].real)); \
__asm__ __volatile__ ("movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[0][1].real)); \
__asm__ __volatile__ ("movss %0, %%xmm4" \
                      : \
                      : \
                      "m" ((aa)->e[1][0].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[1][2].real)); \
__asm__ __volatile__ ("movss %0, %%xmm5" \
                      : \
                      : \
                      "m" ((aa)->e[2][0].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm3, %%xmm3 \n\t" \
                      "shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm4, %%xmm4 \n\t" \
                      "mulps %%xmm0, %%xmm3 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm5, %%xmm5 \n\t" \
                      "mulps %%xmm0, %%xmm4 \n\t" \
                      "addps %%xmm6, %%xmm3 \n\t" \
                      "mulps %%xmm2, %%xmm7 \n\t" \
                      "mulps %%xmm0, %%xmm5 \n\t" \
                      "addps %%xmm7, %%xmm4 \n\t" \
                      "movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[2][1].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[0][2].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "mulps %%xmm2, %%xmm7 \n\t" \
                      "addps %%xmm6, %%xmm5 \n\t" \
                      "addps %%xmm7, %%xmm3 \n\t" \
                      "movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[1][1].real)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[2][2].real)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "mulps %%xmm2, %%xmm7 \n\t" \
                      "addps %%xmm6, %%xmm4 \n\t" \
                      "addps %%xmm7, %%xmm5 \n\t" \
                      "movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[0][0].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[1][1].imag)); \
__asm__ __volatile__ ("shufps $0xb1, %%xmm0, %%xmm0 \n\t" \
                      "shufps $0xb1, %%xmm1, %%xmm1 \n\t" \
                      "shufps $0xb1, %%xmm2, %%xmm2 \n\t" \
                      "shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "xorps %0, %%xmm0" \
                      : \
                      : \
                      "m" (_sse_sgn13)); \
__asm__ __volatile__ ("xorps %0, %%xmm1" \
                      : \
                      : \
                      "m" (_sse_sgn13)); \
__asm__ __volatile__ ("xorps %0, %%xmm2" \
                      : \
                      : \
                      "m" (_sse_sgn13)); \
__asm__ __volatile__ ("mulps %%xmm0, %%xmm6 \n\t" \
                      "mulps %%xmm1, %%xmm7 \n\t" \
                      "addps %%xmm6, %%xmm3 \n\t" \
                      "addps %%xmm7, %%xmm4 \n\t" \
                      "movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[2][2].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[1][0].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm2, %%xmm6 \n\t" \
                      "mulps %%xmm0, %%xmm7 \n\t" \
                      "addps %%xmm6, %%xmm5 \n\t" \
                      "addps %%xmm7, %%xmm4 \n\t" \
                      "movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[0][1].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[2][0].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "mulps %%xmm0, %%xmm7 \n\t" \
                      "addps %%xmm6, %%xmm3 \n\t" \
                      "addps %%xmm7, %%xmm5 \n\t" \
                      "movss %0, %%xmm0" \
                      : \
                      : \
                      "m" ((aa)->e[0][2].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm6" \
                      : \
                      : \
                      "m" ((aa)->e[2][1].imag)); \
__asm__ __volatile__ ("movss %0, %%xmm7" \
                      : \
                      : \
                      "m" ((aa)->e[1][2].imag)); \
__asm__ __volatile__ ("shufps $0x00, %%xmm0, %%xmm0 \n\t" \
                      "shufps $0x00, %%xmm6, %%xmm6 \n\t" \
                      "shufps $0x00, %%xmm7, %%xmm7 \n\t" \
                      "mulps %%xmm2, %%xmm0 \n\t" \
                      "mulps %%xmm1, %%xmm6 \n\t" \
                      "mulps %%xmm2, %%xmm7 \n\t" \
                      "addps %%xmm0, %%xmm3 \n\t" \
                      "addps %%xmm6, %%xmm5 \n\t" \
                      "addps %%xmm7, %%xmm4 \n\t" \
                      "movlps %%xmm3, %0" \
                      : \
                      "=m" ((cc)->h[0].c[0])); \
__asm__ __volatile__ ("movlps %%xmm4, %0" \
                      : \
                      "=m" ((cc)->h[0].c[1])); \
__asm__ __volatile__ ("movlps %%xmm5, %0" \
                      : \
                      "=m" ((cc)->h[0].c[2])); \
__asm__ __volatile__ ("movhps %%xmm3, %0" \
                      : \
                      "=m" ((cc)->h[1].c[0])); \
__asm__ __volatile__ ("movhps %%xmm4, %0" \
                      : \
                      "=m" ((cc)->h[1].c[1])); \
__asm__ __volatile__ ("movhps %%xmm5, %0" \
                      : \
                      "=m" ((cc)->h[1].c[2])); \
}
