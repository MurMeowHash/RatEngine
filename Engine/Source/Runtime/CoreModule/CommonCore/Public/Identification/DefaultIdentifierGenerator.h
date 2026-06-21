#pragma once

#include "IIdentifierGenerator.h"
#include <random>

template<std::integral T>
class DefaultIdentifierGenerator : public IIdentifierGenerator<T> {
public:
    [[nodiscard]] T GenerateIdentifier() override;
private:
    std::random_device rd;
    std::mt19937_64 mt = std::mt19937_64(rd());
    std::uniform_int_distribution<T> dist;
};
