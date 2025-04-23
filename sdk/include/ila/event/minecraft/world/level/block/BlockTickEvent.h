#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>

// clang-format off
class Random;
class BlockPos;
// clang-format on

namespace ila::mc::inline world::inline level::inline block
{
class BlockTickBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    Random&   mRandom;

public:
    constexpr explicit BlockTickBeforeEvent(BlockSource& blockSource, BlockPos& pos, Random& random)
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& pos() const;
    ILNDAPI Random&   random() const;
};

class BlockTickAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Random const&   mRandom;

public:
    constexpr explicit BlockTickAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Random const&   random
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Random const&   random() const;
};
} // namespace ila::mc::inline world::inline level::inline block