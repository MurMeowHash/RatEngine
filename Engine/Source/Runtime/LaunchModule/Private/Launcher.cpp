#include "CoreLoop.h"

CoreLoop g_coreLoop;

int main() {
    Rat::Core::ErrorSeverity errorSeverity;
    errorSeverity = g_coreLoop.Initialize();

    while(!Rat::Core::g_isEngineQuitRequested && errorSeverity != Rat::Core::ErrorSeverity::Fatal) {
        errorSeverity = g_coreLoop.Tick();
    }

    g_coreLoop.Exit();
    return 0;
}