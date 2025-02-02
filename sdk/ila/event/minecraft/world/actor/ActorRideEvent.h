#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>

namespace ila::mc::inline actor
{
class ActorRideBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Actor& mTarget;

public:
    constexpr explicit ActorRideBeforeEvent(Actor& actor, Actor& target)
        : Cancellable(actor)
        , mTarget(target)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Actor& getTarget() const;
};

class ActorRideAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    Actor const& mTarget;

public:
    constexpr explicit ActorRideAfterEvent(Actor& actor, Actor const& target)
        : ActorEvent(actor)
        , mTarget(target)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILAPI Actor const& getTarget() const;
};
} // namespace ila::mc::inline actor