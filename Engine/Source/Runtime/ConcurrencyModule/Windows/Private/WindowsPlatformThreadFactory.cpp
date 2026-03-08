#include "../Public/WindowsPlatformThreadFactory.h"
#include "WindowsPlatformThread.h"

IPlatformThread* WindowsPlatformThreadFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize,
                                                                    ThreadCreationFlags flags) {
    WindowsPlatformThread* windowsPlatformThread = new WindowsPlatformThread();
    windowsPlatformThread->Create(executeAction, stackSize, flags);
    return windowsPlatformThread;
}