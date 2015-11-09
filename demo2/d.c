extern int printf(char *,...);
int add(int x, int y){
    /*__asm__(".byte \x55, \x89,\xe5,\x8b,\x45,"
            "\x0c,\x8b,\x55,\x08,\x01,"
            "\xd0,\x5d,\xc3,\x66,\x90");*/
    __asm__(".byte \x61, \x61,\x61");
}
int main(){
    printf("sum() = %d\n",add(9,4));
    return 0;
}

