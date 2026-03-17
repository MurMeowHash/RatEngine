#include "../Public/MockPlatformThread.h"

void MockPlatformThread::Create(IDelegate<> *executeAction, size_t stackSize, ThreadCreationFlags flags) { }

void MockPlatformThread::Execute() { }

uint32_t MockPlatformThread::GetThreadId() {
    return 0;
}

bool MockPlatformThread::IsValid() {
    return false;
}

bool MockPlatformThread::IsRunning() {
    return false;
}

void MockPlatformThread::Terminate(bool forced) { }
