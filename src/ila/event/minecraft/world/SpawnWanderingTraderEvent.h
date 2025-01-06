#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class SpawnWanderingTraderBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;

public:
    constexpr explicit SpawnWanderingTraderBeforeEvent(BlockSource& blockSource, BlockPos& pos)
        : Cancellable(blockSource)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
};

class SpawnWanderingTraderAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit SpawnWanderingTraderAfterEvent(BlockSource& blockSource, BlockPos const& pos)
        : WorldEvent(blockSource)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
};
} // namespace ila::mc::inline world