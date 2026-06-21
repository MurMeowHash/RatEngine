#include "../../Public/PlatformInteractors/WindowsPlatformInteractor.h"
#include <processthreadsapi.h>
#include "CoreGlobals.h"

WindowsPlatformInteractor::WindowsPlatformInteractor() {
    CreatePlatformRuntimeData();
}

void WindowsPlatformInteractor::RequestQuit(bool forcedQuit) {
    if(forcedQuit)
        TerminateProcess(GetCurrentProcess(), 1);
    else
        Rat::Core::g_isEngineQuitRequested = true;
}

uint32_t WindowsPlatformInteractor::GetRunningThreadId() {
    return GetCurrentThreadId();
}

PlatformRuntimeData WindowsPlatformInteractor::GetPlatformRuntimeData() {
    return m_platformRuntimeData;
}

void WindowsPlatformInteractor::CreatePlatformRuntimeData() {
    m_platformRuntimeData = PlatformRuntimeData{ PlatformType::Windows, PlatformCategory::Desktop };
}