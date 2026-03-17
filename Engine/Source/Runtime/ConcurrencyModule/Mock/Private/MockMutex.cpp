#include "../Public/MockMutex.h"

void MockMutex::Create(bool initiallyLocked) { }

void MockMutex::Lock() { }

void MockMutex::Unlock() { }

bool MockMutex::IsValid() {
    return false;
}

void MockMutex::Terminate() { }