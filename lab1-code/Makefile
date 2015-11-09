all:	server.c httpd.c parse.c token.c http-tree.c
	@gcc -fno-stack-protector -z noexecstack  -g -m32 -o touchstone server.c
	@gcc -fno-stack-protector -z noexecstack -g -m32 -o httpd httpd.c token.c parse.c http-tree.c handle.c
	@gcc -fno-stack-protector -z noexecstack -g -m32 -o broswer broswer.c

stack1: stack1.c
	@gcc -fno-stack-protector -z execstack -g -m32 stack1.c -o stack1

stack2: stack2.c
	@gcc -g -m32 -z execstack -fno-stack-protector stack2.c -o stack2

test-shell: test-shell.c
	@gcc -fno-stack-protector -z execstack -m32 test-shell.c -o test-shell
create-shellcode: create-shellcode.c
	@gcc -g -m32 -z execstack -fno-stack-protector create-shellcode.c -o create-shellcode
clean:
	@rm -rf touchstone httpd stack1 stack2 test-shell
