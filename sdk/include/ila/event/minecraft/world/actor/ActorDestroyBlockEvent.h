#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>

// clang-format off
class Vec3;
// clang-format on

namespace ila::mc::inline world::inline actor
{
class ActorDestroyBlockEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    Vec3 const& mPos;

public:
    constexpr explicit ActorDestroyBlockEvent(Actor& actor, Vec3 const& pos)
        : Cancellable(actor)
        , mPos(pos)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI Vec3 const& pos() const;
};
} // namespace ila::mc::inline world::inline actor