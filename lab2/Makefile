all:	retlibc.c env.c
	@gcc -fno-stack-protector -g -m32 -o retlib retlibc.c
	@gcc -fno-stack-protector -g -m32 -o env env.c
test:retlibc_test.c
	@gcc -fno-stack-protector -g -m32 -o test retlibc_test.c
exec1:exec1.c
	@gcc -fno-stack-protector -g -m32 -o exec1 exec1.c
