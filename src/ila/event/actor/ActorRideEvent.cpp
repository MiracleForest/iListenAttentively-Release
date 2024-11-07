#include "ActorRideEvent.h"

namespace ila::inline actor
{
LL_TYPE_INSTANCE_HOOK(
    ActorRideEventHook,
    HookPriority::Normal,
    Actor,
    "?canAddPassenger@Actor@@UEBA_NAEAV1@@Z",
    bool,
    Actor& pPassenger
)
{
    auto beforeEvent = ActorRideBeforeEvent(pPassenger, *this);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pPassenger);
    eventBus.publish(ActorRideAfterEvent(pPassenger, *this, result));
    return result;
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&);
class ActorRideBeforeEventEmitter : public ll::event::Emitter<emitterFactory1, ActorRideBeforeEvent>
{
    ll::memory::HookRegistrar<ActorRideEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory1(ll::event::ListenerBase&)
{
    return std::make_unique<ActorRideBeforeEventEmitter>();
}

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&);
class ActorRideAfterEventEmitter : public ll::event::Emitter<emitterFactory2, ActorRideAfterEvent>
{
    ll::memory::HookRegistrar<ActorRideEventHook> hook;
};

static std::unique_ptr<ll::event::EmitterBase> emitterFactory2(ll::event::ListenerBase&)
{
    return std::make_unique<ActorRideAfterEventEmitter>();
}

} // namespace ila::inline actor