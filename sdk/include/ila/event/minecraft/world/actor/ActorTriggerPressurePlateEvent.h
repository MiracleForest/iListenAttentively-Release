#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <mc/world/level/BlockPos.h>

namespace ila::mc::inline world::inline actor
{
class ActorTriggerPressurePlateBeforeEvent final : public ll::event::Cancellable<ll::event::ActorEvent>
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit ActorTriggerPressurePlateBeforeEvent(Actor& actor, BlockPos const& pos)
        : Cancellable(actor)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
};

class ActorTriggerPressurePlateAfterEvent final : public ll::event::ActorEvent
{
protected:
    BlockPos const& mPos;

public:
    constexpr explicit ActorTriggerPressurePlateAfterEvent(Actor& actor, BlockPos const& pos)
        : ActorEvent(actor)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI BlockPos const& pos() const;
};
} // namespace ila::mc::inline world::inline actor