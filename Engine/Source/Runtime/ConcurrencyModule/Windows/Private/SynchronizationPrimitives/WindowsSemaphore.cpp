#include "../../Public/SynchronizationPrimitives/WindowsSemaphore.h"
#include <cassert>

void WindowsSemaphore::Create(int32_t initialUsages, int32_t maxUsages) {
    m_semaphore = CreateSemaphoreA(nullptr, initialUsages, maxUsages, nullptr);
}

void WindowsSemaphore::Acquire() {
    assert(IsValid());
    WaitForSingleObject(m_semaphore, INFINITE);
}

void WindowsSemaphore::Release() {
    assert(IsValid());
    ReleaseSemaphore(m_semaphore, 1, nullptr);
}

void WindowsSemaphore::Terminate() {
    assert(IsValid());
    CloseHandle(m_semaphore);
    m_semaphore = nullptr;
}

bool WindowsSemaphore::IsValid() const {
    return m_semaphore != nullptr;
}