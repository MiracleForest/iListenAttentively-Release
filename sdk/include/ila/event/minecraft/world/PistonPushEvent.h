#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class PistonPushBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPistonPos;
    BlockPos& mPushPos;
    uchar&    mBranchFacing;
    uchar&    mPistonMoveFacing;

public:
    constexpr explicit PistonPushBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pistonPos,
        BlockPos&    pushPos,
        uchar&       branchFacing,
        uchar&       pistonMoveFacing
    )
        : Cancellable(blockSource)
        , mPistonPos(pistonPos)
        , mPushPos(pushPos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pistonPos() const;
    ILNDAPI BlockPos& pushPos() const;
    ILNDAPI uchar&    branchFacing() const;
    ILNDAPI uchar&    pistonMoveFacing() const;
};

class PistonPushAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPistonPos;
    BlockPos const& mPushPos;
    uchar const&    mBranchFacing;
    uchar const&    mPistonMoveFacing;

public:
    constexpr explicit PistonPushAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pistonPos,
        BlockPos const& pushPos,
        uchar&          branchFacing,
        uchar&          pistonMoveFacing
    )
        : WorldEvent(blockSource)
        , mPistonPos(pistonPos)
        , mPushPos(pushPos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pistonPos() const;
    ILNDAPI BlockPos const& pushPos() const;
    ILNDAPI uchar const&    branchFacing() const;
    ILNDAPI uchar const&    pistonMoveFacing() const;
};
} // namespace ila::mc::inline world