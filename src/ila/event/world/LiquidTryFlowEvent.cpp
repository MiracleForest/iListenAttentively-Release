#include "LiquidTryFlowEvent.h"
#include <mc/world/level/block/LiquidBlockDynamic.h>

namespace ila::inline world
{

BlockPos const& LiquidTryFlowBeforeEvent::getPos() const { return mPos; }
BlockPos const& LiquidTryFlowBeforeEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar&          LiquidTryFlowBeforeEvent::getFlowFromDirection() const { return mFlowFromDirection; }

BlockPos const& LiquidTryFlowAfterEvent::getPos() const { return mPos; }
BlockPos const& LiquidTryFlowAfterEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar const&    LiquidTryFlowAfterEvent::getFlowFromDirection() const { return mFlowFromDirection; }
bool&           LiquidTryFlowAfterEvent::getResult() const { return mResult; }

LL_TYPE_INSTANCE_HOOK(
    LiquidTryFlowEventHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_canSpreadTo,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    BlockPos const& pFlowFromPos,
    uchar           pFlowFromDirection
)
{
    auto beforeEvent = LiquidTryFlowBeforeEvent(pRegion, pPos, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) return false;
    auto result = origin(pRegion, pPos, pFlowFromPos, pFlowFromDirection);
    eventBus.publish(LiquidTryFlowAfterEvent(pRegion, pPos, pFlowFromPos, pFlowFromDirection, result));
    return result;
}

Event_Factory(LiquidTryFlow, <LiquidTryFlowEventHook>);

} // namespace ila::inline world