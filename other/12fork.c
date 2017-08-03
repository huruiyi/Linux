#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    //5个进程
    int ref = ( fork() && fork() ) || fork();
    printf( "%d", ref );
    sleep( 10 );
    return 0;
}
