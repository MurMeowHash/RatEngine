#include "../Public/RenderThread.h"
#include "CoreUtils.h"

RenderThread::RenderThread(IPlatformThreadFactory *platformThreadFactory)
: ClientThreadBase(platformThreadFactory) { }

void RenderThread::SubmitWork() {
    while(!Rat::Core::Flags::IsFlagSet(RetrieveRuntimeFlags(), ThreadRuntimeFlags::StopRequested)) {
        //do some work
    }
}
