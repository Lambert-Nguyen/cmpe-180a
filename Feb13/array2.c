#include <stdio.h>

int main(){
    int arr[2][2] = {{1,2},
                    {3, 4}};

    /* [ 1 2 3 4 ] Row-major*/
    /* [ 1 2 3 4 ] Column-major*/

    printf("this array has this many bytes=sizeof(arr) %ld\n", sizeof(arr));

    int *p = &arr[0][0];
    for (int i = 0; i < 4; i++){
        printf("%d\n", *p);
        p++;
    }

    /* EXPECTED out if C is row major 1 2 3 4*/
}
