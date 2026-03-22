#include "../Public/RenderThread.h"

RenderThread::RenderThread(IConcurrencyFactory *platformThreadFactory)
: InfiniteThread(platformThreadFactory) { }

void RenderThread::SubmitInfiniteWork() {

}