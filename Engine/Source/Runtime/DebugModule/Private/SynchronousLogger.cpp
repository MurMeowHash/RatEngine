#include "../Public/SynchronousLogger.h"
#include "IConcurrencyFactory.h"
#include "SynchronizationPrimitives/ExclusiveThreadGuard.h"

SynchronousLogger::SynchronousLogger(IConcurrencyFactory *concurrencyFactory)
: m_concurrencyFactory(concurrencyFactory) {
    m_mutex = m_concurrencyFactory->CreatePlatformMutex();
}

SynchronousLogger::~SynchronousLogger() {
    m_mutex->Terminate();
    delete m_mutex;
}

void SynchronousLogger::SetOutputStream(std::ostream *outputStream) {
    ExclusiveThreadGuard guard(m_mutex);
    m_outputStream = outputStream;
}

void SynchronousLogger::PrintError(const std::string &msg) const {
    PrintMsg(msg);
}

void SynchronousLogger::PrintWarning(const std::string &msg) const {
    PrintMsg(msg);
}

void SynchronousLogger::PrintMsg(const std::string &msg) const {
    ExclusiveThreadGuard guard(m_mutex);
    *m_outputStream << msg;
}

void SynchronousLogger::PrintInfo(const std::string &msg) const {
    PrintMsg(msg);
}
