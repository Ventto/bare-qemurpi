#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    char *ptr = malloc(1000);
    ptr[0] = 'a';
    ptr[100] = 'b';
    ptr[200] = 'c';
    printf("Hello, world!\n");
}
