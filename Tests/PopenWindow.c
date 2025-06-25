#include <ZoobyTech/ZWinCraft.h>
#include <ZoobyTech/printf.h>
#include <ZoobyTech/scheduler.h>
#include <ZoobyTech/zoobyBin.h>

int main(void) {
    printf("%s\n","Initializing.");
    // Init platform & start event-pump thread
    initZWC();
    printf("%s\n","Initialized.\nCreating window.");
    // Create a window
    struct zwWindow *win = ZWindow_create();
    printf("%s\n","Created window!");
    if (!win) {
        printf("%s\n", "Failed to create window");
        return 1;
    }
     printf("%s\n","Looping");
    // Simple loop — you’d normally wait on input/events here
    printf("Window running. Press Ctrl+C to quit.\n");
    while (1) {
        sleep(10);
    }

    // (Unreachable in this example, but included for completeness)
    ZWindow_destroy(win);
    return 0;
}
