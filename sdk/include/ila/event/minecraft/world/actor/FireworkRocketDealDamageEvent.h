#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/ActorEvent.h>
#include <mc/world/actor/item/FireworksRocketActor.h>

namespace ila::mc::inline world::inline actor
{
class FireworkRocketDealDamageBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
public:
    constexpr explicit FireworkRocketDealDamageBeforeEvent(FireworksRocketActor& actor)
        : Cancellable(actor)
    {
    }

    ILAPI void serialize(CompoundTag&) const override;

    ILNDAPI FireworksRocketActor& self() const;
};

class FireworkRocketDealDamageAfterEvent final : public ll::event::entity::ActorEvent
{
public:
    constexpr explicit FireworkRocketDealDamageAfterEvent(FireworksRocketActor& actor)
        : ActorEvent(actor)
    {
    }

    ILAPI void serialize(CompoundTag&) const override;

    ILNDAPI FireworksRocketActor& self() const;
};
} // namespace ila::mc::inline world::inline actor