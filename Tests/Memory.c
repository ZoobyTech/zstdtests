// alloc_test.c
#include <ZoobyTech/alloc.h>
#include <ZoobyTech/printf.h>
#include <ZoobyTech/string.h>
#include <ZoobyTech/zoobyBin.h>
int main() {
    printf("Running allocation test...\n");
    char* buffer = alloc(2000);

    char* block = alloc(32);
    for (int i = 0; i < 32; i++) block[i] = 'A';
    block[31] = '\0';
    printf("Alloc: %s\n", block);

    block = realloc(block, 64);
    for (int i = 32; i < 64; i++) block[i] = 'B';
    block[63] = '\0';
    printf("Realloc: %s\n", block);

    free(block);

    int* array = calloc(10, sizeof(int));
    printf("Address:%p\n",array);
    if (!array) {
        printf("Error: calloc failed\n");
        return 1;
    }
    printf("%s\n","Calloc'd");
    for (int i = 0; i < 10; i++) printf("calloc[%d] = %d\n", i, array[i]);
    printf("%s\n","Yeah, freeing next");
    free(array);

    printf("Allocation test completed.\n");
    return 0;
}
