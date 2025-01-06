#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world
{
class FarmDecayBeforeEvent final : public ll::event::Cancellable<ll::event::WorldEvent>
{
protected:
    BlockPos& mPos;
    Actor*&   mActor;
    float&    mFallDistance;

public:
    constexpr explicit FarmDecayBeforeEvent(
        BlockSource& blockSource,
        BlockPos&    pos,
        Actor*&      actor,
        float&       fallDistance
    )
        : Cancellable(blockSource)
        , mPos(pos)
        , mActor(actor)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;
    ILAPI void deserialize(CompoundTag const& nbt) override;

    ILNDAPI BlockPos& getPos() const;
    ILNDAPI Actor*&   getActor() const;
    ILNDAPI float&    getFallDistance() const;
};

class FarmDecayAfterEvent final : public ll::event::WorldEvent
{
protected:
    BlockPos const& mPos;
    Actor* const&   mActor;
    float const&    mFallDistance;

public:
    constexpr explicit FarmDecayAfterEvent(
        BlockSource&    blockSource,
        BlockPos const& pos,
        Actor* const&   actor,
        float const&    fallDistance
    )
        : WorldEvent(blockSource)
        , mPos(pos)
        , mActor(actor)
        , mFallDistance(fallDistance)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& getPos() const;
    ILNDAPI Actor* const&   getActor() const;
    ILNDAPI float const&    getFallDistance() const;
};
} // namespace ila::mc::inline world