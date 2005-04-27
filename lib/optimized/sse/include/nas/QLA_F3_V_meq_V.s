;
; QLA_F3_V_meq_V( QLA_F3_ColorVector *aa, QLA_F3_ColorVector *bb )
;

global QLA_F3_V_meq_V
QLA_F3_V_meq_V:
	push	ebp
	mov	ebp,esp
	push	eax
	push	ebx
	mov	eax,[ebp+8]	; *aa
	mov	ebx,[ebp+12]	; *bb

	movups	xmm0,[eax]	; <(aa)->c[0]>
	movups	xmm2,[ebx]	; <(bb)->c[0]>
	movlps	xmm1,[eax+16]	; <(aa)->c[2]>
	subps	xmm0,xmm2	; t
	shufps	xmm1,xmm1,0x44
	movlps	xmm3,[ebx+16]	; <(bb)->c[2]>
	shufps	xmm3,xmm3,0x44
	movups	[eax],xmm0	; <(aa)->c[0]>
	subps	xmm1,xmm3
	movlps	[eax+16],xmm1	; <(aa)->c[2]>

here:	pop	ebx
	pop	eax
	mov	esp,ebp
	pop	ebp
	ret
