#pragma once
#include <span> // temporary fix workflow

#include "iListenAttentively.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/Emitter.h>
#include <ll/api/event/Event.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <ll/api/event/entity/MobEvent.h>
#include <ll/api/event/player/PlayerEvent.h>
#include <ll/api/event/world/LevelEvent.h>
#include <ll/api/event/world/WorldEvent.h>

#ifdef ILA_EXPORT
#    include <ll/api/Logger.h>
#    include <ll/api/memory/Hook.h>
#    include <ll/api/memory/Memory.h>
#    define ILAPI      __declspec(dllexport)
#    define SelfLogger ila::iListenAttentively::getInstance().getSelf().getLogger()
#    define eventBus   ll::event::EventBus::getInstance()
#    define Event_Factory(eventName, ...)                                                                    \
        static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);            \
        class eventName##BeforeEventEmitter                                                                  \
            : public ll::event::Emitter<emitterFactory1, eventName##BeforeEvent>                             \
        {                                                                                                    \
            ll::memory::HookRegistrar __VA_ARGS__ hook;                                                      \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)             \
        {                                                                                                    \
            return std::make_unique<eventName##BeforeEventEmitter>();                                        \
        }                                                                                                    \
        static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);            \
        class eventName##AfterEventEmitter                                                                   \
            : public ll::event::Emitter<emitterFactory2, eventName##AfterEvent>                              \
        {                                                                                                    \
            ll::memory::HookRegistrar __VA_ARGS__ hook;                                                      \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)             \
        {                                                                                                    \
            return std::make_unique<eventName##AfterEventEmitter>();                                         \
        };
#else
#    define ILAPI __declspec(dllimport)
#endif