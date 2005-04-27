        .section	".text"
	.align 2
	.globl  QLA_F3_V_vpeq_M_times_pV
	.type   QLA_F3_V_vpeq_M_times_pV,@function
QLA_F3_V_vpeq_M_times_pV:
	la  %r1,	-864(%r1)
	stw	%r14,	368(%r1)
	stw	%r15,	376(%r1)
	stw	%r16,	384(%r1)
	stw	%r17,	392(%r1)
	stw	%r18,	400(%r1)
	stw	%r19,	408(%r1)
	stw	%r20,	416(%r1)
	stw	%r21,	424(%r1)
	stw	%r22,	432(%r1)
	stw	%r23,	440(%r1)
	stw	%r24,	448(%r1)
	stw	%r25,	456(%r1)
	stw	%r26,	464(%r1)
	stw	%r27,	472(%r1)
	stw	%r28,	480(%r1)
	stw	%r29,	488(%r1)
	stw	%r30,	496(%r1)
	stw	%r31,	504(%r1)
	stfd    14,     112(%r1)
	stfd    15,     120(%r1)
	stfd    16,     128(%r1)
	stfd    17,     136(%r1)
	stfd    18,     144(%r1)
	stfd    19,     152(%r1)
	stfd    20,     160(%r1)
	stfd    21,     168(%r1)
	stfd    22,     176(%r1)
	stfd    23,     184(%r1)
	stfd    24,     192(%r1)
	stfd    25,     200(%r1)
	stfd    26,     208(%r1)
	stfd    27,     216(%r1)
	stfd    28,     224(%r1)
	stfd    29,     232(%r1)
	stfd    30,     240(%r1)
	stfd    31,     248(%r1)

	addi	%r7,	%r6,	1
	srawi.	%r7,	%r7,	1
	bf gt,  lab0

	lwz     %r8, 0(%r5)
	lwz     %r9, 4(%r5)

	lfs	   0,	0(%r8)
	lfs        1,	4(%r8)
	lfs        2,	8(%r8)
	lfs        3,	12(%r8)

	lfs	   12,  0(%r4)
	lfs	   13,  4(%r4)
	lfs	   14,  8(%r4)
	lfs	   15,  12(%r4)
	lfs        18,  24(%r4)
        lfs        19,  28(%r4)
	lfs        24,  48(%r4)
	lfs        25,  52(%r4)

	lfs	   30,	0(%r3)
	lfs	   31,	4(%r3)
	lfs	   26,	8(%r3)
	lfs	   27,	12(%r3)
	lfs	   16,	16(%r3)
	lfs	   17,	20(%r3)

	li   16,	0
	li   17,	32
	li   18,	64
	li   19,	96
	li   20,	128
	li   27,	16
	li   28,	48
	li   26,	72
	li   25,	88

	addi	%r29, %r4, 176
	subic.	%r7,  %r7, 1
	bf gt,	lab2

