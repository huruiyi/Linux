#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
    if (argc != 2)
    {
        perror("参数不足，./hello a");
    }

    int a = atoi(argv[1]);
    printf("10%%%d=%d", a, 10 / a);
    return 0;
}