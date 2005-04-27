;
; QLA_F3_V_eq_Ma_times_V( QLA_F3_ColorVector *aa, QLA_F3_ColorMatrix *bb, QLA_F3_ColorVector *cc )
; mult_adj_su3_mat_vec( su3_matrix *a, su3_vector *b, su3_vector *c)
;

global QLA_F3_V_eq_Ma_times_V
QLA_F3_V_eq_Ma_times_V:
	push	ebp
	mov	ebp,esp
	push	eax
	push	ebx
	push	ecx
	mov	eax,[ebp+8]	; *aa
	mov	ebx,[ebp+12]	; *bb
	mov	ecx,[ebp+16]	; *cc

	;  bring in real and imaginary c vector
	movlps	xmm0,[ecx]	; x,x,c0i,c0r	<(cc)->c[0]>
	movlps	xmm1,[ecx+8]	; x,x,c1i,c1r	<(cc)->c[1]>
	movlps	xmm2,[ecx+16]	; x,x,c2i,c2r	<(cc)->c[2]>
	shufps	xmm0,xmm0,0x44	; c0i,c0r,c0i,c0r
	shufps	xmm1,xmm1,0x44	; c1i,c1r,c1i,c1r
	shufps	xmm2,xmm2,0x44	; c2i,c2r,c2i,c2r

	; bring in real components of first two rows of matrix b
	movss	xmm3,[ebx]	; x,x,x,b00r	<(bb)->e[0][0].real>
	movss	xmm7,[ebx+8]	; x,x,x,b10r	<(bb)->e[0][1].real>
	shufps	xmm3,xmm7,0x00	; b10r,b10r,b00r,b00r
	movss	xmm4,[ebx+24]	; x,x,x,b01r	<(bb)->e[1][0].real>
	movss	xmm7,[ebx+32]	; x,x,x,b11r	<(bb)->e[1][1].real>
	shufps	xmm4,xmm7,0x00	; b11r,b11r,b01r,b01r
	mulps	xmm3,xmm0
	mulps	xmm4,xmm1
	addps	xmm3,xmm4
	movss	xmm5,[ebx+48]	; x,x,x,b02r	<(bb)->e[2][0].real>
	movss	xmm7,[ebx+56]	; x,x,x,b12r	<(bb)->e[2][1].real>
	shufps	xmm5,xmm7,0x00	; b12r,b12r,b02r,b02r
	mulps	xmm5,xmm2
	addps	xmm3,xmm5

	; special handling of the 3rd row of matrix b
	shufps	xmm1,xmm0,0x44	; c0i,c0r,c1i,c1r
	movss	xmm7,[ebx+16]	; x,x,x,b20r	<(bb)->e[0][2].real>
	movss	xmm6,[ebx+40]	; x,x,x,b21r	<(bb)->e[1][2].real>
	shufps	xmm6,xmm7,0x00	; b20r,b20r,b21r,b21r
	mulps	xmm6,xmm1

	; shuffle c vector for imaginary components of matrix b
	shufps		xmm0,xmm0,0xB1			; c0r,c0i,c0r,c0i
	xorps		xmm0,[negate]			; c0r,-c0i,c0r,-c0i	<_sse_sgn24>
	shufps		xmm1,xmm1,0x11			; c1r,c1i,c1r,c1i
	xorps		xmm1,[negate]			; c1r,-c1i,c1r,-c1i	<_sse_sgn24>
	shufps		xmm2,xmm2,0xB1			; c2r,c2i,c2r,c2i
	xorps		xmm2,[negate]			; c2r,-c2i,c2r,-c2i	<_sse_sgn24>

	; bring in imaginary components of first two rows of matrix b
	movss		xmm4,[ebx+4]			; x,x,x,b00i		<(bb)->e[0][0].imag>
	movss		xmm7,[ebx+12]			; x,x,x,b10i		<(bb)->e[0][1].imag>
	shufps		xmm4,xmm7,0x00			; b10i,b10i,b00i,b00i
	mulps		xmm4,xmm0
	addps		xmm3,xmm4
	movss		xmm5,[ebx+28]			; x,x,x,b01i		<(bb)->e[1][0].imag>
	movss		xmm7,[ebx+36]			; x,x,x,b11i		<(bb)->e[1][1].imag>
	shufps		xmm5,xmm7,0x00			; b11i,b11i,b01i,b01i
	mulps		xmm5,xmm1
	addps		xmm3,xmm5
	movss		xmm5,[ebx+52]			; x,x,x,b02i		<(bb)->e[2][0].imag>
	movss		xmm7,[ebx+60]			; x,x,x,b12i		<(bb)->e[2][1].imag>
	shufps		xmm5,xmm7,0x00			; b12i,b12i,b02i,b02i
	mulps		xmm5,xmm2
	addps		xmm3,xmm5			; a1i,a1r,a0i,a0r
	movups		[eax],xmm3			; store result		<(aa)->c[0]>

	; more special handling of the 3rd row of matrix b
	shufps		xmm1,xmm0,0x44			; c0r,-c0i,c1r,-c1i
	movss		xmm7,[ebx+20]			; x,x,x,b20i		<(bb)->e[0][2].imag>
	movss		xmm5,[ebx+44]			; x,x,x,b21i		<(bb)->e[1][2].imag>
	shufps		xmm5,xmm7,0x00			; b20i,b20i,b21i,b21i
	mulps		xmm5,xmm1
	addps		xmm6,xmm5
	shufps		xmm2,xmm2,0xB4			; -c2i,c2r,c2r,-c2i
	xorps		xmm2,[neg2]			; c2i,c2r,c2r,-c2i	<_sse_sgn3>
	movlps		xmm7,[ebx+64]			; x,x,b22i,b22r		<(bb)->e[2][2]>
	shufps		xmm7,xmm7,0x05			; b22r,b22r,b22i,b22i
	mulps		xmm7,xmm2
	addps		xmm6,xmm7
	movaps		xmm7,xmm6
	shufps		xmm7,xmm7,0xEE
	addps		xmm6,xmm7
	movlps		[eax+16],xmm6			;			<(aa)->c[2]>

	; *******************************************************************	

here:	pop	ecx
	pop	ebx
	pop	eax
	mov	esp,ebp
	pop	ebp
	ret

	align		16
negate:	dd		0x00000000
	dd		0x80000000
	dd		0x00000000
	dd		0x80000000

	align		16
neg2:   dd		0x00000000
	dd		0x00000000
	dd		0x80000000
	dd		0x00000000
