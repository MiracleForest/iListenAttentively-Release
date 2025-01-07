#include "ila/event/minecraft/world/PistonPushEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/block/actor/PistonBlockActor.h>

namespace ila::mc::inline world
{

void PistonPushBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["pistonPos"]        = ListTag { getPistonPos().x, getPistonPos().y, getPistonPos().z };
    nbt["pushPos"]          = ListTag { getPushPos().x, getPushPos().y, getPushPos().z };
    nbt["branchFacing"]     = getBranchFacing();
    nbt["pistonMoveFacing"] = getPistonMoveFacing();
}
void PistonPushBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getPushPos().x        = nbt["pushPos"];
    getPushPos().y        = nbt["pushPos"];
    getPushPos().z        = nbt["pushPos"];
    getBranchFacing()     = nbt["branchFacing"];
    getPistonMoveFacing() = nbt["pistonMoveFacing"];
}
BlockPos const& PistonPushBeforeEvent::getPistonPos() const { return mPistonPos; }
BlockPos&       PistonPushBeforeEvent::getPushPos() const { return mPushPos; }
uchar&          PistonPushBeforeEvent::getBranchFacing() const { return mBranchFacing; }
uchar&          PistonPushBeforeEvent::getPistonMoveFacing() const { return mPistonMoveFacing; }

void PistonPushAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["pistonPos"]        = ListTag { getPistonPos().x, getPistonPos().y, getPistonPos().z };
    nbt["pushPos"]          = ListTag { getPushPos().x, getPushPos().y, getPushPos().z };
    nbt["branchFacing"]     = getBranchFacing();
    nbt["pistonMoveFacing"] = getPistonMoveFacing();
}
BlockPos const& PistonPushAfterEvent::getPistonPos() const { return mPistonPos; }
BlockPos const& PistonPushAfterEvent::getPushPos() const { return mPushPos; }
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
    auto beforeEvent = PistonPushBeforeEvent(
        pRegion,
        getPosition(),
        const_cast<BlockPos&>(pPos),
        pBranchFacing,
        pPistonMoveFacing
    );
    LLEventBus.publish(beforeEvent);
    if (beforeEvent.isCancelled()) { return false; }
    auto result = origin(pRegion, pPos, pBranchFacing, pPistonMoveFacing);
    if (result)
    {
        LLEventBus.publish(
            PistonPushAfterEvent(pRegion, getPosition(), pPos, pBranchFacing, pPistonMoveFacing)
        );
    }
    return result;
}

Event_Hook_Factory(PistonPush, <PistonPushEventHook>);

} // namespace ila::mc::inline world