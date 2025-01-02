#pragma once

#include <ll/api/event/Emitter.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/io/Logger.h>
#include <ll/api/memory/Hook.h>
#include <mc/nbt/CompoundTag.h>


#ifndef SelfLogger
#    define SelfLogger ll::mod::NativeMod::current()->getLogger()
#endif

#ifndef LLEventBus
#    define LLEventBus ll::event::EventBus::getInstance()
#endif

#ifndef Event_Hook_Factory
#    define Event_Hook_Factory(eventName, ...)                                                               \
        static std::unique_ptr<ll::event::EmitterBase> eventBeforeEmitterFactory();                          \
        class eventName##BeforeEventEmitter                                                                  \
            : public ll::event::Emitter<eventBeforeEmitterFactory, eventName##BeforeEvent>                   \
        {                                                                                                    \
            ll::memory::HookRegistrar __VA_ARGS__ hook;                                                      \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> eventBeforeEmitterFactory()                           \
        {                                                                                                    \
            return std::make_unique<eventName##BeforeEventEmitter>();                                        \
        }                                                                                                    \
                                                                                                             \
        static std::unique_ptr<ll::event::EmitterBase> eventAfterEmitterFactory();                           \
        class eventName##AfterEventEmitter                                                                   \
            : public ll::event::Emitter<eventAfterEmitterFactory, eventName##AfterEvent>                     \
        {                                                                                                    \
            ll::memory::HookRegistrar __VA_ARGS__ hook;                                                      \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> eventAfterEmitterFactory()                            \
        {                                                                                                    \
            return std::make_unique<eventName##AfterEventEmitter>();                                         \
        };
#endif

#ifndef Event_Listener_Factory
#    define Event_Listener_Factory(eventName)                                                                \
        static std::unique_ptr<ll::event::EmitterBase> eventName##EmitterFactory();                          \
        class eventName##EventEmitter                                                                        \
            : public ll::event::Emitter<eventName##EmitterFactory, eventName##Event>                         \
        {                                                                                                    \
        private:                                                                                             \
            std::vector<ll::event::ListenerPtr> mListeners = {};                                             \
                                                                                                             \
        public:                                                                                              \
            eventName##EventEmitter();                                                                       \
            ~eventName##EventEmitter()                                                                       \
            {                                                                                                \
                for (auto& listener : mListeners) { LLEventBus.removeListener(listener); }                   \
                mListeners.clear();                                                                          \
            }                                                                                                \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> eventName##EmitterFactory()                           \
        {                                                                                                    \
            return std::make_unique<eventName##EventEmitter>();                                              \
        }                                                                                                    \
        eventName##EventEmitter::eventName##EventEmitter()
#endif