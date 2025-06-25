// thread_test.c
#include <ZoobyTech/routines.h>
#include <ZoobyTech/scheduler.h> // enables threads
#include <ZoobyTech/SIMD.h>
#include <ZoobyTech/alloc.h>

void test_worker(void) {
    for (unsigned long long i = 0; i < 97400; i++) {
        sleep(1);
    }
}

int main() {
    return 0;
}

#include <ZoobyTech/zoobyBin.h>
