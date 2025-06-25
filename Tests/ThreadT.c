// thread_test.c
#include <ZoobyTech/debug.h>
#include <ZoobyTech/SIMD.h> // enables SIMD on all future includes.
#include <ZoobyTech/scheduler.h> // enables threads

void test_worker(void) {
    for (unsigned long long i = 0; i < 97400; i++) {
        i++;
    }
}

int main() {
    struct thread* t = threadCreate((void*)test_worker);
    threadStart(t);
    threadJoin(t);
    sleep(100000);
    return 0;

}

#include <ZoobyTech/zoobyBin.h>
