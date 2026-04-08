#pragma once

#include "IDelegate.h"
#include "StaticDelegate.h"
#include <unordered_map>
#include <typeindex>
#include <vector>
#include <memory>

template<typename TEventBase>
class EventBusBase {
public:
    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void Publish(const TEvent& event) const {
        auto eventHandlers = m_listeners.find(typeid(TEvent));
        if(eventHandlers == m_listeners.end())
            return;

        for(const std::unique_ptr<StaticDelegate<const TEventBase&>> &handler : eventHandlers->second) {
            handler->Invoke(event);
        }
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void Subscribe(IDelegate<const TEvent&>* eventHandler) {
        std::size_t delegateHash = std::hash<IDelegate<const TEvent&>*>{}(eventHandler);
        if(m_cachedDelegates.contains(delegateHash))
            return;

        if(!m_listeners.contains(typeid(TEvent)))
            m_listeners.emplace(typeid(TEvent), std::vector<std::unique_ptr<StaticDelegate<const TEventBase&>>>());

        std::unique_ptr<StaticDelegate<const TEventBase&>> eventHandlerWrapper = std::make_unique<StaticDelegate<const TEventBase&>>(
                [eventHandler](const TEventBase& eventBase){
                    eventHandler->Invoke(static_cast<const TEvent&>(eventBase));
                });

        auto eventHandlersIterator = m_listeners.find(typeid(TEvent));
        StaticDelegate<const TEventBase&>* wrapperRawPointer = eventHandlerWrapper.get();
        eventHandlersIterator->second.emplace_back(std::move(eventHandlerWrapper));
        m_cachedDelegates.emplace(delegateHash, wrapperRawPointer);
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    void UnSubscribe(IDelegate<const TEvent &>* eventHandler) {
        std::size_t delegateHash = std::hash<IDelegate<const TEvent&>*>{}(eventHandler);
        auto cachedDelegateIterator = m_cachedDelegates.find(delegateHash);
        auto eventHandlersIterator = m_listeners.find(typeid(TEvent));

        if(cachedDelegateIterator == m_cachedDelegates.end() || eventHandlersIterator == m_listeners.end())
            return;

        std::erase_if(eventHandlersIterator->second,
                      [&cachedDelegateIterator](const std::unique_ptr<StaticDelegate<const TEventBase&>> &eventHandler){
            return eventHandler.get() == cachedDelegateIterator->second;
        });
        m_cachedDelegates.erase(delegateHash);
    }

    template<typename TEvent> requires(std::is_base_of_v<TEventBase, TEvent>)
    [[nodiscard]] std::vector<StaticDelegate<const TEventBase&>> GetListenersSnapshot() const {
        std::vector<StaticDelegate<const TEventBase&>> snapshot;
        auto eventHandlers = m_listeners.find(typeid(TEvent));
        if (eventHandlers == m_listeners.end())
            return snapshot;

        snapshot.reserve(eventHandlers->second.size());
        for (const std::unique_ptr<StaticDelegate<const TEventBase&>> &handler : eventHandlers->second) {
            snapshot.emplace_back(*handler);
        }
        return snapshot;
    }

private:
    std::unordered_map<std::type_index, std::vector<std::unique_ptr<StaticDelegate<const TEventBase&>>>> m_listeners;
    std::unordered_map<std::size_t, StaticDelegate<const TEventBase&>*> m_cachedDelegates;
};