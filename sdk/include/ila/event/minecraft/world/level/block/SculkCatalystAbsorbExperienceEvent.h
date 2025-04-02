#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/world/LevelEvent.h>
#include <mc/world/level/block/actor/SculkCatalystBlockActor.h>

namespace ila::mc::inline world::inline level::inline block
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

    ILNDAPI SculkCatalystBlockActor& blockActor() const;
    ILNDAPI Actor&                   actor() const;
};

class SculkCatalystAbsorbExperienceAfterEvent final : public ll::event::LevelEvent
{
protected:
    SculkCatalystBlockActor& mBlockActor;
    Actor&                   mActor;

public:
    constexpr explicit SculkCatalystAbsorbExperienceAfterEvent(
        Level&                   level,
        SculkCatalystBlockActor& blockActor,
        Actor&                   actor
    )
        : LevelEvent(level)
        , mBlockActor(blockActor)
        , mActor(actor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI SculkCatalystBlockActor& blockActor() const;
    ILNDAPI Actor&                   actor() const;
};
} // namespace ila::mc::inline world::inline level::inline block