lab1:
	lwz	%r30, 8(%r5)
	fmadds	  6, 12,  0, 30
	fmadds	  7, 12,  1, 31
	dcbt     %r16,   %r29
	lfs	   20,  32(%r4)
	fmadds	  8, 18,  0, 26
	fmadds	  9, 18,  1, 27
	lfs        21,  36(%r4)
	fmadds	 10, 24,  0, 16
	fmadds	 11, 24,  1, 17

	lfs        26,  56(%r4)
        lfs        27,  60(%r4)
	fnmsubs   6, 13,  1,  6
	fmadds    7, 13,  0,  7
	lfs        4,   16(%r8)
	dcbt     %r28,   %r3
	fnmsubs   8, 19,  1,  8
	fmadds    9, 19,  0,  9
	lfs        5,   20(%r8)
	fnmsubs  10, 25,  1, 10
	fmadds   11, 25,  0, 11

	lfs        16,  16(%r4)
	fmadds    6, 14,  2,  6
	fmadds    7, 14,  3,  7
	dcbt     %r26,   %r3
	lfs        17,  20(%r4)
	fmadds    8, 20,  2,  8
	fmadds    9, 20,  3,  9
	lfs        22,  40(%r4)
	lfs        23,  44(%r4)
	fmadds   10, 26,  2, 10
	fmadds   11, 26,  3, 11
	lfs        28,  64(%r4)

	lfs        29,  68(%r4)
	fnmsubs   6, 15,  3,  6
	fmadds    7, 15,  2,  7
	lfs        12,  72(%r4)
	dcbt     %r17,   %r29
	fnmsubs   8, 21,  3,  8
	lfs        13,  76(%r4)
	fmadds    9, 21,  2,  9
	fnmsubs  10, 27,  3, 10
	lfs        18,  96(%r4)
	fmadds   11, 27,  2, 11

	lfs        19,  100(%r4)
	fmadds    6, 16,  4,  6
	fmadds    7, 16,  5,  7
	lfs        0,   0(%r9)
	fmadds    8, 22,  4,  8
	fmadds    9, 22,  5,  9
	lfs        1,   4(%r9)
	dcbt     %r16,   %r30
	fmadds   10, 28,  4, 10
	lfs        2,   8(%r9)
	fmadds   11, 28,  5, 11

	lfs        3,   12(%r9)
	fnmsubs   6, 17,  5,  6
	fmadds    7, 17,  4,  7
	lfs	   30,	24(%r3)
	fnmsubs   8, 23,  5,  8
	lfs	   31,	28(%r3)
	fmadds    9, 23,  4,  9
	dcbt     %r18,   %r29
	fnmsubs  10, 29,  5, 10
	lfs	   26,	32(%r3)
	lfs	   27,	36(%r3)
	fmadds   11, 29,  4, 11

	mr       %r8,   %r30
	lfs	   16,	40(%r3)
	stfs       6,   0(%r3)
        subic.	%r7,	%r7,	1
	lfs	   17,	44(%r3)
	stfs       7,   4(%r3)
	lfs        24,  120(%r4)
	stfs       8,   8(%r3)
	lfs        25,  124(%r4)
	stfs       9,   12(%r3)
	fmadds	  30, 12,  0, 30
	lfs        14,  80(%r4)
	stfs       10,  16(%r3)
	fmadds	  31, 12,  1, 31
	lfs        15,  84(%r4)
	stfs       11,  20(%r3)

	lwz     %r31, 12(%r5)
	fmadds	  8, 18,  0, 26
	lfs        20,  104(%r4)
	fmadds	  9, 18,  1, 27
	lfs        21,  108(%r4)
	fmadds	 10, 24,  0, 16
	fmadds	 11, 24,  1, 17

	lfs        26,  128(%r4)
	dcbt     %r19,   %r29
	fnmsubs   6, 13,  1,  30
	fmadds    7, 13,  0,  31
	lfs        27,  132(%r4)
	fnmsubs   8, 19,  1,  8
	fmadds    9, 19,  0,  9
	lfs        4,   16(%r9)
	fnmsubs  10, 25,  1, 10
	fmadds   11, 25,  0, 11

	lfs        5,   20(%r9)
	dcbt     %r16,   %r31
	fmadds    6, 14,  2,  6
	fmadds    7, 14,  3,  7
	lfs        16,  88(%r4)
	fmadds    8, 20,  2,  8
	fmadds    9, 20,  3,  9
	lfs        17,  92(%r4)
	fmadds   10, 26,  2, 10
	fmadds   11, 26,  3, 11

	lfs        22,  112(%r4)
	dcbt     %r27,   %r31
	fnmsubs   6, 15,  3,  6
	fmadds    7, 15,  2,  7
	lfs        23,  116(%r4)
	fnmsubs   8, 21,  3,  8
	fmadds    9, 21,  2,  9
	lfs        28,  136(%r4)
	lfs        29,  140(%r4)
	fnmsubs  10, 27,  3, 10
	fmadds   11, 27,  2, 11

	lfs        0,   0(%r8)
	fmadds    6, 16,  4,  6
	fmadds    7, 16,  5,  7
	lfs        1,   4(%r8)
	fmadds    8, 22,  4,  8
	fmadds    9, 22,  5,  9
	lfs        2,   8(%r8)
	fmadds   10, 28,  4, 10
	fmadds   11, 28,  5, 11
	lfs        3,   12(%r8)

	fnmsubs   6, 17,  5,  6
	lfs        12,  144(%r4)
	lfs        13,  148(%r4)
	fmadds    7, 17,  4,  7
	fnmsubs   8, 23,  5,  8
	dcbt     %r20,   %r29
	lfs        18,  168(%r4)
	lfs        19,  172(%r4)
	fmadds    9, 23,  4,  9
	lfs	   30,	48(%r3)
	lfs	   31,	52(%r3)
	fnmsubs  10, 29,  5, 10
	fmadds   11, 29,  4, 11
	lfs	   26,	56(%r3)

	stfs       6,   24(%r3)
	lfs	   27,	60(%r3)
	mr       %r9,   %r31
	stfs       7,   28(%r3)
	lfs	   16,	64(%r3)
	stfs       8,   32(%r3)
	lfs	   17,	68(%r3)
	stfs       9,   36(%r3)
	lfs        24,  192(%r4)
	stfs       10,  40(%r3)
	addi %r5, %r5, 8
	lfs 	   25,  196(%r4)
	stfs       11,  44(%r3)

	addi %r29, %r29, 144
	lfs        14,  152(%r4)
	addi %r3, %r3, 48
	lfs        15,  156(%r4)
	addi %r4, %r4, 144

	bt gt,  lab1
