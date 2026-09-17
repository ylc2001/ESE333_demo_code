#include <stdio.h>

int main() {
    int x = 7;
    int *p = &x;

    printf("%d\n", x);
    printf("%d\n", *p);
    printf("%p\n", (void *)p);

    *p = 10;
    printf("%d\n", x);
    return 0;
}
