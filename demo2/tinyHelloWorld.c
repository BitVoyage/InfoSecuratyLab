
extern int printf(char *,...);
int p(){
    __asm__("\tmovl $4, %eax\n"
            "\tmovl $1, %ebx\n"
            "\tmovl $0x080484d0, %ecx\n"
            "\tmovl $20, %edx\n"
            "\tint $0x80"
            );
}
int main(){
    p();
    return 0;
}

