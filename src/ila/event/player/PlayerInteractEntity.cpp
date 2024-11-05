#include "PlayerInteractEntity.h"

namespace ila::inline player
{
LL_TYPE_INSTANCE_HOOK(
    PlayerInteractEntityEventHook,
    HookPriority::Normal,
    Player,
    "?interact@Player@@QEAA_NAEAVActor@@AEBVVec3@@@Z",
    bool,
    Actor& actor,
    Vec3&  location
)
{
    // clang-format off
    auto beforeEvent = PlayerInteractEntityBeforeEvent(*this, actor, location);
    ll::event::EventBus::getInstance().publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(actor, location);
    ll::event::EventBus::getInstance().publish(PlayerInteractEntityAfterEvent(*this, actor, location, result));
    // clang-format on
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class PlayerInteractEntityBeforeEventEmitter
    : public ll::event::Emitter<emitterFactory1, PlayerInteractEntityBeforeEvent>
{
    ll::memory::HookRegistrar<PlayerInteractEntityEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerInteractEntityBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class PlayerInteractEntityAfterEventEmitter
    : public ll::event::Emitter<emitterFactory2, PlayerInteractEntityAfterEvent>
{
    ll::memory::HookRegistrar<PlayerInteractEntityEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<PlayerInteractEntityAfterEventEmitter>();
}

} // namespace ila::inline server