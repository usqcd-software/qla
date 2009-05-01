#define QLA_D3_V_eq_M_times_V(cc,aa,bb) \
{ \
__asm__ __volatile__ ("movupd %0, %%xmm0" \
                      : \
                      : \
                      "m" (QLA_elem_V(*bb,0))); \
__asm__ __volatile__ ("movupd %0, %%xmm1" \
                      : \
                      : \
                      "m" (QLA_elem_V(*bb,1))); \
__asm__ __volatile__ ("movupd %0, %%xmm2" \
                      : \
                      : \
                      "m" (QLA_elem_V(*bb,2))); \
__asm__ __volatile__ ("movsd %0, %%xmm3" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,0,0)))); \
__asm__ __volatile__ ("movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,0,1)))); \
__asm__ __volatile__ ("movsd %0, %%xmm4" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,1,0)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,1,2)))); \
__asm__ __volatile__ ("movsd %0, %%xmm5" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,2,0)))); \
__asm__ __volatile__ ("unpcklpd %%xmm3, %%xmm3 \n\t" \
                      "unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm4, %%xmm4 \n\t" \
                      "mulpd %%xmm0, %%xmm3 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm1, %%xmm6 \n\t" \
                      "unpcklpd %%xmm5, %%xmm5 \n\t" \
                      "mulpd %%xmm0, %%xmm4 \n\t" \
                      "addpd %%xmm6, %%xmm3 \n\t" \
                      "mulpd %%xmm2, %%xmm7 \n\t" \
                      "mulpd %%xmm0, %%xmm5 \n\t" \
                      "addpd %%xmm7, %%xmm4 \n\t" \
                      "movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,2,1)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,0,2)))); \
__asm__ __volatile__ ("unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm1, %%xmm6 \n\t" \
                      "mulpd %%xmm2, %%xmm7 \n\t" \
                      "addpd %%xmm6, %%xmm5 \n\t" \
                      "addpd %%xmm7, %%xmm3 \n\t" \
                      "movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,1,1)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_real(QLA_elem_M(*aa,2,2)))); \
__asm__ __volatile__ ("unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm1, %%xmm6 \n\t" \
                      "mulpd %%xmm2, %%xmm7 \n\t" \
                      "addpd %%xmm6, %%xmm4 \n\t" \
                      "addpd %%xmm7, %%xmm5 \n\t" \
                      "movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,0,0)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,1,1)))); \
__asm__ __volatile__ ("shufpd $0x1, %%xmm0, %%xmm0 \n\t" \
                      "shufpd $0x1, %%xmm1, %%xmm1 \n\t" \
                      "shufpd $0x1, %%xmm2, %%xmm2 \n\t" \
                      "unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "xorpd %0, %%xmm0" \
                      : \
                      : \
                      "m" (_sse_sgn2)); \
__asm__ __volatile__ ("xorpd %0, %%xmm1" \
                      : \
                      : \
                      "m" (_sse_sgn2)); \
__asm__ __volatile__ ("xorpd %0, %%xmm2" \
                      : \
                      : \
                      "m" (_sse_sgn2)); \
__asm__ __volatile__ ("mulpd %%xmm0, %%xmm6 \n\t" \
                      "mulpd %%xmm1, %%xmm7 \n\t" \
                      "addpd %%xmm6, %%xmm3 \n\t" \
                      "addpd %%xmm7, %%xmm4 \n\t" \
                      "movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,2,2)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,1,0)))); \
__asm__ __volatile__ ("unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm2, %%xmm6 \n\t" \
                      "mulpd %%xmm0, %%xmm7 \n\t" \
                      "addpd %%xmm6, %%xmm5 \n\t" \
                      "addpd %%xmm7, %%xmm4 \n\t" \
                      "movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,0,1)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,2,0)))); \
__asm__ __volatile__ ("unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm1, %%xmm6 \n\t" \
                      "mulpd %%xmm0, %%xmm7 \n\t" \
                      "addpd %%xmm6, %%xmm3 \n\t" \
                      "addpd %%xmm7, %%xmm5 \n\t" \
                      "movsd %0, %%xmm0" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,0,2)))); \
__asm__ __volatile__ ("movsd %0, %%xmm6" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,2,1)))); \
__asm__ __volatile__ ("movsd %0, %%xmm7" \
                      : \
                      : \
                      "m" (QLA_imag(QLA_elem_M(*aa,1,2)))); \
__asm__ __volatile__ ("unpcklpd %%xmm0, %%xmm0 \n\t" \
                      "unpcklpd %%xmm6, %%xmm6 \n\t" \
                      "unpcklpd %%xmm7, %%xmm7 \n\t" \
                      "mulpd %%xmm2, %%xmm0 \n\t" \
                      "mulpd %%xmm1, %%xmm6 \n\t" \
                      "mulpd %%xmm2, %%xmm7 \n\t" \
                      "addpd %%xmm0, %%xmm3 \n\t" \
                      "addpd %%xmm7, %%xmm4 \n\t" \
                      "addpd %%xmm6, %%xmm5 \n\t" \
                      "movupd %%xmm3, %0" \
                      : \
                      "=m" (QLA_elem_V(*cc,0))); \
__asm__ __volatile__ ("movupd %%xmm4, %0" \
                      : \
                      "=m" (QLA_elem_V(*cc,1))); \
__asm__ __volatile__ ("movupd %%xmm5, %0" \
                      : \
                      "=m" (QLA_elem_V(*cc,2))); \
}
