#include "../Public/WindowsConcurrencyFactory.h"
#include "WindowsPlatformThread.h"
#include "WindowsMutex.h"

IPlatformThread* WindowsConcurrencyFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize,
                                                                 ThreadCreationFlags flags) {
    WindowsPlatformThread* windowsPlatformThread = new WindowsPlatformThread();
    windowsPlatformThread->Create(executeAction, stackSize, flags);
    return windowsPlatformThread;
}

IMutex *WindowsConcurrencyFactory::CreatePlatformMutex(bool initiallyLocked) {
    WindowsMutex* windowsMutex = new WindowsMutex();
    windowsMutex->Create(initiallyLocked);
    return windowsMutex;
}