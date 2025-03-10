#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline level::inline block
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

    ILNDAPI BlockPos& pos() const;
    ILNDAPI BlockPos& flowFromPos() const;
    ILNDAPI uchar&    flowFromDirection() const;
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

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI BlockPos const& flowFromPos() const;
    ILNDAPI uchar const&    flowFromDirection() const;
};
} // namespace ila::mc::inline world::inline level::inline block