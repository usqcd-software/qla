        .section	".text"
	.align 2
	.globl  QLA_F3_V_veq_M_times_pV
	.type   QLA_F3_V_veq_M_times_pV,@function
QLA_F3_V_veq_M_times_pV:
	mr	%r7,	%r3	; dest
	mr	%r3,	%r6	; n
	mr	%r6,	%r5	; srcvec
	mr	%r5,	%r4	; srcmat
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
	li   16,	0
	stfd    14,     112(%r1)
	li   17,	32
	stfd    15,     120(%r1)
	li   18,	64
	stfd    16,     128(%r1)
	li   19,	96
	stfd    17,     136(%r1)
	li   20,	128
	li   21,	160
	stfd    18,     144(%r1)
	li   22,	192
	li   23,	224
	stfd    19,     152(%r1)
	li   24,	256
	li   25,	288
	stfd    20,     160(%r1)
	li   26,	320
	li   27,	16
	stfd    21,     168(%r1)
	li   28,	48
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

	addi	%r3,	%r3,	1
	srawi.	%r3,	%r3,	1
	bf gt,  lab0

	lfs	   12,  0(%r5)
	lfs	   13,  4(%r5)
	lfs	   14,  8(%r5)
	lfs	   15,  12(%r5)
	lfs        18,  24(%r5)
        lfs        19,  28(%r5)
	lfs        20,  32(%r5)
	lfs        21,  36(%r5)
	lfs        24,  48(%r5)
	lfs        25,  52(%r5)
	lfs        26,  56(%r5)
	lfs        27,  60(%r5)

	lwz     %r12, 0(%r6)
	lwz     %r11, 4(%r6)
	addi	%r14, %r7, 0
	addi	%r13, %r7, 24

	add     %r29, %r5, %r16

	lfs	   0,	0(%r12)
	lfs        1,	4(%r12)
	lfs        2,	8(%r12)
	lfs        3,	12(%r12)

	mr	%r10,	%r13
	addi	%r29, %r29, 208
	subic.	%r3,	%r3,	1
	bf gt,	lab2

