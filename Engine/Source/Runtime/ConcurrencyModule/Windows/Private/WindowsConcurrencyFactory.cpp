#include "../Public/WindowsConcurrencyFactory.h"
#include "WindowsPlatformThread.h"
#include "../Public/SynchronizationPrimitives/WindowsMutex.h"
#include "SynchronizationPrimitives/WindowsFence.h"
#include "SynchronizationPrimitives/WindowsSemaphore.h"

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

IFence * WindowsConcurrencyFactory::CreatePlatformFence(bool invokeMemoryBarrier) {
    return new WindowsFence(invokeMemoryBarrier);
}

ISemaphore * WindowsConcurrencyFactory::CreatePlatformSemaphore(int32_t initialUsages, int32_t maxUsages) {
    WindowsSemaphore* windowsSemaphore = new WindowsSemaphore();
    windowsSemaphore->Create(initialUsages, maxUsages);
    return windowsSemaphore;
}