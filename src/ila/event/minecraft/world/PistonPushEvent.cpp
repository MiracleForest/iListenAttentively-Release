#include "ila/event/minecraft/world/PistonPushEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/actor/PistonBlockActor.h>

namespace ila::mc::inline world
{

void PistonPushBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pos"]              = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["branchFacing"]     = getBranchFacing();
    nbt["pistonMoveFacing"] = getPistonMoveFacing();
}
void PistonPushBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPos().x            = nbt["pos"];
    getPos().y            = nbt["pos"];
    getPos().z            = nbt["pos"];
    getBranchFacing()     = nbt["branchFacing"];
    getPistonMoveFacing() = nbt["pistonMoveFacing"];
}
BlockPos& PistonPushBeforeEvent::getPos() const { return mPos; }
uchar&    PistonPushBeforeEvent::getBranchFacing() const { return mBranchFacing; }
uchar&    PistonPushBeforeEvent::getPistonMoveFacing() const { return mPistonMoveFacing; }

void PistonPushAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pos"]              = ListTag { getPos().x, getPos().y, getPos().z };
    nbt["branchFacing"]     = getBranchFacing();
    nbt["pistonMoveFacing"] = getPistonMoveFacing();
}
BlockPos const& PistonPushAfterEvent::getPos() const { return mPos; }
uchar const&    PistonPushAfterEvent::getBranchFacing() const { return mBranchFacing; }
uchar const&    PistonPushAfterEvent::getPistonMoveFacing() const { return mPistonMoveFacing; }

LL_TYPE_INSTANCE_HOOK(
    PistonPushEventHook,
    HookPriority::Normal,
    PistonBlockActor,
    &PistonBlockActor::_attachedBlockWalker,
    bool,
    BlockSource&    pRegion,
    BlockPos const& pPos,
    uchar           pBranchFacing,
    uchar           pPistonMoveFacing
)
{
    auto beforeEvent =
        PistonPushBeforeEvent(pRegion, const_cast<BlockPos&>(pPos), pBranchFacing, pPistonMoveFacing);
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pRegion, pPos, pBranchFacing, pPistonMoveFacing);
    if (result) { LLEventBus.publish(PistonPushAfterEvent(pRegion, pPos, pBranchFacing, pPistonMoveFacing)); }
    return result;
}

Event_Hook_Factory(PistonPush, <PistonPushEventHook>);

} // namespace ila::mc::inline world