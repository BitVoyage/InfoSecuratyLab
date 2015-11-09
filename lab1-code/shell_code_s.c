#include <stdio.h>

void main(){
    _asm("

mov    $0x0,%edx
mov    $0x0,%esi
mov    $0x4005d4,%edi
callq  400420 <execve@plt>
            ");
}
