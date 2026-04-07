#include "../../Public/SynchronizationPrimitives/MockSemaphore.h"

void MockSemaphore::Create(int32_t initialUsages, int32_t maxUsages) { }

void MockSemaphore::Acquire() { }

void MockSemaphore::Release() { }

void MockSemaphore::Terminate() { }

bool MockSemaphore::IsValid() const { return false; }
