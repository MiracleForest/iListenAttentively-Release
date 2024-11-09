#include "SculkBlockGrowthEvent.h"

namespace ila::inline world
{

BlockPos const& SculkBlockGrowthBeforeEvent::getPos() const { return mPos; }

BlockPos const& SculkBlockGrowthAfterEvent::getPos() const { return mPos; }

LL_STATIC_HOOK(
    SculkBlockGrowthEventHook,
    HookPriority::Normal,
    "?_placeGrowthAt@SculkBlockBehavior@@CAXAEAVIBlockWorldGenAPI@@PEAVBlockSource@@AEBVBlockPos@@AEAVRandom@"
    "@"
    "AEAVSculkSpreader@@@Z",
    void,
    class IBlockWorldGenAPI& pTarget,
    BlockSource*             pRegion,
    BlockPos const&          pPos,
    Random&                  pRandom,
    class SculkSpreader&     pSculkSpreader
)
{
    if (pRegion == nullptr) return origin(pTarget, pRegion, pPos, pRandom, pSculkSpreader);
    auto beforeEvent = SculkBlockGrowthBeforeEvent(*pRegion, pPos);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pTarget, pRegion, pPos, pRandom, pSculkSpreader);
    eventBus.publish(SculkBlockGrowthAfterEvent(*pRegion, pPos));
}

Event_Factory(SculkBlockGrowth, <SculkBlockGrowthEventHook>);

} // namespace ila::inline world