lab2:
	fmadds	  6, 12,  0, 30
	fmadds	  7, 12,  1, 31
	lfs        20,  32(%r4)
	fmadds	  8, 18,  0, 26
	fmadds	  9, 18,  1, 27
	lfs        21,  36(%r4)
	fmadds	 10, 24,  0, 16
	fmadds	 11, 24,  1, 17

	lfs        26,  56(%r4)
	fnmsubs   6, 13,  1,  6
	fmadds    7, 13,  0,  7
	lfs        27,  60(%r4)
	fnmsubs   8, 19,  1,  8
	fmadds    9, 19,  0,  9
	lfs        4,   16(%r8)
	fnmsubs  10, 25,  1, 10
	fmadds   11, 25,  0, 11

	lfs        5,   20(%r8)
	fmadds    6, 14,  2,  6
	fmadds    7, 14,  3,  7
	lfs        16,  16(%r4)
	fmadds    8, 20,  2,  8
	fmadds    9, 20,  3,  9
	lfs        17,  20(%r4)
	fmadds   10, 26,  2, 10
	fmadds   11, 26,  3, 11

	lfs        22,  40(%r4)
	fnmsubs   6, 15,  3,  6
	fmadds    7, 15,  2,  7
	lfs        23,  44(%r4)
	fnmsubs   8, 21,  3,  8
	fmadds    9, 21,  2,  9
	lfs        28,  64(%r4)
	fnmsubs  10, 27,  3, 10
	fmadds   11, 27,  2, 11

	lfs        29,  68(%r4)
	fmadds    6, 16,  4,  6
	fmadds    7, 16,  5,  7
	fmadds    8, 22,  4,  8
	fmadds    9, 22,  5,  9
	fmadds   10, 28,  4, 10
	fmadds   11, 28,  5, 11

	fnmsubs   6, 17,  5,  6
	fmadds    7, 17,  4,  7
	fnmsubs   8, 23,  5,  8
	fmadds    9, 23,  4,  9
	fnmsubs  10, 29,  5, 10
	fmadds   11, 29,  4, 11

	andi.	%r6, %r6, 1
	stfs       6,   0(%r3)
	stfs       7,   4(%r3)
	stfs       8,   8(%r3)
	stfs       9,   12(%r3)
	stfs       10,  16(%r3)
	stfs       11,  20(%r3)

	bt gt, lab0

	lfs        0,   0(%r9)
	lfs        1,   4(%r9)
	lfs	   30,	24(%r3)
	lfs	   31,	28(%r3)
	lfs        12,  72(%r4)
	lfs        13,  76(%r4)

	lfs	   26,	32(%r3)
	lfs	   27,	36(%r3)
	lfs        18,  96(%r4)
	lfs        19,  100(%r4)

	lfs	   16,	40(%r3)
	lfs	   17,	44(%r3)

	fmadds	  6, 12,  0, 30
	fmadds	  7, 12,  1, 31
	lfs        24,  120(%r4)
	lfs        25,  124(%r4)
	fmadds	  8, 18,  0, 26
	fmadds	  9, 18,  1, 27
	lfs        2,   8(%r9)
	lfs        3,   12(%r9)
	fmadds	 10, 24,  0, 16
	fmadds   11, 24,  1, 17
	lfs        14,  80(%r4)
	lfs        15,  84(%r4)

	lfs        20,  104(%r4)
	fnmsubs   6, 13,  1,  6
	fmadds    7, 13,  0,  7
	lfs        21,  108(%r4)
	fnmsubs   8, 19,  1,  8
	lfs        26,  128(%r4)
	fmadds    9, 19,  0,  9
	lfs        27,  132(%r4)
	fnmsubs  10, 25,  1, 10
	fmadds   11, 25,  0, 11

	lfs        4,   16(%r9)
	fmadds    6, 14,  2,  6
	lfs        5,   20(%r9)
	fmadds    7, 14,  3,  7
	fmadds    8, 20,  2,  8
	lfs        16,  88(%r4)
	fmadds    9, 20,  3,  9
	fmadds   10, 26,  2, 10
	lfs        17,  92(%r4)
	fmadds   11, 26,  3, 11

	fnmsubs   6, 15,  3,  6
	lfs        22,  112(%r4)
	fmadds    7, 15,  2,  7
	fnmsubs   8, 21,  3,  8
	lfs        23,  116(%r4)
	fmadds    9, 21,  2,  9
	fnmsubs  10, 27,  3, 10
	lfs        28,  136(%r4)
	fmadds   11, 27,  2, 11

	fmadds    6, 16,  4,  6
	lfs        29,  140(%r4)
	fmadds    7, 16,  5,  7
	fmadds    8, 22,  4,  8
	fmadds    9, 22,  5,  9
	fmadds   10, 28,  4, 10
	fmadds   11, 28,  5, 11

	fnmsubs   6, 17,  5,  6
	fmadds    7, 17,  4,  7
	fnmsubs   8, 23,  5,  8
	fmadds    9, 23,  4,  9
	fnmsubs  10, 29,  5, 10
	fmadds   11, 29,  4, 11

	stfs       6,   24(%r3)
	stfs       7,   28(%r3)
	stfs       8,   32(%r3)
	stfs       9,   36(%r3)
	stfs       10,  40(%r3)
	stfs       11,  44(%r3)

