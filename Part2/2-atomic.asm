#
# 2-2-atomic.asm
#
# An assembly file generated by 2-2-atomic.asm
# PLEASE REFER TO THE LINE 39 FOR THE CRITICAL SECTION 
#
# @author: karu-rress
#
	
	.text
	.globl	counter
	.bss
	.align 4
	.type	counter, @object
	.size	counter, 4
counter:
	.zero	4
	.text
	.globl	add
	.type	add, @function
add:
.LFB0:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%rdi, -40(%rbp)
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -12(%rbp)
	jmp	.L2
.L3: # NOTE: modified some code for clearer understanding
	movl	$1, %eax # Now register eax has 1
# # # # # # IMPORTANT: THE CRITICAL SECTION # # # # # #
	lock xaddl	%eax, counter(%rip) # Add 1(=eax) to counter (and store the old value in eax)
# # # # # # THE END OF THE CRITICAL SECTION # # # # # #
	addl	%edx, %eax
	movl	%eax, -16(%rbp)
	addl	$1, -12(%rbp)
.L2:
	cmpl	$999999, -12(%rbp)
	jle	.L3
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L5
	call	__stack_chk_fail@PLT
.L5:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE0:
	.size	add, .-add
	.section	.rodata
.LC0:
	.string	"Counter: %d\n"
	.text
	.globl	main
	.type	main, @function
main:
.LFB1:
	.cfi_startproc
	pushq	%rbp
	.cfi_def_cfa_offset 16
	.cfi_offset 6, -16
	movq	%rsp, %rbp
	.cfi_def_cfa_register 6
	subq	$48, %rsp
	movq	%fs:40, %rax
	movq	%rax, -8(%rbp)
	xorl	%eax, %eax
	movl	$0, -40(%rbp)
	jmp	.L7
.L8:
	leaq	-32(%rbp), %rax
	movl	-40(%rbp), %edx
	movslq	%edx, %rdx
	salq	$3, %rdx
	addq	%rdx, %rax
	movl	$0, %ecx
	leaq	add(%rip), %rdx
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_create@PLT
	addl	$1, -40(%rbp)
.L7:
	cmpl	$1, -40(%rbp)
	jle	.L8
	movl	$0, -36(%rbp)
	jmp	.L9
.L10:
	movl	-36(%rbp), %eax
	cltq
	movq	-32(%rbp,%rax,8), %rax
	movl	$0, %esi
	movq	%rax, %rdi
	call	pthread_join@PLT
	addl	$1, -36(%rbp)
.L9:
	cmpl	$1, -36(%rbp)
	jle	.L10
	movl	counter(%rip), %eax
	movl	%eax, -44(%rbp)
	movl	-44(%rbp), %eax
	movl	%eax, %esi
	leaq	.LC0(%rip), %rax
	movq	%rax, %rdi
	movl	$0, %eax
	call	printf@PLT
	movl	$0, %eax
	movq	-8(%rbp), %rdx
	subq	%fs:40, %rdx
	je	.L12
	call	__stack_chk_fail@PLT
.L12:
	leave
	.cfi_def_cfa 7, 8
	ret
	.cfi_endproc
.LFE1:
	.size	main, .-main
	.ident	"GCC: (GNU) 14.2.1 20240910"
	.section	.note.GNU-stack,"",@progbits