

int factorial(int n) {
    int f=1;
    /* f(n) = n * (n-1) * (n -2) ... 1*/

    for(int i =1; i <= n; i++){
        f = f * i;
    }
    return f;
}