#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/util/Random.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline level::inline block
{
class DragonEggBlockTeleportBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos const& mPos;
    Random&         mRandom;
    BlockPos&       mTargetPos;

public:
    constexpr explicit DragonEggBlockTeleportBeforeEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Random&         random,
        BlockPos&       targetPos
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPos(targetPos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Random&         random() const;
    ILNDAPI BlockPos&       targetPos() const;
};

class DragonEggBlockTeleportAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Random const&   mRandom;
    BlockPos const& mTargetPos;

public:
    constexpr explicit DragonEggBlockTeleportAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Random const&   random,
        BlockPos const& targetPos
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mRandom(random)
        , mTargetPos(targetPos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Random const&   random() const;
    ILNDAPI BlockPos const& targetPos() const;
};
} // namespace ila::mc::inline world::inline level::inline block