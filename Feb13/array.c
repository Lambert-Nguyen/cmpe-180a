#include <stdio.h>

long unsigned getarr(int arr[]) {
    return sizeof(arr);
}

int main(){
    int arr[3] = {1,2,3};
    printf("this array has this many bytes=sizeof(arr) %ld\n", sizeof(arr));
    printf("this array has this many bytes=getarr() %ld\n", getarr(arr));

}
