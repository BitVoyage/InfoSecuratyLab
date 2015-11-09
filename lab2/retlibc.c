#include <stdio.h>

int main(int argc, char **argv){

    if(argc != 2){
        puts("Need an argument\n");
        _exit(1);
    }
    func(argv[1]);
    return 0;
}
int func(char *argv){
    char buff[5];
    printf("Exploiting via returning into libc function\n");
    strcpy(buff, argv);
    printf("\nYou typed [%s] \n\n", buff);
    return 0;
}
