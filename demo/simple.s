	.globl main
main:
	movl $0, %eax
	call f
	incl %eax
	incl %eax
f:
	ret
.Done:
	nop
	nop
	nop

