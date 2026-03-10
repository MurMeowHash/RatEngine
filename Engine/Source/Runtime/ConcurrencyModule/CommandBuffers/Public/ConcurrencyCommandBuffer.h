#pragma once

template<typename TCommandDelegate>
struct ConcurrencyCommand {
    ConcurrencyCommand(const TCommandDelegate& command, ConcurrencyCommand<TCommandDelegate>* next)
    : m_command(command), m_next(next) { }

    TCommandDelegate m_command;
    ConcurrencyCommand<TCommandDelegate>* m_next;
};

template<typename TCommandDelegate>
class ConcurrencyCommandBuffer {
public:
    ConcurrencyCommand<TCommandDelegate>* GetRoot() const { return m_root; }

    void EqueueCommand(const TCommandDelegate& command) {
        ConcurrencyCommand<TCommandDelegate>* commandNode = new ConcurrencyCommand<TCommandDelegate>(command, nullptr);
        *m_tail = commandNode;
        m_tail = &commandNode->m_next;
    }

    virtual void Submit() = 0;

private:
    ConcurrencyCommand<TCommandDelegate>* m_root;
    ConcurrencyCommand<TCommandDelegate>** m_tail = &m_root;
};