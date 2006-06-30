.set r0,0; .set SP,1; .set RTOC,2; .set r3,3; .set r4,4
.set r5,5; .set r6,6; .set r7,7; .set r8,8; .set r9,9
.set r10,10; .set r11,11; .set r12,12; .set r13,13; .set r14,14
.set r15,15; .set r16,16; .set r17,17; .set r18,18; .set r19,19
.set r20,20; .set r21,21; .set r22,22; .set r23,23; .set r24,24
.set r25,25; .set r26,26; .set r27,27; .set r28,28; .set r29,29
.set r30,30; .set r31,31
.set fp0,0; .set fp1,1; .set fp2,2; .set fp3,3; .set fp4,4
.set fp5,5; .set fp6,6; .set fp7,7; .set fp8,8; .set fp9,9
.set fp10,10; .set fp11,11; .set fp12,12; .set fp13,13; .set fp14,14
.set fp15,15; .set fp16,16; .set fp17,17; .set fp18,18; .set fp19,19
.set fp20,20; .set fp21,21; .set fp22,22; .set fp23,23; .set fp24,24
.set fp25,25; .set fp26,26; .set fp27,27; .set fp28,28; .set fp29,29
.set fp30,30; .set fp31,31
.set MQ,0; .set XER,1; .set FROM_RTCU,4; .set FROM_RTCL,5; .set FROM_DEC,6
.set LR,8; .set CTR,9; .set TID,17; .set DSISR,18; .set DAR,19; .set TO_RTCU,20
.set TO_RTCL,21; .set TO_DEC,22; .set SDR_0,24; .set SDR_1,25; .set SRR_0,26
.set SRR_1,27
.set BO_dCTR_NZERO_AND_NOT,0; .set BO_dCTR_NZERO_AND_NOT_1,1
.set BO_dCTR_ZERO_AND_NOT,2; .set BO_dCTR_ZERO_AND_NOT_1,3
.set BO_IF_NOT,4; .set BO_IF_NOT_1,5; .set BO_IF_NOT_2,6
.set BO_IF_NOT_3,7; .set BO_dCTR_NZERO_AND,8; .set BO_dCTR_NZERO_AND_1,9
.set BO_dCTR_ZERO_AND,10; .set BO_dCTR_ZERO_AND_1,11; .set BO_IF,12
.set BO_IF_1,13; .set BO_IF_2,14; .set BO_IF_3,15; .set BO_dCTR_NZERO,16
.set BO_dCTR_NZERO_1,17; .set BO_dCTR_ZERO,18; .set BO_dCTR_ZERO_1,19
.set BO_ALWAYS,20; .set BO_ALWAYS_1,21; .set BO_ALWAYS_2,22
.set BO_ALWAYS_3,23; .set BO_dCTR_NZERO_8,24; .set BO_dCTR_NZERO_9,25
.set BO_dCTR_ZERO_8,26; .set BO_dCTR_ZERO_9,27; .set BO_ALWAYS_8,28
.set BO_ALWAYS_9,29; .set BO_ALWAYS_10,30; .set BO_ALWAYS_11,31
.set CR0_LT,0; .set CR0_GT,1; .set CR0_EQ,2; .set CR0_SO,3
.set CR1_FX,4; .set CR1_FEX,5; .set CR1_VX,6; .set CR1_OX,7
.set CR2_LT,8; .set CR2_GT,9; .set CR2_EQ,10; .set CR2_SO,11
.set CR3_LT,12; .set CR3_GT,13; .set CR3_EQ,14; .set CR3_SO,15
.set CR4_LT,16; .set CR4_GT,17; .set CR4_EQ,18; .set CR4_SO,19
.set CR5_LT,20; .set CR5_GT,21; .set CR5_EQ,22; .set CR5_SO,23
.set CR6_LT,24; .set CR6_GT,25; .set CR6_EQ,26; .set CR6_SO,27
.set CR7_LT,28; .set CR7_GT,29; .set CR7_EQ,30; .set CR7_SO,31
.set TO_LT,16; .set TO_GT,8; .set TO_EQ,4; .set TO_LLT,2; .set TO_LGT,1

# r3 - r6 r8 r9 r10 r11 r23 r24 r25 r30
# r4 - r6 r8 r9 r10 r12 r23 r27 r28 r31
# r5 - r7 - r11 - r26
# r7 - r11 r29

.set w0,0;.set w1,8;.set w2,16;.set w3,24;.set w4,32;.set w5,40;.set w6,48
.set w7,56;.set w8,64;.set w9,72;.set w12,96
.set wm1,-8;.set wm2,-16;.set wm3,-24;.set wm4,-32;.set wm7,-56

	.file	"qla/reloop/QLA_F3_V_vpeq_M_times_pV.c"
	.globl	QLA_F3_V_vpeq_M_times_pV
	.type	QLA_F3_V_vpeq_M_times_pV,@function
#	.size	QLA_F3_V_vpeq_M_times_pV,768

	.section	".text"
	.align	3
