#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Emitter.h>
#include <ll/api/event/EventBus.h>
#include <ll/api/event/EventRefObjSerializer.h>
#include <ll/api/event/ListenerBase.h>
#include <ll/api/io/Logger.h>
#include <ll/api/memory/Hook.h>
#include <mc/network/MinecraftPacketIds.h>

#ifndef SelfLogger
#    define SelfLogger ll::mod::NativeMod::current()->getLogger()
#endif

#ifndef LLEventBus
#    define LLEventBus ll::event::EventBus::getInstance()
#endif

#ifndef Event_Hook_Factory_Base
#    define Event_Hook_Factory_Base(eventName, ...)                                                          \
        static std::unique_ptr<ll::event::EmitterBase> eventName##EmitterFactory();                          \
        class eventName##EventEmitter                                                                        \
            : public ll::event::Emitter<eventName##EmitterFactory, eventName##Event>                         \
        {                                                                                                    \
            ll::memory::HookRegistrar __VA_ARGS__ hook;                                                      \
        };                                                                                                   \
        static std::unique_ptr<ll::event::EmitterBase> eventName##EmitterFactory()                           \
        {                                                                                                    \
            return std::make_unique<eventName##EventEmitter>();                                              \
        }
#endif

#ifndef Event_Hook_Factory
#    define Event_Hook_Factory(eventName, ...)                                                               \
        Event_Hook_Factory_Base(eventName##Before, __VA_ARGS__);                                             \
        Event_Hook_Factory_Base(eventName##After, __VA_ARGS__);
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

class BlockSource;
class Dimension;
class NetworkIdentifier;
class NetworkPeer;

namespace ila
{
ILAPI void nextTick(std::function<void()> const& func);
ILNDAPI std::string getDimensionName(::DimensionType const& dimId);
ILNDAPI std::string getDimensionName(::BlockSource& region);
ILNDAPI std::string          getDimensionName(::Dimension& region);
ILNDAPI ::DimensionType      getDimensionId(std::string const& dimName);
using ll::event::serializePtrObj;
using ll::event::serializeRefObj;
using ll::memory::dAccess;
using namespace ll::memory_literals;
} // namespace ila

namespace ll::memory
{
template<class T>
constexpr FuncPtr resolveIdentifier(std::string const& symbol)
{
    return Symbol(symbol).view().resolve();
}
template<class T>
constexpr FuncPtr resolveIdentifier(ll::memory::FuncPtr func)
{
    return func;
}
} // namespace ll::memory

template<>
struct magic_enum::customize::enum_range<MinecraftPacketIds>
{
    static constexpr int min = static_cast<int>(MinecraftPacketIds::KeepAlive);
    static constexpr int max = static_cast<int>(MinecraftPacketIds::EndId);
};