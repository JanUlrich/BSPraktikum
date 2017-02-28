.file	"my_tsl.c"
	.section	.text.unlikely,"ax",@progbits
.LCOLDB0:
	.text
.LHOTB0:
	.p2align 4,,15
	.globl	tsl
	.type	tsl, @function
tsl:
.LFB0:
	.cfi_startproc
	xorl	%eax, %eax
	addl	$1, %eax
	lock xchg	(%rdi), %eax
	testb	%al, %al
	je	.L2
	xorl	%eax, %eax
	addl	$1, %eax
	ret
.L2:
	xorl	%eax, %eax
	ret
	.cfi_endproc
.LFE0:
	.size	tsl, .-tsl
	.section	.text.unlikely
.LCOLDE0:
	.text
.LHOTE0:
	.ident	"GCC: (GNU) 5.3.1 20160406 (Red Hat 5.3.1-6)"
	.section	.note.GNU-stack,"",@progbits
