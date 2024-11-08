#include "PlayerInteractEntityEvent.h"

namespace ila::inline player
{

Actor& PlayerInteractEntityBeforeEvent::getTarget() const { return mTarget; }
Vec3&  PlayerInteractEntityBeforeEvent::getPos() const { return mPos; }

Actor const& PlayerInteractEntityAfterEvent::getTarget() const { return mTarget; }
Vec3 const&  PlayerInteractEntityAfterEvent::getPos() const { return mPos; }
bool&        PlayerInteractEntityAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    PlayerInteractEntityEventHook,
    HookPriority::Normal,
    Player,
    "?interact@Player@@QEAA_NAEAVActor@@AEBVVec3@@@Z",
    bool,
    Actor& pActor,
    Vec3&  pLocation
)
{
    auto beforeEvent = PlayerInteractEntityBeforeEvent(*this, pActor, pLocation);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pActor, pLocation);
    eventBus.publish(PlayerInteractEntityAfterEvent(*this, pActor, pLocation, result));
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

} // namespace ila::inline player