.The_CodeLC:
QLA_F3_V_vpeq_M_times_pV:
	or	r12,SP,SP
	addi	r0,r0,-16
	stwu	SP,-112(SP)
	.long 0x7fec07dc
	.long 0x7fcc07dc
	.long 0x7fac07dc
	.long 0x7f8c07dc
	stw	r31,44(SP)
	stw	r30,40(SP)
	stw	r29,36(SP)
	stw	r28,32(SP)
	stw	r27,28(SP)
	stw	r26,24(SP)
	stw	r25,20(SP)
	stw	r24,16(SP)
	stw	r23,12(SP)
	cmpi	0,0,r6,0
	addi	r5,r5,-4
	bc	BO_IF_NOT,CR0_GT,CL.47
	lwzu	r7,4(r5)
	addi	r9,r0,w0
	addi	r8,r0,w1
	.long 0x7c234b1c
	addi	r10,r0,w3
	.long 0x7c044b1c
	addi	r11,r0,w2
	mtspr	CTR,r6
	addi	r6,r0,w6
	.long 0x7fe03b1c
	.long 0x7c63431c
	addi	r9,r0,w4
	.long 0x7d24531c
	addi	r10,r0,w7
	.long 0x7c435b1c
	.long 0x7d04331c
	.long 0x103f083a
	.long 0x7ce4431c
	.long 0x7cc44b1c
	.long 0x10bf1a7a
	.long 0x7c84531c
	.long 0x115f123a
	.long 0x19f0824
	bc	BO_dCTR_ZERO,CR0_LT,CL.28
	addi	r11,r0,w1
	addi	r10,r0,w3
	.long 0x5f2a64
	.long 0x7c275b1c
	addi	r12,r0,w9
	.long 0x7c63531c
	.long 0x11f5224
	lwzu	r11,4(r5)
	addi	r31,r0,w12
	.long 0x7da4631c
	.long 0x7d24fb1c
	.long 0x100161fa
	addi	r30,r0,w5
	.long 0x104111ba
	.long 0x7fe05b1c
	addi	r29,r0,w2
	addi	r4,r4,w9
	.long 0x13c1413a
	addi	r27,r0,wm4
	addi	r28,r0,wm7
	.long 0x101e4
	addi	r23,r0,wm1
	.long 0x7ca34b1c
	.long 0x119f1b7a
	.long 0x7d43f31c
	.long 0x38111a4
	.long 0x7d04331c
	.long 0x3a1f124
	.long 0x7d67eb1c
	addi	r10,r0,w7
	.long 0x7c64e31c
	or	r7,r11,r11
	.long 0x7c44db1c
	.long 0x10bf2a7a
	.long 0x7c24bb1c
	.long 0x115f523a
	.long 0x7ce4431c
	.long 0x19f6364
	.long 0x7cc44b1c
	.long 0x100b00fa
	.long 0x7c84531c
	.long 0x13cbe0ba
	.long 0x11abe87a
	bc	BO_dCTR_ZERO,CR0_LT,CL.29
	addi	r11,r0,w1
	addi	r25,r0,wm3
	addi	r24,r0,wm2
CL.30:	
	.long 0x3bf2a64
	.long 0x7f83331c
	.long 0xbf5224
	lwzu	r26,4(r5)
	.long 0x6b00e4
	.long 0x7c04631c
	.long 0x14bf0a4
	.long 0x7c475b1c
	.long 0x2b6864
	.long 0x7d03531c
	.long 0x7d24fb1c
	addi	r3,r3,w3
	.long 0x7fe0d31c
	addi	r4,r4,w9
	.long 0x7c63cf1c
	.long 0x106261fa
	.long 0x7d43c71c
	.long 0x1162e9ba
	.long 0x7c23bf1c
	.long 0x1022293a
	.long 0x119fe03a
	.long 0x7d43f31c
	.long 0x10bf427a
	.long 0x7d04331c
	.long 0x1a219e4
	.long 0x7c64e31c
	.long 0x3c259a4
	.long 0x7d67eb1c
	.long 0x3a20924
	.long 0x7c44db1c
	.long 0x115f523a
	.long 0x7c24bb1c
	.long 0x19f6024
	.long 0x7ce4431c
	.long 0x100b68fa
	.long 0x7cc44b1c
	.long 0x13cbf0ba
	.long 0x7c84531c
	.long 0x11abe87a
	or	r7,r26,r26
	bc	BO_dCTR_NZERO,CR0_LT,CL.30
CL.29:	
	addi	r3,r3,w3
	.long 0xb00e4
	addi	r24,r0,wm2
	.long 0x4bf0a4
	addi	r25,r0,wm3
	.long 0x2b6864
	.long 0x7c03cf1c
	.long 0x7c43c71c
	.long 0x7c23bf1c
CL.28:	
	.long 0x7f2a64
	addi	r11,r0,w1
	addi	r28,r0,wm7
	.long 0x15f5224
	addi	r29,r0,w2
	.long 0x7ca75b1c
	addi	r27,r0,wm4
	addi	r4,r4,w9
	addi	r23,r0,wm1
	.long 0x7c24e31c
	addi	r12,SP,32
	.long 0x7c07eb1c
	.long 0x7c44db1c
	.long 0x112561fa
	addi	r0,r0,16
	.long 0x110519ba
	.long 0x7f8c03dc
	.long 0x1145513a
	addi	r3,r3,w3
	.long 0x7c64bb1c
	addi	r25,r0,wm3
	addi	r24,r0,wm2
	.long 0xe549e4
	lwz	r26,24(SP)
	.long 0xc541a4
	.long 0x7fac03dc
	.long 0x1055124
	lwz	r27,28(SP)
	lwz	r28,32(SP)
	lwz	r29,36(SP)
	.long 0x10a0387a
	.long 0x7fcc03dc
	.long 0x108030ba
	lwz	r30,40(SP)
	.long 0x10c040fa
	lwz	r31,44(SP)
	.long 0x7fec03dc
	.long 0x202864
	.long 0x4020a4
	.long 0x30e4
	.long 0x7c23cf1c
	.long 0x7c43c71c
	.long 0x7c03bf1c
	lwz	r24,16(SP)
	lwz	r23,12(SP)
	lwz	r25,20(SP)
	addi	SP,SP,112
	bclr	BO_ALWAYS,CR0_LT
CL.47:	
	addi	SP,SP,112
	bclr	BO_ALWAYS,CR0_LT
