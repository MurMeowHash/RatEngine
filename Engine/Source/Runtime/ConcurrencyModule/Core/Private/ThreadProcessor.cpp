#include "../Public/ThreadProcessor.h"

void ThreadProcessor::Tick() const {
    for (const std::pair<const std::type_index, IConcurrencySystem *> &system: m_systems) {
        system.second->Tick();
    }
}

void ThreadProcessor::TerminateProcessor() {
    for (const std::pair<const std::type_index, IConcurrencySystem *> &systemPair: m_systems) {
        systemPair.second->Terminate();
        delete systemPair.second;
    }

    m_systems.clear();
}
