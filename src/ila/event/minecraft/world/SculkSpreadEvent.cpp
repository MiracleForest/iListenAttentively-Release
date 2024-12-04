#include "SculkSpreadEvent.h"
#include <mc/world/level/WorldBlockTarget.h>
#include <mc/world/level/block/Block.h>
#include <mc/world/level/block/MultifaceSpreader.h>

namespace ila::mc::inline world
{

BlockPos const& SculkSpreadBeforeEvent::getSelfPos() const { return mSelfPos; }
Block const&    SculkSpreadBeforeEvent::getSelfBlock() const { return mSelfBlock; }
uchar&          SculkSpreadBeforeEvent::getSelfFace() const { return mSelfFace; }
BlockPos const& SculkSpreadBeforeEvent::getTargetPos() const { return mTargetPos; }
Block const&    SculkSpreadBeforeEvent::getTargetBlock() const { return mTargetBlock; }
uchar const&    SculkSpreadBeforeEvent::getTargetFace() const { return mTargetFace; }
uchar&          SculkSpreadBeforeEvent::getFacing() const { return mFacing; }

BlockPos const& SculkSpreadAfterEvent::getSelfPos() const { return mSelfPos; }
Block const&    SculkSpreadAfterEvent::getSelfBlock() const { return mSelfBlock; }
uchar const&    SculkSpreadAfterEvent::getSelfFace() const { return mSelfFace; }
BlockPos const& SculkSpreadAfterEvent::getTargetPos() const { return mTargetPos; }
Block const&    SculkSpreadAfterEvent::getTargetBlock() const { return mTargetBlock; }
uchar const&    SculkSpreadAfterEvent::getTargetFace() const { return mTargetFace; }
uchar const&    SculkSpreadAfterEvent::getFacing() const { return mFacing; }

using Return_Type = std::optional<std::pair<BlockPos const, uchar const>>;

LL_TYPE_INSTANCE_HOOK(
    SculkSpreadEventHook,
    HookPriority::Normal,
    MultifaceSpreader,
    &MultifaceSpreader::getSpreadFromFaceTowardDirection,
    Return_Type,
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
        auto& region      = ((WorldBlockTarget&)pTarget).mBlockSource;
        auto  beforeEvent = SculkSpreadBeforeEvent(
            region,
            pPos,
            pSelf,
            pFace,
            result->first,
            pBlock,
            result->second,
            pFacing
        );
        eventBus.publish(beforeEvent);
        if (beforeEvent.isCancelled()) return std::nullopt;
        eventBus.publish(
            SculkSpreadAfterEvent(region, pPos, pSelf, pFace, result->first, pBlock, result->second, pFacing)
        );
    }
    return result;
}

Event_Factory(SculkSpread, <SculkSpreadEventHook>);

} // namespace ila::mc::inline world