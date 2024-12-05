#include "ila/event/minecraft/world/BlockTickEvent.h"
#include <mc/world/level/block/Block.h>

namespace ila::mc::inline world
{

BlockPos const& BlockTickBeforeEvent::getPos() const { return mPos; }
Random&         BlockTickBeforeEvent::getRandom() const { return mRandom; }

BlockPos const& BlockTickAfterEvent::getPos() const { return mPos; }
Random const&   BlockTickAfterEvent::getRandom() const { return mRandom; }

LL_TYPE_INSTANCE_HOOK(
    BlockTickEventHook,
    HookPriority::Normal,
    Block,
    "?randomTick@Block@@QEBAXAEAVBlockSource@@AEBVBlockPos@@AEAVRandom@@@Z",
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    Random&         pRandom
)
{
    auto beforeEvent = BlockTickBeforeEvent(pRegion, pPos, pRandom);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pPos, pRandom);
    eventBus.publish(BlockTickAfterEvent(pRegion, pPos, pRandom));
}

Event_Factory(BlockTick, <BlockTickEventHook>);

} // namespace ila::mc::inline world