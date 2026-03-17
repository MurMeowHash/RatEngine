#include "../Public/EngineLogger.h"

void EngineLogger::SetOutputStream(std::ostream *outputStream) {
    m_outputStream = outputStream;
}

void EngineLogger::PrintError(const std::string &msg) const {
    PrintMsg(msg);
}

void EngineLogger::PrintWarning(const std::string &msg) const {
    PrintMsg(msg);
}

void EngineLogger::PrintMsg(const std::string &msg) const {
    *m_outputStream << msg;
}

void EngineLogger::PrintInfo(const std::string &msg) const {
    PrintMsg(msg);
}
