stack2:
	@gcc -m32 -z noexecstack -g -o stack2 stack2.c

exec3:
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o exec3 exec3.c

browser:
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o browser browser.c
repeat:
	@gcc -m32 -fno-stack-protector -z noexecstack -g -o repeat repeatBrowser.c
clean:
	@rm -rf stack2 exec3
