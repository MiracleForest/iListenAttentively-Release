#include "ila/event/minecraft/world/SculkSpreadEvent.h"
#include "ila/base/Gloabl.h"
#include <mc/world/level/WorldBlockTarget.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/MultifaceSpreader.h>

namespace ila::mc::inline world
{

void SculkSpreadBeforeEvent::serialize(CompoundTag& nbt) const
{
    Cancellable::serialize(nbt);
    nbt["selfPos"]     = ListTag { getSelfPos().x, getSelfPos().y, getSelfPos().z };
    nbt["selfBlock"]   = serializeRefObj(getSelfBlock());
    nbt["selfFace"]    = getSelfFace();
    nbt["targetPos"]   = ListTag { getTargetPos().x, getTargetPos().y, getTargetPos().z };
    nbt["targetBlock"] = serializeRefObj(getTargetBlock());
    nbt["targetFace"]  = getTargetFace();
    nbt["facing"]      = getFacing();
}
void SculkSpreadBeforeEvent::deserialize(CompoundTag const& nbt)
{
    Cancellable::deserialize(nbt);
    getSelfPos().x   = nbt["selfPos"][0];
    getSelfPos().y   = nbt["selfPos"][1];
    getSelfPos().z   = nbt["selfPos"][2];
    getSelfFace()    = nbt["selfFace"];
    getTargetPos().x = nbt["targetPos"][0];
    getTargetPos().y = nbt["targetPos"][1];
    getTargetPos().z = nbt["targetPos"][2];
    getTargetFace()  = nbt["targetFace"];
    getFacing()      = nbt["facing"];
}
BlockPos& SculkSpreadBeforeEvent::getSelfPos() const { return mSelfPos; }
Block&    SculkSpreadBeforeEvent::getSelfBlock() const { return mSelfBlock; }
uchar&    SculkSpreadBeforeEvent::getSelfFace() const { return mSelfFace; }
BlockPos& SculkSpreadBeforeEvent::getTargetPos() const { return mTargetPos; }
Block&    SculkSpreadBeforeEvent::getTargetBlock() const { return mTargetBlock; }
uchar&    SculkSpreadBeforeEvent::getTargetFace() const { return mTargetFace; }
uchar&    SculkSpreadBeforeEvent::getFacing() const { return mFacing; }


void SculkSpreadAfterEvent::serialize(CompoundTag& nbt) const
{
    WorldEvent::serialize(nbt);
    nbt["selfPos"]     = ListTag { getSelfPos().x, getSelfPos().y, getSelfPos().z };
    nbt["selfBlock"]   = serializeRefObj(getSelfBlock());
    nbt["selfFace"]    = getSelfFace();
    nbt["targetPos"]   = ListTag { getTargetPos().x, getTargetPos().y, getTargetPos().z };
    nbt["targetBlock"] = serializeRefObj(getTargetBlock());
    nbt["targetFace"]  = getTargetFace();
    nbt["facing"]      = getFacing();
}
BlockPos const& SculkSpreadAfterEvent::getSelfPos() const { return mSelfPos; }
Block const&    SculkSpreadAfterEvent::getSelfBlock() const { return mSelfBlock; }
uchar const&    SculkSpreadAfterEvent::getSelfFace() const { return mSelfFace; }
BlockPos const& SculkSpreadAfterEvent::getTargetPos() const { return mTargetPos; }
Block const&    SculkSpreadAfterEvent::getTargetBlock() const { return mTargetBlock; }
uchar const&    SculkSpreadAfterEvent::getTargetFace() const { return mTargetFace; }
uchar const&    SculkSpreadAfterEvent::getFacing() const { return mFacing; }

using ReturnType = std::optional<std::pair<BlockPos const, uchar const>>;

LL_TYPE_INSTANCE_HOOK(
    SculkSpreadEventHook,
    HookPriority::Normal,
    MultifaceSpreader,
    &MultifaceSpreader::getSpreadFromFaceTowardDirection,
    ReturnType,
    IBlockWorldGenAPI& pTarget,
    Block const&       pSelf,
    Block const&       pBlock,
    BlockPos const&    pPos,
    uchar              pFacing,
    uchar              pFace
)
{
    auto result = origin(pTarget, pSelf, pBlock, pPos, pFacing, pFace);
    if (result.has_value())
    {
        auto& region      = (static_cast<WorldBlockTarget&>(pTarget)).mBlockSource;
        auto  beforeEvent = SculkSpreadBeforeEvent(
            region,
            const_cast<BlockPos&>(pPos),
            const_cast<Block&>(pSelf),
            pFace,
            const_cast<BlockPos&>(result->first),
            const_cast<Block&>(pBlock),
            const_cast<uchar&>(result->second),
            pFacing
        );
        LLEventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) { return std::nullopt; }
        LLEventBus.publish(
            SculkSpreadAfterEvent(region, pPos, pSelf, pFace, result->first, pBlock, result->second, pFacing)
        );
    }
    return result;
}

Event_Hook_Factory(SculkSpread, <SculkSpreadEventHook>);

} // namespace ila::mc::inline world