extern int printf(char *,...);
const char buf[] = {'\x55','\x89','\xe5','\x8b','\x45',
    '\x0c','\x8b','\x55','\x08',
    '\x01','\xd0','\x5d','\xc3','\x66','\x90'};
int main(){
    printf("sum() = %d\n",((int(*)(int, int))buf)(3,4));
    return 0;
}

