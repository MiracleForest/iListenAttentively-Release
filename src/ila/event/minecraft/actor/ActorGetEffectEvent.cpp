#include "ila/event/minecraft/actor/ActorGetEffectEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/effect/EffectDuration.h>

namespace ila::mc::inline actor
{

void ActorGetEffectBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["effect"] = *getEffect().save();
}
void ActorGetEffectBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getEffect() = MobEffectInstance::load(nbt["effect"].get<CompoundTag>());
}
MobEffectInstance& ActorGetEffectBeforeEvent::getEffect() const { return mEffect; };

void ActorGetEffectAfterEvent::serialize(CompoundTag& nbt) const
{
    ActorEvent::serialize(nbt);
    nbt["effect"] = *getEffect().save();
}
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
    auto beforeEvent = ActorGetEffectBeforeEvent(*this, const_cast<MobEffectInstance&>(pEffect));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pEffect);
    LLEventBus.publish(ActorGetEffectAfterEvent(*this, pEffect));
}

Event_Hook_Factory(ActorGetEffect, <ActorGetEffectEventHook>);

} // namespace ila::mc::inline actor