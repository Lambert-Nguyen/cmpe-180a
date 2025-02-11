
#include <stdlib.h> /* need for atoi() stdc library funct. */
#include "factorial.h"

int main(int argc, char *argv[]) {
    printf("argc = %d\n", argc);
    printf("argv[0] - %s\n", argv[0]);
    if (argc < 2) {
        printf("Argument count should be 2 or larger\n");
        return 1;
    }
    int n = atoi(argv[1]);
    printf("factorial(%d)=%d\n",n, factorial(n));
    return 0;
}
