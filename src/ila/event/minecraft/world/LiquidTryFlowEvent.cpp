#include "ila/event/minecraft/world/LiquidTryFlowEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/LiquidBlockDynamic.h>

namespace ila::mc::inline world
{

void LiquidTryFlowBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]               = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["flowFromPos"]       = ListTag { getFlowFromPos().x, getFlowFromPos().y, getFlowFromPos().z };
    nbt["flowFromDirection"] = getFlowFromDirection();
}
void LiquidTryFlowBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x             = nbt["pos"]["x"];
    getPos().y             = nbt["pos"]["y"];
    getPos().z             = nbt["pos"]["z"];
    getFlowFromPos().x     = nbt["flowFromPos"]["x"];
    getFlowFromPos().y     = nbt["flowFromPos"]["y"];
    getFlowFromPos().z     = nbt["flowFromPos"]["z"];
    getFlowFromDirection() = nbt["flowFromDirection"];
}
BlockPos& LiquidTryFlowBeforeEvent::getPos() const { return mPos; }
BlockPos& LiquidTryFlowBeforeEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar&    LiquidTryFlowBeforeEvent::getFlowFromDirection() const { return mFlowFromDirection; }

void LiquidTryFlowAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]               = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["flowFromPos"]       = ListTag { getFlowFromPos().x, getFlowFromPos().y, getFlowFromPos().z };
    nbt["flowFromDirection"] = getFlowFromDirection();
}
BlockPos const& LiquidTryFlowAfterEvent::getPos() const { return mPos; }
BlockPos const& LiquidTryFlowAfterEvent::getFlowFromPos() const { return mFlowFromPos; }
uchar const&    LiquidTryFlowAfterEvent::getFlowFromDirection() const { return mFlowFromDirection; }

LL_TYPE_INSTANCE_HOOK(
    LiquidTryFlowEventHook,
    HookPriority::Normal,
    LiquidBlockDynamic,
    &LiquidBlockDynamic::_isLiquidBlocking,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    BlockPos const& pFlowFromPos,
    uchar           pFlowFromDirection
)
{
    auto beforeEvent = LiquidTryFlowBeforeEvent(
        pRegion,
        const_cast<BlockPos&>(pPos),
        const_cast<BlockPos&>(pFlowFromPos),
        pFlowFromDirection
    );
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pRegion, pPos, pFlowFromPos, pFlowFromDirection);
    if (result)
    {
        LLEventBus.publish(LiquidTryFlowAfterEvent(pRegion, pPos, pFlowFromPos, pFlowFromDirection));
    }
    return result;
}

Event_Hook_Factory(LiquidTryFlow, <LiquidTryFlowEventHook>);

} // namespace ila::mc::inline world