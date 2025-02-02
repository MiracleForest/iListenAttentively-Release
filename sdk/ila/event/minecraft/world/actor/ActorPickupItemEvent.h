#pragma once
#include "ila/base/Macro.h"
#include <ll/api/event/Cancellable.h>
#include <ll/api/event/entity/MobEvent.h>

namespace ila::mc::inline actor
{
class ActorPickupItemBeforeEvent final : public ll::event::Cancellable<ll::event::entity::MobEvent>
{
protected:
    ItemActor& mItemActor;

public:
    constexpr explicit ActorPickupItemBeforeEvent(Mob& actor, ItemActor& itemActor)
        : Cancellable(actor)
        , mItemActor(itemActor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ItemActor& getItemActor() const;
};

class ActorPickupItemAfterEvent final : public ll::event::entity::MobEvent
{
protected:
    ItemActor const& mItemActor;

public:
    constexpr explicit ActorPickupItemAfterEvent(Mob& actor, ItemActor const& itemActor)
        : MobEvent(actor)
        , mItemActor(itemActor)
    {
    }

    ILAPI void serialize(CompoundTag& nbt) const override;

    ILNDAPI ItemActor const& getItemActor() const;
};
} // namespace ila::mc::inline actor