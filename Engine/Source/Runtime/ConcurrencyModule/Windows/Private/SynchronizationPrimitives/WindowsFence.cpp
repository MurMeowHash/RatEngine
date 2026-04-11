#include "SynchronizationPrimitives/WindowsFence.h"
#include <windows.h>

WindowsFence::WindowsFence(bool invokeMemoryBarrier) {
    if (invokeMemoryBarrier)
        WindowsFence::MakeMemoryVisible();
}

void WindowsFence::MakeMemoryVisible() {
    MemoryBarrier();
}
