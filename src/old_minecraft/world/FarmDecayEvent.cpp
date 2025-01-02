#include "ila/event/minecraft/world/FarmDecayEvent.h"
#include <mc/world/level/block/FarmBlock.h>

namespace ila::mc::inline world
{

BlockPos const& FarmDecayBeforeEvent::getPos() const { return mPos; }
Actor*&         FarmDecayBeforeEvent::getActor() const { return mActor; }
float&          FarmDecayBeforeEvent::getFallDistance() const { return mFallDistance; }

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
    auto beforeEvent = FarmDecayBeforeEvent(pRegion, pPos, pActor, pFallDistance);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pPos, pActor, pFallDistance);
    eventBus.publish(FarmDecayAfterEvent(pRegion, pPos, pActor, pFallDistance));
}

Event_Factory(FarmDecay, <FarmDecayEventHook>);

} // namespace ila::mc::inline world