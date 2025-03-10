#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/WorldEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline level::inline block
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

    ILNDAPI BlockPos& pos() const;
    ILNDAPI Actor*&   actor() const;
    ILNDAPI float&    fallDistance() const;
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

    ILNDAPI BlockPos const& pos() const;
    ILNDAPI Actor* const&   actor() const;
    ILNDAPI float const&    fallDistance() const;
};
} // namespace ila::mc::inline world::inline level::inline block