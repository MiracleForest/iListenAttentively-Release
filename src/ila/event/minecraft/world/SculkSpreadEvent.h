#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>
#include <mc/world/level/block/Block.h>


namespace ila::mc::inline world
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

    ILNDAPI BlockPos& getSelfPos() const;
    ILNDAPI Block&    getSelfBlock() const;
    ILNDAPI uchar&    getSelfFace() const;
    ILNDAPI BlockPos& getTargetPos() const;
    ILNDAPI Block&    getTargetBlock() const;
    ILNDAPI uchar&    getTargetFace() const;
    ILNDAPI uchar&    getFacing() const;
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

    ILNDAPI BlockPos const& getSelfPos() const;
    ILNDAPI Block const&    getSelfBlock() const;
    ILNDAPI uchar const&    getSelfFace() const;
    ILNDAPI BlockPos const& getTargetPos() const;
    ILNDAPI Block const&    getTargetBlock() const;
    ILNDAPI uchar const&    getTargetFace() const;
    ILNDAPI uchar const&    getFacing() const;
};
} // namespace ila::mc::inline worlds