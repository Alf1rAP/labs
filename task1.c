#include <stdio.h>

void modificate(int *ram, int *lat)
{
    *ram = *ram - 1;
    *lat = *lat + 1;
}

int main()
{
    int ram = 32;
    int latency = -64;

    modificate(&ram, &latency);
    printf("%d %d\n", ram, latency);
    return 0;
}
