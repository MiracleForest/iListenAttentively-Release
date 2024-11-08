#include "Global.h"
#include <mc/world/effect/MobEffectInstance.h>

namespace ila::inline actor
{
class ActorGetEffectBeforeEvent final : public ll::event::Cancellable<ll::event::entity::ActorEvent>
{
protected:
    MobEffectInstance const& mEffect;

public:
    constexpr explicit ActorGetEffectBeforeEvent(Actor& actor, MobEffectInstance const& effect)
        : Cancellable(actor)
        , mEffect(effect)
    {
    }

    ILAPI MobEffectInstance const& getEffect() const;
};

class ActorGetEffectAfterEvent final : public ll::event::entity::ActorEvent
{
protected:
    MobEffectInstance const& mEffect;

public:
    constexpr explicit ActorGetEffectAfterEvent(Actor& actor, MobEffectInstance const& effect)
        : ActorEvent(actor)
        , mEffect(effect)
    {
    }

    ILAPI MobEffectInstance const& getEffect() const;
};
} // namespace ila::inline actor