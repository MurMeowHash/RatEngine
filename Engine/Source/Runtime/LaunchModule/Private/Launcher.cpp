#include "CoreLoop.h"

CoreLoop g_coreLoop;

int main() {
    g_coreLoop.Initialize();
    g_coreLoop.Exit();
    return 0;
}