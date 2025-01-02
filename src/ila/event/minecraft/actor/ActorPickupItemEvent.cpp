#include "ila/event/minecraft/actor/ActorPickupItemEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/actor/ai/goal/PickupItemsGoal.h>

namespace ila::mc::inline actor
{

void ActorPickupItemBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["itemActor"] = reinterpret_cast<uintptr_t>(&getItemActor());
}
ItemActor& ActorPickupItemBeforeEvent::getItemActor() const { return mItemActor; };

void ActorPickupItemAfterEvent::serialize(CompoundTag& nbt) const
{
    MobEvent::serialize(nbt);
    nbt["itemActor"] = reinterpret_cast<uintptr_t>(&getItemActor());
}
ItemActor const& ActorPickupItemAfterEvent::getItemActor() const { return mItemActor; };

LL_TYPE_INSTANCE_HOOK(
    ActorPickupItemEventHook,
    HookPriority::Normal,
    PickupItemsGoal,
    &PickupItemsGoal::_pickItemUp,
    void,
    ItemActor* pItem
)
{
    if (pItem == nullptr) { return origin(pItem); }
    auto* actor       = mUnk964019.as<Mob*>();
    auto  beforeEvent = ActorPickupItemBeforeEvent(*actor, *pItem);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pItem);
    LLEventBus.publish(ActorPickupItemAfterEvent(*actor, *pItem));
}

Event_Hook_Factory(ActorPickupItem, <ActorPickupItemEventHook>);

} // namespace ila::mc::inline actor