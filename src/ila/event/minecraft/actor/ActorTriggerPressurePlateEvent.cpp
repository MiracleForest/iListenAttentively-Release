#include "ila/event/minecraft/actor/ActorTriggerPressurePlateEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/BasePressurePlateBlock.h>

namespace ila::mc::inline world
{

void ActorTriggerPressurePlateBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
BlockPos const& ActorTriggerPressurePlateBeforeEvent::getPos() const { return mPos; }

void ActorTriggerPressurePlateAfterEvent::serialize(CompoundTag& nbt) const
{
    ActorEvent::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
BlockPos const& ActorTriggerPressurePlateAfterEvent::getPos() const { return mPos; }

LL_TYPE_INSTANCE_HOOK(
    ActorTriggerPressurePlateEventHook,
    HookPriority::Normal,
    BasePressurePlateBlock,
    &BasePressurePlateBlock::$shouldTriggerEntityInside,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Actor&          pActor
)
{
    auto before = ActorTriggerPressurePlateBeforeEvent(pActor, pPos);
    LLEventBus.publish(before);
    if (before.isCancelled()) { return false; }
    auto result = origin(pRegion, pPos, pActor);
    if (result) { LLEventBus.publish(ActorTriggerPressurePlateAfterEvent(pActor, pPos)); }
    return result;
}

Event_Hook_Factory(ActorTriggerPressurePlate, <ActorTriggerPressurePlateEventHook>);

} // namespace ila::mc::inline world