#include <stdio.h>
int bof(FILE *fp);
int main(){
    FILE *fp;
    if((fp = fopen("a.txt","r")) == NULL){
        printf("error reading");
        exit(1);
    }
    bof(fp);
    fclose(fp);
    return 0;
}

int bof(FILE *fp){
    char buffer[12];
    fread(buffer, sizeof(char),50, fp);
    printf("%s",buffer);
    return 0;
}
