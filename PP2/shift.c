#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int shiftstring(char* s, int numshift){
    int length = strlen(s);
    if (length == 0 || numshift == 0) {
        fprintf(stdout,"%s\n", s);
        return 0;
    }
    numshift = numshift % length;
    char temp1;
    for (int y = 0; y < numshift; y++) {
        temp1 = s[length-1];
        for (int x = (length-1); x > 0; x--) {
            s[x] = s[x-1];
        }
        s[0] = temp1;
        }

    // for (int t = 0; t < length; t++){
    //     fprintf(stdout, "Character at index %d: %c\n", t, s[t]);
    //     fprintf(stdout, "%c",s[t]);
    // }

    fprintf(stdout,"%s\n", s);
    return 0;
}

int main(int argc, char *argv[]){
    // printf("argc = %d\n", argc);
    // printf("argv[0] - %s\n", argv[0]);

    if (argc != 3) {
        fprintf(stderr, "Argument count must be 3\n");
        fprintf(stderr,"Usage: %s NumberofShift InputString. Ex: %s 1 hello \n", argv[0], argv[0]);
        return 1;
    }

    int shifts = atoi(argv[1]); //number of shifts
    
    char* s = strdup(argv[2]);
    if (!s) {
        fprintf(stderr, "Memory allocation failed\n");
        return 1;
    }

    shiftstring(s, shifts);
    free(s);
    return 0;
}