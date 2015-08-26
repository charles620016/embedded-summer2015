	.syntax unified
	.arch armv7-a
	.eabi_attribute 27, 3
	.eabi_attribute 28, 1
	.fpu vfpv3-d16
	.eabi_attribute 20, 1
	.eabi_attribute 21, 1
	.eabi_attribute 23, 3
	.eabi_attribute 24, 1
	.eabi_attribute 25, 1
	.eabi_attribute 26, 2
	.eabi_attribute 30, 6
	.eabi_attribute 34, 1
	.eabi_attribute 18, 4
	.thumb
	.file	"clz_benchmark.c"
	.text
	.align	2
	.global	clz1
	.thumb
	.thumb_func
	.type	clz1, %function
clz1:
	@ args = 0, pretend = 0, frame = 16
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #20
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	cmp	r3, #0
	bne	.L2
	movs	r3, #32
	b	.L3
.L2:
	movs	r3, #1
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #16
	cmp	r3, #0
	bne	.L4
	ldr	r3, [r7, #12]
	adds	r3, r3, #16
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #16
	str	r3, [r7, #4]
.L4:
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #24
	cmp	r3, #0
	bne	.L5
	ldr	r3, [r7, #12]
	adds	r3, r3, #8
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #8
	str	r3, [r7, #4]
.L5:
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #28
	cmp	r3, #0
	bne	.L6
	ldr	r3, [r7, #12]
	adds	r3, r3, #4
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #4
	str	r3, [r7, #4]
.L6:
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #30
	cmp	r3, #0
	bne	.L7
	ldr	r3, [r7, #12]
	adds	r3, r3, #2
	str	r3, [r7, #12]
	ldr	r3, [r7, #4]
	lsls	r3, r3, #2
	str	r3, [r7, #4]
.L7:
	ldr	r3, [r7, #4]
	asrs	r3, r3, #31
	ldr	r2, [r7, #12]
	add	r3, r3, r2
	str	r3, [r7, #12]
	ldr	r3, [r7, #12]
.L3:
	mov	r0, r3
	adds	r7, r7, #20
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	clz1, .-clz1
	.align	2
	.global	clz2
	.thumb
	.thumb_func
	.type	clz2, %function
clz2:
	@ args = 0, pretend = 0, frame = 8
	@ frame_needed = 1, uses_anonymous_args = 0
	@ link register save eliminated.
	push	{r7}
	sub	sp, sp, #12
	add	r7, sp, #0
	str	r0, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #1
	ldr	r2, [r7, #4]
	orrs	r3, r3, r2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #2
	ldr	r2, [r7, #4]
	orrs	r3, r3, r2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #4
	ldr	r2, [r7, #4]
	orrs	r3, r3, r2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #8
	ldr	r2, [r7, #4]
	orrs	r3, r3, r2
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r3, r3, #16
	ldr	r2, [r7, #4]
	orrs	r3, r3, r2
	str	r3, [r7, #4]
	ldr	r2, [r7, #4]
	mov	r3, r2
	lsls	r3, r3, #3
	subs	r3, r3, r2
	lsls	r2, r3, #8
	subs	r2, r2, r3
	lsls	r3, r2, #8
	subs	r3, r3, r2
	lsls	r2, r3, #8
	subs	r3, r2, r3
	str	r3, [r7, #4]
	ldr	r3, [r7, #4]
	lsrs	r2, r3, #26
	movw	r3, #:lower16:table.4729
	movt	r3, #:upper16:table.4729
	ldrb	r3, [r3, r2]	@ zero_extendqisi2
	mov	r0, r3
	adds	r7, r7, #12
	mov	sp, r7
	@ sp needed
	ldr	r7, [sp], #4
	bx	lr
	.size	clz2, .-clz2
	.section	.rodata
	.align	2
.LC0:
	.ascii	"clz1() : %lf sec\012\000"
	.align	2
.LC1:
	.ascii	"clz2() : %lf sec\012\000"
	.text
	.align	2
	.global	main
	.thumb
	.thumb_func
	.type	main, %function
main:
	@ args = 0, pretend = 0, frame = 24
	@ frame_needed = 1, uses_anonymous_args = 0
	push	{r7, lr}
	sub	sp, sp, #24
	add	r7, sp, #0
	bl	clock
	str	r0, [r7, #8]
	movs	r3, #0
	str	r3, [r7, #4]
	b	.L11
.L12:
	ldr	r0, [r7, #4]
	bl	clz1
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L11:
	ldr	r3, [r7, #4]
	cmp	r3, #-1
	bne	.L12
	bl	clock
	str	r0, [r7, #12]
	bl	clock
	str	r0, [r7, #16]
	movs	r3, #0
	str	r3, [r7, #4]
	b	.L13
.L14:
	ldr	r0, [r7, #4]
	bl	clz2
	ldr	r3, [r7, #4]
	adds	r3, r3, #1
	str	r3, [r7, #4]
.L13:
	ldr	r3, [r7, #4]
	cmp	r3, #-1
	bne	.L14
	bl	clock
	str	r0, [r7, #20]
	ldr	r2, [r7, #12]
	ldr	r3, [r7, #8]
	subs	r3, r2, r3
	fmsr	s15, r3	@ int
	fsitod	d6, s15
	fldd	d7, .L16
	fdivd	d7, d6, d7
	movw	r0, #:lower16:.LC0
	movt	r0, #:upper16:.LC0
	fmrrd	r2, r3, d7
	bl	printf
	ldr	r2, [r7, #20]
	ldr	r3, [r7, #16]
	subs	r3, r2, r3
	fmsr	s15, r3	@ int
	fsitod	d6, s15
	fldd	d7, .L16
	fdivd	d7, d6, d7
	movw	r0, #:lower16:.LC1
	movt	r0, #:upper16:.LC1
	fmrrd	r2, r3, d7
	bl	printf
	movs	r3, #0
	mov	r0, r3
	adds	r7, r7, #24
	mov	sp, r7
	@ sp needed
	pop	{r7, pc}
.L17:
	.align	3
.L16:
	.word	0
	.word	1093567616
	.size	main, .-main
	.data
	.align	2
	.type	table.4729, %object
	.size	table.4729, 64
table.4729:
	.byte	32
	.byte	31
	.byte	0
	.byte	16
	.byte	0
	.byte	30
	.byte	3
	.byte	0
	.byte	15
	.byte	0
	.byte	0
	.byte	0
	.byte	29
	.byte	10
	.byte	2
	.byte	0
	.byte	0
	.byte	0
	.byte	12
	.byte	14
	.byte	21
	.byte	0
	.byte	19
	.byte	0
	.byte	0
	.byte	28
	.byte	0
	.byte	25
	.byte	0
	.byte	9
	.byte	1
	.byte	0
	.byte	17
	.byte	0
	.byte	4
	.byte	0
	.byte	0
	.byte	0
	.byte	11
	.byte	0
	.byte	13
	.byte	22
	.byte	20
	.byte	0
	.byte	26
	.byte	0
	.byte	0
	.byte	18
	.byte	5
	.byte	0
	.byte	0
	.byte	23
	.byte	0
	.byte	27
	.byte	0
	.byte	6
	.byte	0
	.byte	24
	.byte	7
	.byte	0
	.byte	8
	.byte	0
	.byte	0
	.byte	0
	.ident	"GCC: (Ubuntu/Linaro 4.8.2-16ubuntu4) 4.8.2"
	.section	.note.GNU-stack,"",%progbits
