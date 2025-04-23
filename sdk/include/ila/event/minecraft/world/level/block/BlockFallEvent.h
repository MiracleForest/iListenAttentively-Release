#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/actor/item/FallingBlockActor.h>

// clang-format off
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline level::inline block
{
class BlockFallBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Block const&    mOldBlock;
    bool&           mCreative;

public:
    constexpr explicit BlockFallBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Block const&    oldBlock,
        bool&           creative
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mOldBlock(oldBlock)
        , mCreative(creative)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Block const&    oldBlock() const;
    ILNDAPI bool&           creative() const;
};

class BlockFallAfterEvent final : public ll::event::ActorEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit BlockFallAfterEvent(FallingBlockActor& actor, BlockPos const& pos)
        : ActorEvent(actor)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const&    pos() const;
    ILNDAPI FallingBlockActor& self() const;
};
} // namespace ila::mc::inline world::inline level::inline block