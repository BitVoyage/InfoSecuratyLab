int main(){
    int y;
    y = f();
    printf("%d\n", y);
    return 0;
}

int f(){
    int x = 3;
    *(&x+2) = 0;
    return x;
}
