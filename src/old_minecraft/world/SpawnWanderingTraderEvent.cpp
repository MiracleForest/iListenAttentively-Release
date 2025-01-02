#include "ila/event/minecraft/world/SpawnWanderingTraderEvent.h"
#include <mc/world/actor/ai/village/WanderingTraderScheduler.h>

namespace ila::mc::inline world
{

BlockPos& SpawnWanderingTraderBeforeEvent::getPos() const { return mPos; }

BlockPos const& SpawnWanderingTraderAfterEvent::getPos() const { return mPos; }

LL_TYPE_INSTANCE_HOOK(
    SpawnWanderingTraderEventHook,
    HookPriority::Normal,
    WanderingTraderScheduler,
    &WanderingTraderScheduler::_spawnWanderingTraderAtPos,
    void,
    BlockPos const&    pPos,
    BlockSource& pRegion
)
{
    auto beforeEvent = SpawnWanderingTraderBeforeEvent(pRegion, const_cast<BlockPos&>(pPos));
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pPos, pRegion);
    eventBus.publish(SpawnWanderingTraderAfterEvent(pRegion, pPos));
}

Event_Factory(SpawnWanderingTrader, <SpawnWanderingTraderEventHook>);

} // namespace ila::mc::inline world