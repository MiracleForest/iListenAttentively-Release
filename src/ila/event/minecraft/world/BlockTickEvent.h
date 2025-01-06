#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/util/Random.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
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

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI Random&   getRandom() const;
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

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI Random const&   getRandom() const;
};
} // namespace ila::mc::inline world