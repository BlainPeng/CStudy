#include <stdio.h>


void test12(char *a) {

//    a[0] = 'a';
    *a = 'a';
}

int main() {

    char array1[10];
    test12(array1);

    char *array2 = NULL;
    test12(array1);
    printf("%s\n", array1);
    return 0;
}