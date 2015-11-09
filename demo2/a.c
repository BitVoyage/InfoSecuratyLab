void g();
int main(){
    f();
    g();
    return 0;
}

int f(){
    int x = 3;
    printf("value = %d\n", x);
    return x;
}
void g(){
    int z;
    printf("value = %d\n", z);
    return;
}
