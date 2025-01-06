#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/LevelEvent.h>
#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

namespace ila::mc::inline level
{
class SculkCatalystAbsorbExperienceBeforeEvent final : public ll::event::Cancellable<ll::event::LevelEvent>
{
protected:
    SculkCatalystBlockActor& mBlockActor;
    Actor&                   mActor;

public:
    constexpr explicit SculkCatalystAbsorbExperienceBeforeEvent(
        Level&                   level,
        SculkCatalystBlockActor& blockActor,
        Actor&                   actor
    )
        : Cancellable(level)
        , mBlockActor(blockActor)
        , mActor(actor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI SculkCatalystBlockActor& getBlockActor() const;
    ILNDAPI Actor&                   getActor() const;
};

class SculkCatalystAbsorbExperienceAfterEvent final : public ll::event::LevelEvent
{
protected:
    SculkCatalystBlockActor const& mBlockActor;
    Actor const&                   mActor;

public:
    constexpr explicit SculkCatalystAbsorbExperienceAfterEvent(
        Level&                         level,
        SculkCatalystBlockActor const& blockActor,
        Actor const&                   actor
    )
        : LevelEvent(level)
        , mBlockActor(blockActor)
        , mActor(actor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI SculkCatalystBlockActor const& getBlockActor() const;
    ILNDAPI Actor const&                   getActor() const;
};
} // namespace ila::mc::inline level