lab1:
	fmuls     6, 12,  0
	dcbt     %r16,   %r29
	fmuls     7, 12,  1
	lwz	%r30, 8(%r6)
	fmuls     8, 18,  0

	fmuls     9, 18,  1
	addi	%r9, %r7, 48
	fmuls    10, 24,  0

	fmuls    11, 24,  1
	lfs	20,  32(%r5)
	fnmsubs   6, 13,  1,  6
	dcbt     %r17,   %r29
	fmadds    7, 13,  0,  7
	lfs        21,  36(%r5)
	fnmsubs   8, 19,  1,  8
	lfs        26,  56(%r5)
	fmadds    9, 19,  0,  9
        lfs        27,  60(%r5)
	fnmsubs  10, 25,  1, 10
	dcbt     %r18,   %r29
	fmadds   11, 25,  0, 11
	lfs        4,   16(%r12)
	mr       %r13,   %r10

	fmadds    6, 14,  2,  6
	lfs        5,   20(%r12)
	fmadds    7, 14,  3,  7

	fmadds    8, 20,  2,  8
	lfs        16,  16(%r5)
	fmadds    9, 20,  3,  9
	dcbt     %r16,   %r30
	fmadds   10, 26,  2, 10
	lfs        17,  20(%r5)
	fmadds   11, 26,  3, 11
	dcbt     %r17,   %r30
	fnmsubs   6, 15,  3,  6
	lfs        22,  40(%r5)
	fmadds    7, 15,  2,  7

	fnmsubs   8, 21,  3,  8
	lfs        23,  44(%r5)
	fmadds    9, 21,  2,  9
	dcbt     %r19,   %r29
	fnmsubs  10, 27,  3, 10
	lfs        28,  64(%r5)
	fmadds   11, 27,  2, 11

	fmadds    6, 16,  4,  6
	lfs        29,  68(%r5)
	fmadds    7, 16,  5,  7

	fmadds    8, 22,  4,  8
	lfs        0,   0(%r11)
	fmadds    9, 22,  5,  9
	dcbt     %r20,   %r29
	fmadds   10, 28,  4, 10
	lfs        1,   4(%r11)
	fmadds   11, 28,  5, 11

	fnmsubs   6, 17,  5,  6
	lfs        12,  72(%r5)
	fmadds    7, 17,  4,  7

	fnmsubs   8, 23,  5,  8
	lfs        13,  76(%r5)
	fmadds    9, 23,  4,  9
	lfs        18,  96(%r5)
	fnmsubs  10, 29,  5, 10
	lfs        19,  100(%r5)
	fmadds   11, 29,  4, 11
	lfs        24,  120(%r5)
	mr       %r12,   %r30
	stfs       6,   0(%r14)
        subic.	%r3,	%r3,	1
	lfs        25,  124(%r5)
	stfs       7,   4(%r14)
	lfs        2,   8(%r11)
	stfs       8,   8(%r14)
	lfs        3,   12(%r11)
	stfs       9,   12(%r14)
	lfs        14,  80(%r5)
	stfs       10,  16(%r14)
	lfs        15,  84(%r5)
	stfs       11,  20(%r14)
	fmuls     6, 12,  0
	dcbt     %r21,   %r29
	fmuls     7, 12,  1
	lwz     %r31, 12(%r6)
	fmuls     8, 18,  0

	fmuls     9, 18,  1
	addi	%r10, %r7, 72
	fmuls    10, 24,  0

	fmuls    11, 24,  1
	lfs        20,  104(%r5)
	fnmsubs   6, 13,  1,  6
	dcbt     %r22,   %r29
	fmadds    7, 13,  0,  7
	lfs        21,  108(%r5)
	fnmsubs   8, 19,  1,  8
	lfs        26,  128(%r5)
	fmadds    9, 19,  0,  9
	lfs        27,  132(%r5)
	fnmsubs  10, 25,  1, 10
	dcbt     %r23,   %r29
	fmadds   11, 25,  0, 11
	lfs        4,   16(%r11)
	mr       %r14,   %r9

	fmadds    6, 14,  2,  6
	lfs        5,   20(%r11)
	fmadds    7, 14,  3,  7

	fmadds    8, 20,  2,  8
	lfs        16,  88(%r5)
	fmadds    9, 20,  3,  9
	dcbt     %r27,   %r31
	fmadds   10, 26,  2, 10
	lfs        17,  92(%r5)
	fmadds   11, 26,  3, 11

	fnmsubs   6, 15,  3,  6
	lfs        22,  112(%r5)
	fmadds    7, 15,  2,  7

	fnmsubs   8, 21,  3,  8
	lfs        23,  116(%r5)
	fmadds    9, 21,  2,  9
	dcbt     %r24,   %r29
	fnmsubs  10, 27,  3, 10
	lfs        28,  136(%r5)
	fmadds   11, 27,  2, 11

	fmadds    6, 16,  4,  6
	lfs        29,  140(%r5)
	fmadds    7, 16,  5,  7

	fmadds    8, 22,  4,  8
	lfs        0,   0(%r12)
	fmadds    9, 22,  5,  9
	dcbt     %r25,   %r29
	fmadds   10, 28,  4, 10
	lfs        1,   4(%r12)
	fmadds   11, 28,  5, 11

	fnmsubs   6, 17,  5,  6
	lfs        12,  144(%r5)
	fmadds    7, 17,  4,  7

	fnmsubs   8, 23,  5,  8
	lfs        13,  148(%r5)
	fmadds    9, 23,  4,  9
	lfs        18,  168(%r5)
	fnmsubs  10, 29,  5, 10
	lfs        19,  172(%r5)
	fmadds   11, 29,  4, 11

	lfs        24,  192(%r5)
	mr       %r11,   %r31
	stfs       6,   0(%r13)
	lfs	25,  196(%r5)
	stfs       7,   4(%r13)
	lfs        2,   8(%r12)
	stfs       8,   8(%r13)

	addi %r29, %r29, 144
	lfs        3,   12(%r12)
	stfs       9,   12(%r13)
	lfs        14,  152(%r5)
	stfs       10,  16(%r13)
	lfs        15,  156(%r5)
	stfs       11,  20(%r13)
	addi %r5, %r5, 144
	addi %r6, %r6, 8
	addi %r7, %r7, 48
	bf gt,  lab2
	b  lab1
