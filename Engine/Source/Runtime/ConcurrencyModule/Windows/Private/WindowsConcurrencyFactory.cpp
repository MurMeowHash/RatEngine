#include "../Public/WindowsConcurrencyFactory.h"
#include "WindowsPlatformThread.h"
#include "../Public/SynchronizationPrimitives/WindowsMutex.h"

IPlatformThread* WindowsConcurrencyFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize,
                                                                 ThreadCreationFlags flags) {
    WindowsPlatformThread* windowsPlatformThread = new WindowsPlatformThread();
    windowsPlatformThread->Create(executeAction, stackSize, flags);
    return windowsPlatformThread;
}

IMutex *WindowsConcurrencyFactory::CreatePlatformMutex() {
    WindowsMutex* windowsMutex = new WindowsMutex();
    windowsMutex->Create();
    return windowsMutex;
}