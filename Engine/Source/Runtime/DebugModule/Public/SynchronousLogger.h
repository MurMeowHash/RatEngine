#pragma once

#include "ILogger.h"

class IConcurrencyFactory;
class IMutex;

class SynchronousLogger : public ILogger {
public:
    explicit SynchronousLogger(IConcurrencyFactory* concurrencyFactory);
    ~SynchronousLogger() override;
    void SetOutputStream(std::ostream *outputStream) override;
    void PrintError(const std::string &msg) const override;
    void PrintWarning(const std::string &msg) const override;
    void PrintInfo(const std::string &msg) const override;

private:
    IConcurrencyFactory* m_concurrencyFactory;

    std::ostream *m_outputStream = nullptr;
    IMutex* m_mutex;

    void PrintMsg(const std::string &msg) const;
};