	.globl main
main:
	movl $0, %eax # n = 0;
	movl $0, %ecx # sum = 0;
.Loop:	
	addl %eax, %ecx # sum += n;
	incl %eax # n++;
	cmpl $100, %eax
	jle  .Loop #  '.' as static, not globle
.Done:
	nop
	nop
	nop

