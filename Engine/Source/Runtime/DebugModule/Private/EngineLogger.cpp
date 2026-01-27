#include "../Public/EngineLogger.h"

void EngineLogger::SetOutputStream(std::ostream *outputStream) {
    m_outputStream = outputStream;
}

void EngineLogger::PrintError(const std::string &msg) const {
    *m_outputStream << msg;
}