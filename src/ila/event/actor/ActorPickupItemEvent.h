#include "Global.h"
#include <mc/world/effect/MobEffectInstance.h>

namespace ila::inline actor
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

    ILAPI ItemActor& getItemActor() const;
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

    ILAPI ItemActor const& getItemActor() const;
};
} // namespace ila::inline actor