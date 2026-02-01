#include "../../Public/PlatformInteractors/WindowsPlatformInteractor.h"
#include <processthreadsapi.h>
#include "CoreGlobals.h"

void WindowsPlatformInteractor::RequestQuit(bool forcedQuit) {
    if(forcedQuit)
        TerminateProcess(GetCurrentProcess(), 1);
    else
        Rat::Core::g_isEngineQuitRequested = true;
}