lab0:
	lwz     %r14,   368(%r1)
	lwz     %r15,   376(%r1)
	lwz     %r16,   384(%r1)
	lwz     %r17,   392(%r1)
	lwz     %r18,   400(%r1)
	lwz     %r19,   408(%r1)
	lwz     %r20,   416(%r1)
	lwz     %r21,   424(%r1)
	lwz     %r22,   432(%r1)
	lwz     %r23,   440(%r1)
	lwz     %r24,   448(%r1)
	lwz     %r25,   456(%r1)
	lwz     %r26,   464(%r1)
	lwz     %r27,   472(%r1)
	lwz     %r28,   480(%r1)
	lwz     %r29,   488(%r1)
	lwz     %r30,   496(%r1)
	lwz     %r31,   504(%r1)
	lfd     14,     112(%r1)
	lfd     15,     120(%r1)
	lfd     16,     128(%r1)
	lfd     17,     136(%r1)
	lfd     18,     144(%r1)
	lfd     19,     152(%r1)
	lfd     20,     160(%r1)
	lfd     21,     168(%r1)
	lfd     22,     176(%r1)
	lfd     23,     184(%r1)
	lfd     24,     192(%r1)
	lfd     25,     200(%r1)
	lfd     26,     208(%r1)
	lfd     27,     216(%r1)
	lfd     28,     224(%r1)
	lfd     29,     232(%r1)
	lfd     30,     240(%r1)
	lfd     31,     248(%r1)
	la   %r1,       864(%r1)
	blr
