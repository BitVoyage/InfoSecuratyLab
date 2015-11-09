#include <stdlib.h>
int main()
{
    putenv("BIN_SH=/bin/sh");
    printf("%x\n",getenv("BIN_SH"));
    return 0;
 }
