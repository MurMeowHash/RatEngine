#pragma once

template<typename T>
class IIdentifierGenerator {
public:
    virtual T GenerateIdentifier() = 0;
    virtual ~IIdentifierGenerator() = default;
};