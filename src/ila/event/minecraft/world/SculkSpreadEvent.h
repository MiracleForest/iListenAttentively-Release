#include "ila/Global.h"

namespace ila::mc::inline world
{
class SculkSpreadBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mSelfPos;
    Block const&    mSelfBlock;
    uchar&          mSelfFace;
    BlockPos const& mTargetPos;
    Block const&    mTargetBlock;
    uchar const&    mTargetFace;
    uchar&          mFacing;

public:
    constexpr explicit SculkSpreadBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& selfPos,
        Block const&    selfBlock,
        uchar&          selfFace,
        BlockPos const& targetPos,
        Block const&    targetBlock,
        uchar const&    targetFace,
        uchar&          facing
    )
        : Cancellable(blockSource)
        , mSelfPos(selfPos)
        , mSelfBlock(selfBlock)
        , mSelfFace(selfFace)
        , mTargetPos(targetPos)
        , mTargetBlock(targetBlock)
        , mTargetFace(targetFace)
        , mFacing(facing)
    {
    }

    ILAPI BlockPos const& getSelfPos() const;
    ILAPI Block const&    getSelfBlock() const;
    ILAPI uchar&          getSelfFace() const;
    ILAPI BlockPos const& getTargetPos() const;
    ILAPI Block const&    getTargetBlock() const;
    ILAPI uchar const&    getTargetFace() const;
    ILAPI uchar&          getFacing() const;
};

class SculkSpreadAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mSelfPos;
    Block const&    mSelfBlock;
    uchar const&    mSelfFace;
    BlockPos const& mTargetPos;
    Block const&    mTargetBlock;
    uchar const&    mTargetFace;
    uchar const&    mFacing;

public:
    constexpr explicit SculkSpreadAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& selfPos,
        Block const&    selfBlock,
        uchar const&    selfFace,
        BlockPos const& targetPos,
        Block const&    targetBlock,
        uchar const&    targetFace,
        uchar const&    facing
    )
        : WorldEvent(blockSource)
        , mSelfPos(selfPos)
        , mSelfBlock(selfBlock)
        , mSelfFace(selfFace)
        , mTargetPos(targetPos)
        , mTargetBlock(targetBlock)
        , mTargetFace(targetFace)
        , mFacing(facing)
    {
    }

    ILAPI BlockPos const& getSelfPos() const;
    ILAPI Block const&    getSelfBlock() const;
    ILAPI uchar const&    getSelfFace() const;
    ILAPI BlockPos const& getTargetPos() const;
    ILAPI Block const&    getTargetBlock() const;
    ILAPI uchar const&    getTargetFace() const;
    ILAPI uchar const&    getFacing() const;
};
} // namespace ila::mc::inline world