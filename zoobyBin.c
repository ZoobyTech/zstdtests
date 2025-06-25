#include <ZoobyTech/zoobyBin.h>
#include <ZoobyTech/printf.h>

__attribute__((visibility("default")))
int main(void)
{
    const char *msg = "Hello, world!\n\0";

    printf("%s\n",msg);

    return 0;
};
