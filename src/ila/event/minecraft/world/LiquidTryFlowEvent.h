#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class LiquidTryFlowBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    BlockPos& mFlowFromPos;
    uchar&    mFlowFromDirection;

public:
    constexpr explicit LiquidTryFlowBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        BlockPos&    flowFromPos,
        uchar&       flowFromDirection
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI BlockPos& getFlowFromPos() const;
    ILNDAPI uchar&    getFlowFromDirection() const;
};

class LiquidTryFlowAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    BlockPos const& mFlowFromPos;
    uchar const&    mFlowFromDirection;

public:
    constexpr explicit LiquidTryFlowAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        BlockPos const& flowFromPos,
        uchar&          flowFromDirection
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mFlowFromPos(flowFromPos)
        , mFlowFromDirection(flowFromDirection)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI BlockPos const& getFlowFromPos() const;
    ILNDAPI uchar const&    getFlowFromDirection() const;
};
} // namespace ila::mc::inline world