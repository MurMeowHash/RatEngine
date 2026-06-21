#include "../../Public/Identification/DefaultIdentifierGenerator.h"

template<std::integral T>
T DefaultIdentifierGenerator<T>::GenerateIdentifier() {
    return dist(mt);
}