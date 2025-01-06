#include "ila/event/minecraft/world/FarmDecayEvent.h"
#include "ila/base/Gloabl.h"
#include <cstdint>
#include <mc/world/level/block/FarmBlock.h>

namespace ila::mc::inline world
{

void FarmDecayBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]          = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["actor"]        = serializeRefObj(getActor());
    nbt["fallDistance"] = getFallDistance();
}
void FarmDecayBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x        = nbt["pos"][0];
    getPos().y        = nbt["pos"][1];
    getPos().z        = nbt["pos"][2];
    getFallDistance() = nbt["fallDistance"];
}
BlockPos& FarmDecayBeforeEvent::getPos() const { return mPos; }
Actor*&   FarmDecayBeforeEvent::getActor() const { return mActor; }
float&    FarmDecayBeforeEvent::getFallDistance() const { return mFallDistance; }

void FarmDecayAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]          = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["actor"]        = serializeRefObj(getActor());
    nbt["fallDistance"] = getFallDistance();
}
BlockPos const& FarmDecayAfterEvent::getPos() const { return mPos; }
Actor* const&   FarmDecayAfterEvent::getActor() const { return mActor; }
float const&    FarmDecayAfterEvent::getFallDistance() const { return mFallDistance; }

LL_TYPE_INSTANCE_HOOK(
    FarmDecayEventHook,
    HookPriority::Normal,
    FarmBlock,
    &FarmBlock::$transformOnFall,
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Actor*          pActor,
    float           pFallDistance
)
{
    auto beforeEvent = FarmDecayBeforeEvent(pRegion, const_cast<BlockPos&>(pPos), pActor, pFallDistance);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pRegion, pPos, pActor, pFallDistance);
    LLEventBus.publish(FarmDecayAfterEvent(pRegion, pPos, pActor, pFallDistance));
}

Event_Hook_Factory(FarmDecay, <FarmDecayEventHook>);

} // namespace ila::mc::inline world