#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/block/Block.h>


namespace ila::mc::inline world::inline level::inline block
{
class SculkSpreadBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mSelfPos;
    Block&    mSelfBlock;
    uchar&    mSelfFace;
    BlockPos& mTargetPos;
    Block&    mTargetBlock;
    uchar&    mTargetFace;
    uchar&    mFacing;

public:
    constexpr explicit SculkSpreadBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    selfPos,
        Block&       selfBlock,
        uchar&       selfFace,
        BlockPos&    targetPos,
        Block&       targetBlock,
        uchar&       targetFace,
        uchar&       facing
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

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& selfPos() const;
    ILNDAPI Block&    selfBlock() const;
    ILNDAPI uchar&    selfFace() const;
    ILNDAPI BlockPos& targetPos() const;
    ILNDAPI Block&    targetBlock() const;
    ILNDAPI uchar&    targetFace() const;
    ILNDAPI uchar&    facing() const;
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

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& selfPos() const;
    ILNDAPI Block const&    selfBlock() const;
    ILNDAPI uchar const&    selfFace() const;
    ILNDAPI BlockPos const& targetPos() const;
    ILNDAPI Block const&    targetBlock() const;
    ILNDAPI uchar const&    targetFace() const;
    ILNDAPI uchar const&    facing() const;
};
} // namespace ila::mc::inline world::inline level::inline block