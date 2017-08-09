#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    printf( "Hello World\n" );
    //printf("Hello World");
    fork();
    return 0;
}
