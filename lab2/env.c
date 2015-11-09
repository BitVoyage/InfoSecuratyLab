#include <string.h>
#include <stdlib.h>
#include <stdio.h>
extern char **environ;

int main(int  argc, char *argv[] ){
    char buffer[5];

    int i=0;
    while(*(environ+i)){
        printf("%s:%p\n",*(environ + i), *(environ + i));
        i++;
    }
    return 0;
}
