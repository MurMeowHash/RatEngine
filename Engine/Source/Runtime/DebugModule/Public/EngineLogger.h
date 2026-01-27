#pragma once

#include "ILogger.h"

class EngineLogger : public ILogger {
public:
    void SetOutputStream(std::ostream *outputStream) override;
    void PrintError(const std::string &msg) const override;
private:
    std::ostream *m_outputStream = nullptr;
};