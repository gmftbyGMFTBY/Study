# Author : GMFTBY
# Time   : 2017.2.28

    .file	"test.c"
	.section	.rodata.str1.1,"aMS",@progbits,1
.LC0:
	.string	"r"
.LC1:
	.string	"%d"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB2:
	.text
.LHOTB2:
	.p2align 4,,15
	.globl	read_file
	.type	read_file, @function
read_file:
.LFB41:
	.cfi_startproc
	pushq	%r13
	.cfi_def_cfa_offset 16
	.cfi_offset 13, -16
	pushq	%r12
	.cfi_def_cfa_offset 24
	.cfi_offset 12, -24
	pushq	%rbp
	.cfi_def_cfa_offset 32
	.cfi_offset 6, -32
	pushq	%rbx
	.cfi_def_cfa_offset 40
	.cfi_offset 3, -40
	movq	%rdi, %rbx
	leaq	160000(%rbx), %r13
	movq	%rsi, %rdi
	movl	$.LC0, %esi
	subq	$8, %rsp
	.cfi_def_cfa_offset 48
	call	fopen
	movq	%rax, %r12
	.p2align 4,,10
	.p2align 3
.L2:
	leaq	800(%rbx), %rbp
	.p2align 4,,10
	.p2align 3
.L3:
	movq	%rbx, %rdx
	xorl	%eax, %eax
	movl	$.LC1, %esi
	movq	%r12, %rdi
	addq	$4, %rbx
	call	__isoc99_fscanf
	cmpq	%rbx, %rbp
	jne	.L3
	cmpq	%rbp, %r13
	movq	%rbp, %rbx
	jne	.L2
	addq	$8, %rsp
	.cfi_def_cfa_offset 40
	movq	%r12, %rdi
	popq	%rbx
	.cfi_def_cfa_offset 32
	popq	%rbp
	.cfi_def_cfa_offset 24
	popq	%r12
	.cfi_def_cfa_offset 16
	popq	%r13
	.cfi_def_cfa_offset 8
	jmp	fclose
	.cfi_endproc
.LFE41:
	.size	read_file, .-read_file
	.section	.text.unlikely
.LCOLDE2:
	.text
.LHOTE2:
	.section	.rodata.str1.1
.LC3:
	.string	"../../data/matrix_a"
.LC4:
	.string	"../../data/matrix_b"
.LC5:
	.string	"%d "
	.section	.text.unlikely
.LCOLDB6:
	.section	.text.startup,"ax",@progbits
.LHOTB6:
	.p2align 4,,15
	.globl	main
	.type	main, @function
main:
.LFB42:
	.cfi_startproc
	pushq	%r12
	.cfi_def_cfa_offset 16
	.cfi_offset 12, -16
	pushq	%rbp
	.cfi_def_cfa_offset 24
	.cfi_offset 6, -24
	movl	$.LC3, %esi
	pushq	%rbx
	.cfi_def_cfa_offset 32
	.cfi_offset 3, -32
	subq	$480016, %rsp
	.cfi_def_cfa_offset 480048
	movq	%rsp, %rdi
	leaq	320000(%rsp), %rbx
	movq	%fs:40, %rax
	movq	%rax, 480008(%rsp)
	xorl	%eax, %eax
	call	read_file
	leaq	160000(%rsp), %rdi
	movl	$.LC4, %esi
	leaq	160000(%rbx), %rbp
	call	read_file
	movq	%rbx, %rdx
	xorl	%eax, %eax
.L9:
	leaq	8(%rdx), %rdi
	movq	%rdx, %rcx
	movq	$0, (%rdx)
	movq	$0, 792(%rdx)
	addq	$800, %rdx
	andq	$-8, %rdi
	subq	%rdi, %rcx
	addl	$800, %ecx
	shrl	$3, %ecx
	cmpq	%rdx, %rbp
	rep stosq
	jne	.L9
	movq	%rsp, %r8
	movq	%rbx, %rdi
.L13:
	xorl	%esi, %esi
	.p2align 4,,10
	.p2align 3
.L15:
	movdqa	(%rdi,%rsi), %xmm3
	leaq	320000(%rsp,%rsi), %rcx
	leaq	160000(%rsp,%rsi), %rax
	movq	%r8, %rdx
	.p2align 4,,10
	.p2align 3
.L11:
	movd	(%rdx), %xmm4
	addq	$800, %rax
	addq	$4, %rdx
	pshufd	$0, %xmm4, %xmm0
	movdqa	%xmm0, %xmm1
	movdqa	%xmm0, %xmm2
	movdqa	-800(%rax), %xmm0
	pmuludq	-800(%rax), %xmm1
	pshufd	$8, %xmm1, %xmm1
	cmpq	%rax, %rcx
	psrlq	$32, %xmm2
	psrlq	$32, %xmm0
	pmuludq	%xmm2, %xmm0
	pshufd	$8, %xmm0, %xmm0
	punpckldq	%xmm0, %xmm1
	paddd	%xmm1, %xmm3
	jne	.L11
	movaps	%xmm3, (%rdi,%rsi)
	addq	$16, %rsi
	cmpq	$800, %rsi
	jne	.L15
	addq	$800, %rdi
	addq	$800, %r8
	cmpq	%rdi, %rbp
	jne	.L13
.L14:
	leaq	800(%rbx), %r12
	.p2align 4,,10
	.p2align 3
.L16:
	movl	(%rbx), %edx
	xorl	%eax, %eax
	movl	$.LC5, %esi
	movl	$1, %edi
	addq	$4, %rbx
	call	__printf_chk
	cmpq	%rbx, %r12
	jne	.L16
	movl	$10, %edi
	movq	%r12, %rbx
	call	putchar
	cmpq	%r12, %rbp
	jne	.L14
	xorl	%eax, %eax
	movq	480008(%rsp), %rsi
	xorq	%fs:40, %rsi
	jne	.L26
	addq	$480016, %rsp
	.cfi_remember_state
	.cfi_def_cfa_offset 32
	popq	%rbx
	.cfi_def_cfa_offset 24
	popq	%rbp
	.cfi_def_cfa_offset 16
	popq	%r12
	.cfi_def_cfa_offset 8
	ret
.L26:
	.cfi_restore_state
	call	__stack_chk_fail
	.cfi_endproc
.LFE42:
	.size	main, .-main
	.section	.text.unlikely
.LCOLDE6:
	.section	.text.startup
.LHOTE6:
	.ident	"GCC: (Ubuntu 5.4.0-6ubuntu1~16.04.5) 5.4.0 20160609"
	.section	.note.GNU-stack,"",@progbits
