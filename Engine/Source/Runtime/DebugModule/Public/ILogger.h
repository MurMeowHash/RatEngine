#pragma once

#include <string>

class ILogger {
public:
    virtual void SetOutputStream(std::ostream *outputStream) = 0;
    virtual void PrintError(const std::string &msg) const = 0;
    virtual void PrintWarning(const std::string &msg) const = 0;
    virtual void PrintInfo(const std::string &msg) const = 0;
    virtual ~ILogger() = default;
};