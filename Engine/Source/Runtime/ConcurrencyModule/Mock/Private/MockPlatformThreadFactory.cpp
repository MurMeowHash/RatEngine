#include "../Public/MockPlatformThreadFactory.h"
#include "MockPlatformThread.h"

IPlatformThread * MockPlatformThreadFactory::CreatePlatformThread(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) {
    return new MockPlatformThread();
}
