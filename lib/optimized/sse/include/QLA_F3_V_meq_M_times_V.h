#define QLA_F3_V_meq_M_times_V(aa,bb,cc) \
{ \
__asm__ __volatile__ ("movups %0, %%xmm0" \
                      : \
                      : \
                      "m" (*(cc))); \
__asm__ __volatile__ ("movups %0, %%xmm1" \
                      : \
                      : \
                      "m" (*(bb))); \
__asm__ __volatile__ ("movups %0, %%xmm2" \
                      : \
                      : \
                      "m" (*(bb))); \
__asm__ __volatile__ ("movlps %0, %%xmm4" \
                      : \
                      : \
                      "m" (*(((char *)cc)+16))); \
__asm__ __volatile__ ("movups %0, %%xmm5" \
                      : \
                      : \
                      "m" (*(((char *)bb)+16))); \
__asm__ __volatile__ ("movups %0, %%xmm6" \
                      : \
                      : \
                      "m" (*(((char *)bb)+16))); \
__asm__ __volatile__ ("mulps %%xmm0, %%xmm1 \n\t" \
                      "movlhps %%xmm0, %%xmm4 \n\t" \
                      "shufps $0xB1, %%xmm2, %%xmm2 \n\t" \
                      "mulps %%xmm0, %%xmm2 \n\t" \
                      "movaps %%xmm1, %%xmm3 \n\t" \
                      "movlhps %%xmm2, %%xmm3 \n\t" \
                      "mulps %%xmm4, %%xmm5 \n\t" \
                      "shufps $0xB1, %%xmm6, %%xmm6 \n\t" \
                      "mulps %%xmm4, %%xmm6 \n\t" \
                      "movhlps %%xmm1, %%xmm2 \n\t" \
                      "addps %%xmm2, %%xmm3 \n\t" \
                      "shufps $0x4E, %%xmm4, %%xmm4 \n\t" \
                      "movhlps %%xmm0, %%xmm4 \n\t" \
                      "movups %0, %%xmm1" \
                      : \
                      : \
                      "m" (*(((char *)bb)+32))); \
__asm__ __volatile__ ("mulps %%xmm4, %%xmm1 \n\t" \
                      "movups %0, %%xmm2" \
                      : \
                      : \
                      "m" (*(((char *)bb)+32))); \
__asm__ __volatile__ ("shufps $0xB1, %%xmm2, %%xmm2 \n\t" \
                      "mulps %%xmm4, %%xmm2 \n\t" \
                      "movaps %%xmm5, %%xmm7 \n\t" \
                      "movlhps %%xmm6, %%xmm5 \n\t" \
                      "movhlps %%xmm7, %%xmm6 \n\t" \
                      "movaps %%xmm1, %%xmm7 \n\t" \
                      "addps %%xmm5, %%xmm3 \n\t" \
                      "movlhps %%xmm2, %%xmm7 \n\t" \
                      "movhlps %%xmm1, %%xmm2 \n\t" \
                      "addps %%xmm2, %%xmm7 \n\t" \
                      "shufps $0xBE, %%xmm4, %%xmm4 \n\t" \
                      "movups %0, %%xmm2" \
                      : \
                      : \
                      "m" (*(((char *)bb)+48))); \
__asm__ __volatile__ ("addps %%xmm6, %%xmm7 \n\t" \
                      "movaps %%xmm3, %%xmm1 \n\t" \
                      "shufps $0xDD, %%xmm7, %%xmm3 \n\t" \
                      "xorps %0, %%xmm3" \
                      : \
                      : \
                      "m" (_sse_sgn13)); \
__asm__ __volatile__ ("shufps $0x88, %%xmm7, %%xmm1 \n\t" \
                      "movups %0, %%xmm5" \
                      : \
                      : \
                      "m" (*(((char *)bb)+48))); \
__asm__ __volatile__ ("addps %%xmm3, %%xmm1 \n\t" \
                      "movlps %0, %%xmm6" \
                      : \
                      : \
                      "m" (*(((char *)bb)+64))); \
__asm__ __volatile__ ("mulps %%xmm0, %%xmm2 \n\t" \
                      "shufps $0xB1, %%xmm5, %%xmm5 \n\t" \
                      "mulps %%xmm0, %%xmm5 \n\t" \
                      "movlhps %%xmm6, %%xmm6 \n\t" \
                      "mulps %%xmm4, %%xmm6 \n\t" \
                      "movaps %%xmm2, %%xmm0 \n\t" \
                      "movlhps %%xmm5, %%xmm2 \n\t" \
                      "movhlps %%xmm0, %%xmm5 \n\t" \
                      "addps %%xmm2, %%xmm6 \n\t" \
                      "movups %0, %%xmm3" \
                      : \
                      : \
                      "m" (*(aa))); \
__asm__ __volatile__ ("addps %%xmm5, %%xmm6 \n\t" \
                      "movaps %%xmm6, %%xmm7 \n\t" \
                      "shufps $0x0D, %%xmm7, %%xmm7 \n\t" \
                      "subps %%xmm1, %%xmm3 \n\t" \
                      "shufps $0x08, %%xmm6, %%xmm6 \n\t" \
                      "xorps %0, %%xmm7" \
                      : \
                      : \
                      "m" (_sse_sgn13)); \
__asm__ __volatile__ ("movlps %0, %%xmm0" \
                      : \
                      : \
                      "m" (*(((char *)aa)+16))); \
__asm__ __volatile__ ("addps %%xmm6, %%xmm7 \n\t" \
                      "movups %%xmm3, %0" \
                      : \
                      "=m" (*(aa))); \
__asm__ __volatile__ ("subps %%xmm7, %%xmm0 \n\t" \
                      "movlps %%xmm0, %0" \
                      : \
                      "=m" (*(((char *)aa)+16))); \
}
