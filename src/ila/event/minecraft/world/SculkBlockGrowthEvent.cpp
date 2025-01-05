#include "ila/event/minecraft/world/SculkBlockGrowthEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/SculkBlockBehavior.h>
#include <mc/world/level/WorldBlockTarget.h>

namespace ila::mc::inline world
{

void SculkBlockGrowthBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
void SculkBlockGrowthBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x = nbt["pos"][0];
    getPos().y = nbt["pos"][1];
    getPos().z = nbt["pos"][2];
}
BlockPos& SculkBlockGrowthBeforeEvent::getPos() const { return mPos; }

void SculkBlockGrowthAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"] = ListTag { getPos().x, getPos().y, getPos().z };
}
BlockPos const& SculkBlockGrowthAfterEvent::getPos() const { return mPos; }

LL_STATIC_HOOK(
    SculkBlockGrowthEventHook,
    HookPriority::Normal,
    &SculkBlockBehavior::_placeGrowthAt,
    void,
    IBlockWorldGenAPI& pTarget,
    BlockSource*       pRegion,
    BlockPos const&    pPos,
    Random&            pRandom,
    SculkSpreader&     pSculkSpreader
)
{
    if (pRegion == nullptr) { return origin(pTarget, pRegion, pPos, pRandom, pSculkSpreader); }
    auto beforeEvent = SculkBlockGrowthBeforeEvent(*pRegion, const_cast<BlockPos&>(pPos));
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return; }
    origin(pTarget, pRegion, pPos, pRandom, pSculkSpreader);
    LLEventBus.publish(SculkBlockGrowthAfterEvent(*pRegion, pPos));
}

Event_Hook_Factory(SculkBlockGrowth, <SculkBlockGrowthEventHook>);

} // namespace ila::mc::inline world