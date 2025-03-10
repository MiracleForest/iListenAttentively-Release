#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/block/actor/ChestBlockActor.h>

namespace ila::mc::inline world::inline level::inline block::inline actor
{
class ChestPairWithBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    ChestBlockActor& mChest;
    BlockPos&        mPosition;

public:
    constexpr explicit ChestPairWithBeforeEvent(
        BlockSource&     blockSource,
        ChestBlockActor& chest,
        BlockPos&        position
    )
        : Cancellable(blockSource)
        , mChest(chest)
        , mPosition(position)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI ChestBlockActor& chest() const;
    ILNDAPI BlockPos&        pos() const;
};

class ChestPairWithAfterEvent final : public ll::event::WorldEvent
{
protected:
    ChestBlockActor& mChest;
    BlockPos const&  mPosition;

public:
    constexpr explicit ChestPairWithAfterEvent(
        BlockSource&     blockSource,
        ChestBlockActor& chest,
        BlockPos const&  position
    )
        : WorldEvent(blockSource)
        , mChest(chest)
        , mPosition(position)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ChestBlockActor& chest() const;
    ILNDAPI BlockPos const&  pos() const;
};
} // namespace ila::mc::inline world::inline level::inline block::inline actor