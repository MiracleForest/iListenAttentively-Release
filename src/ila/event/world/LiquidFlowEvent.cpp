#include "LiquidFlowEvent.h"
#include <mc/world/level/block/LiquidBlockDynamic.h>

namespace ila::inline world
{

BlockPos const& LiquidFlowBeforeEvent::getPos() const { return mPos; }
int&            LiquidFlowBeforeEvent::getNeighbor() const { return mNeighbor; }
BlockPos const& LiquidFlowBeforeEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar&          LiquidFlowBeforeEvent::getFlowFromDirection() const { return mFlowFromDirection; }

BlockPos const& LiquidFlowAfterEvent::getPos() const { return mPos; }
int const&      LiquidFlowAfterEvent::getNeighbor() const { return mNeighbor; }
BlockPos const& LiquidFlowAfterEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar const&    LiquidFlowAfterEvent::getFlowFromDirection() const { return mFlowFromDirection; }

LL_TYPE_INSTANCE_HOOK(
    LiquidFlowEventHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_trySpreadTo,
    void,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    int             pNeighbor,
    BlockPos const& pFlowFromPos,
    uchar           pFlowFromDirection
)
{
    auto beforeEvent = LiquidFlowBeforeEvent(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return;
    origin(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(LiquidFlowAfterEvent(pRegion, pPos, pNeighbor, pFlowFromPos, pFlowFromDirection));
}

Event_Factory(LiquidFlow, <LiquidFlowEventHook>);

} // namespace ila::inline world