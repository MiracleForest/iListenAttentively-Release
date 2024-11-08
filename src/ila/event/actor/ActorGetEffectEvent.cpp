#include "ActorGetEffectEvent.h"

namespace ila::inline actor
{

MobEffectInstance const& ActorGetEffectBeforeEvent::getEffect() const { return mEffect; };

MobEffectInstance const& ActorGetEffectAfterEvent::getEffect() const { return mEffect; };

LL_TYPE_INSTANCE_HOOK(
    ActorGetEffectEventHook,
    HookPriority::Normal,
    Actor,
    &Actor::addEffect,
    void,
    MobEffectInstance const& pEffect
)
{
    auto beforeEvent = ActorGetEffectBeforeEvent(*this, pEffect);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pEffect);
    eventBus.publish(ActorGetEffectAfterEvent(*this, pEffect));
}

Event_Factory(ActorGetEffect, <ActorGetEffectEventHook>);

} // namespace ila::inline actor