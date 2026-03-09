#include "../Public/WindowsConcurrencyFactory.h"
#include "WindowsPlatformThread.h"

IPlatformThread* WindowsConcurrencyFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize,
                                                                 ThreadCreationFlags flags) {
    WindowsPlatformThread* windowsPlatformThread = new WindowsPlatformThread();
    windowsPlatformThread->Create(executeAction, stackSize, flags);
    return windowsPlatformThread;
}