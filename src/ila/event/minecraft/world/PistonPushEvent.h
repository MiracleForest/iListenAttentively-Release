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
    BlockPos& mPos;
    uchar&    mBranchFacing;
    uchar&    mPistonMoveFacing;

public:
    constexpr explicit PistonPushBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        uchar&       branchFacing,
        uchar&       pistonMoveFacing
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI uchar&    getBranchFacing() const;
    ILNDAPI uchar&    getPistonMoveFacing() const;
};

class PistonPushAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    uchar const&    mBranchFacing;
    uchar const&    mPistonMoveFacing;

public:
    constexpr explicit PistonPushAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        uchar&          branchFacing,
        uchar&          pistonMoveFacing
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mBranchFacing(branchFacing)
        , mPistonMoveFacing(pistonMoveFacing)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI uchar const&    getBranchFacing() const;
    ILNDAPI uchar const&    getPistonMoveFacing() const;
};
} // namespace ila::mc::inline world