#include <stdio.h>

int main()
{
    printf("sizeof char = %zu\n", sizeof(char));
    printf("sizeof short = %zu\n", sizeof(short));
    printf("sizeof int = %zu\n", sizeof(int));
    printf("sizeof long = %zu\n", sizeof(long));
    printf("sizeof long long = %zu\n", sizeof(long long));
}
/*
MSVC
sizeof char = 1
sizeof short = 2
sizeof int = 4
sizeof long = 4
sizeof long long = 8
*/