lab2:
	fmuls     6, 12,  0

	fmuls     7, 12,  1
	lwz     %r30, 8(%r6)
	fmuls     8, 18,  0

	fmuls     9, 18,  1
	addi	%r9, %r7, 48
	fmuls    10, 24,  0

	fmuls    11, 24,  1
	lfs        20,  32(%r5)
	fnmsubs   6, 13,  1,  6

	fmadds    7, 13,  0,  7
	lfs        21,  36(%r5)
	fnmsubs   8, 19,  1,  8
	lfs        26,  56(%r5)
	fmadds    9, 19,  0,  9
	lfs        27,  60(%r5)
	fnmsubs  10, 25,  1, 10

	fmadds   11, 25,  0, 11
	lfs        4,   16(%r12)
	mr       %r13,   %r10

	fmadds    6, 14,  2,  6
	lfs        5,   20(%r12)
	fmadds    7, 14,  3,  7

	fmadds    8, 20,  2,  8
	lfs        16,  16(%r5)
	fmadds    9, 20,  3,  9

	fmadds   10, 26,  2, 10
	lfs        17,  20(%r5)
	fmadds   11, 26,  3, 11

	fnmsubs   6, 15,  3,  6
	lfs        22,  40(%r5)
	fmadds    7, 15,  2,  7

	fnmsubs   8, 21,  3,  8
	lfs        23,  44(%r5)
	fmadds    9, 21,  2,  9

	fnmsubs  10, 27,  3, 10
	lfs        28,  64(%r5)
	fmadds   11, 27,  2, 11

	fmadds    6, 16,  4,  6
	lfs        29,  68(%r5)
	fmadds    7, 16,  5,  7

	fmadds    8, 22,  4,  8
	lfs        0,   0(%r11)
	fmadds    9, 22,  5,  9

	fmadds   10, 28,  4, 10
	lfs        1,   4(%r11)
	fmadds   11, 28,  5, 11

	fnmsubs   6, 17,  5,  6
	lfs        12,  72(%r5)
	fmadds    7, 17,  4,  7

	fnmsubs   8, 23,  5,  8
	lfs        13,  76(%r5)
	fmadds    9, 23,  4,  9

	fnmsubs  10, 29,  5, 10
	lfs        18,  96(%r5)
	fmadds   11, 29,  4, 11

	mr       %r12,   %r30
	lfs        19,  100(%r5)
	subic.	3,	3,	1

	lfs        24,  120(%r5)
	stfs       6,   0(%r14)
	lfs        25,  124(%r5)
	stfs       7,   4(%r14)
	lfs        2,   8(%r11)
	stfs       8,   8(%r14)
	lfs        3,   12(%r11)
	stfs       9,   12(%r14)
	lfs        14,  80(%r5)
	stfs       10,  16(%r14)
	lfs        15,  84(%r5)
	stfs       11,  20(%r14)
	fmuls     6, 12,  0

	fmuls     7, 12,  1
	lwz     %r31, 12(%r6)
	fmuls     8, 18,  0

	fmuls     9, 18,  1
	addi	%r10, %r7, 72
	fmuls    10, 24,  0

	fmuls    11, 24,  1
	lfs        20,  104(%r5)
	fnmsubs   6, 13,  1,  6

	fmadds    7, 13,  0,  7
	lfs        21,  108(%r5)
	fnmsubs   8, 19,  1,  8

	lfs        26,  128(%r5)
	add     %r10, %r10, %r7

	fmadds    9, 19,  0,  9
	lfs        27,  132(%r5)
	fnmsubs  10, 25,  1, 10

	fmadds   11, 25,  0, 11
	lfs        4,   16(%r11)
	mr       %r14,   %r9

	fmadds    6, 14,  2,  6
	lfs        5,   20(%r11)
	fmadds    7, 14,  3,  7

	fmadds    8, 20,  2,  8
	lfs        16,  88(%r5)
	fmadds    9, 20,  3,  9

	fmadds   10, 26,  2, 10
	lfs        17,  92(%r5)
	fmadds   11, 26,  3, 11

	fnmsubs   6, 15,  3,  6
	lfs        22,  112(%r5)
	fmadds    7, 15,  2,  7

	fnmsubs   8, 21,  3,  8
	lfs        23,  116(%r5)
	fmadds    9, 21,  2,  9

	fnmsubs  10, 27,  3, 10
	lfs        28,  136(%r5)
	fmadds   11, 27,  2, 11

	fmadds    6, 16,  4,  6
	lfs        29,  140(%r5)
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

	stfs       6,   0(%r13)
	stfs       7,   4(%r13)
	stfs       8,   8(%r13)
	stfs       9,   12(%r13)
	stfs       10,  16(%r13)
	stfs       11,  20(%r13)

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
